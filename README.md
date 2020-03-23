# LB2C (LB2 Clone)

LB2の再実装。

## セットアップ

Ubuntu/Debianでの例を示す。

- Java, SBTのインストール

```
$ sudo apt-get install openjdk-8-jdk
$ echo "deb https://dl.bintray.com/sbt/debian /" | sudo tee -a /etc/apt/sources.list.d/sbt.list
$ curl -sL "https://keyserver.ubuntu.com/pks/lookup?op=get&search=0x2EE0EA64E40A89B84B2DF73499E82A75642AC823" | sudo apt-key add
$ sudo apt-get update
$ sudo apt-get install sbt
```

- 生成コードのビルド環境の準備(gcc, make, libomp, etc.)

```
$ sudo apt-get install build-essential
$ sudo apt-get install libomp-dev
```

## 実行

sbtのrunコマンドの後に、動作モードとクエリを指定して実行する。コード生成からビルド、実行まで一通り行われる。

```
$ git clone https://github.com/jnmt/lb2c.git
$ cd lb2c
$ sbt
> run compiler "Print(Scan(\"a.tbl\"))" 
```

- 動作モード

| モード    | 説明 |
| :-----: | :-- |
| compiler    | 通常モード。対応済みオペレータは下記参照のこと。 |
| simd        | SIMDモード。オペレータは通常モードと同様。AVX-512用のフラグをつけてビルドし、インテルのエミュレータ(SDE)経由で実行 |
| parallel    | 並列処理コード生成モード。オペレータはSIMD対応を除き通常モードと同様。不安定。 |
| interpreter | インタープリタで実行。一部オペレータのみ。 |

- サポート済みオペレータ

| オペレータ | 説明 |
| :-----: | :-- |
| Print   | 結果を標準出力へ出力。 |
| Time    | 実行時間を計測して出力。 |
| Scan    | パイプ"\|"区切りのテキストファイルをスキャン。 |
| Filter  | 指定した述語に基づいタプルを選択。 |
| FilterV | 指定した述語に基づいタプルを選択。SIMD利用。 |
| Project | 指定した属性を射影。 |
| Calculate  | 指定した計算式を評価。 |
| CalculateV | 指定した計算式を評価。SIMD利用。 |
| NestedLoopJoin | ネストループ結合方式で関係結合。 |
| HashJoin       | ハッシュ結合方式で関係結合。 |
| Aggregate | 集約。count/min/max/sum/avgをサポート。 |
| Sort      | クイックソートでソート。昇順のみサポート。 |
| CaseWhen  | CASE WHEN文。 |
| Preload   | 事前にテキストファイルをスキャンしてメモリ上にロード。 |
| ScanTable | Preloadしたテーブルをスキャン |

## クエリ例

- Scan

```
Print( Scan(\"/Users/jun/src/tpch-dbgen/nation.tbl\", int n_nationkey, string n_name, int n_regionkey, string n_comment) )
```

- Filter

```
Print( Filter( Scan(\"/Users/jun/src/tpch-dbgen/nation.tbl\", int n_nationkey, string n_name, int n_regionkey, string n_comment), n_regionkey=3) )
```

- HashJoin

```
Print(
HashJoin (
  Filter( Scan(\"/Users/jun/src/tpch-dbgen/nation.tbl\", int n_nationkey, string n_name, int n_regionkey, string n_comment), n_regionkey=3),
  Scan(\"/Users/jun/src/tpch-dbgen/customer.tbl\", int c_custkey, string c_name, string c_address, int c_nationkey, string c_phone, double c_acctbal, string c_mktsegment, string c_comment),
  n_nationkey, c_nationkey
  )
)
```

- Project

```
Print(
Project(
  NestedLoopJoin (
    Filter( Scan(\"/Users/jun/src/tpch-dbgen/nation.tbl\", int n_nationkey, string n_name, int n_regionkey, string n_comment), n_regionkey=3),
    Scan(\"/Users/jun/src/tpch-dbgen/customer.tbl\", int c_custkey, string c_name, string c_address, int c_nationkey, string c_phone, double c_acctbal, string c_mktsegment, string c_comment),
    n_nationkey, c_nationkey
    ),
  c_custkey, c_name, n_name )
)
```

- Aggregate

```
Print(
  Aggregate(
    HashJoin(
      Scan(\"/Users/jun/src/tpch-dbgen/partsupp.tbl\", int ps_partkey, int ps_suppkey, int ps_availqty, double ps_supplycost, string ps_comment),
      Scan(\"/Users/jun/src/tpch-dbgen/lineitem.tbl\", int l_orderkey, int l_partkey, int l_suppkey, int l_linenumber, double l_quantity, double l_extendedprice, double l_discount, double l_tax, string l_returnflag, string l_linestatus, string l_shipdate, string l_commitdate, string l_receiptdate, string l_shipinstruct, string l_shipmode, string l_comment),
      ps_suppkey, l_suppkey
    ),
    keys(l_orderkey), count(*) )
)
```

- Calculate, Aggregate & Project

```
Print(
  Project(
    Aggregate(
      Calculate(
        Scan(\"/Users/jun/src/tpch-dbgen/lineitem.tbl\", int l_orderkey, int l_partkey, int l_suppkey, int l_linenumber, double l_quantity, double l_extendedprice, double l_discount, double l_tax, string l_returnflag, string l_linestatus, string l_shipdate, string l_commitdate, string l_receiptdate, string l_shipinstruct, string l_shipmode, string l_comment),
        l_extendedprice*(1-l_discount)*(1+l_tax) as charge
      ),
      keys(l_returnflag, l_linestatus), sum(charge) ),
  sum_charge
  )
)
```

- Sort

```
Print(
  Sort(
    Scan(\"/Users/jun/src/tpch-dbgen/part.tbl\", int p_partkey, string p_name, string p_mfgr, string p_brand, string p_type, int p_size, string p_container, double p_retailprice, string p_comment),
    p_size, p_retailprice
  )
)
```

- CaseWhen

```
Print(
  CaseWhen(
    Scan(\"/Users/jun/src/tpch-dbgen/nation.tbl\", int n_nationkey, string n_name, int n_regionkey, string n_comment),
    n_regionkey = 3 then 1 else 0 as x
  )
)
```

## TPC-H Queries

- Q1

```
Print(
  Sort(
    Aggregate(
      Calculate(
        Filter(
          Scan(\"/Users/jun/src/tpch-dbgen/lineitem.tbl\", int l_orderkey, int l_partkey, int l_suppkey, int l_linenumber, double l_quantity, double l_extendedprice, double l_discount, double l_tax, string l_returnflag, string l_linestatus, date l_shipdate, date l_commitdate, date l_receiptdate, string l_shipinstruct, string l_shipmode, string l_comment),
          l_shipdate <= \"1998-09-02\"
        ),
        l_extendedprice*(1-l_discount) as disc_price,
        l_extendedprice*(1-l_discount)*(1+l_tax) as charge
      ),
      keys(l_returnflag, l_linestatus), sum(l_quantity), sum(l_extendedprice), sum(disc_price), sum(charge), avg(l_quantity), avg(l_extendedprice), avg(l_discount), count(*)
    ),
    l_returnflag, l_linestatus
  )
)
```

- Q1 (Preload & Exec)

```
PreloadExec(
  Scan(\"/Users/jun/src/tpch-dbgen/lineitem.tbl\", int l_orderkey, int l_partkey, int l_suppkey, int l_linenumber, double l_quantity, double l_extendedprice, double l_discount, double l_tax, string l_returnflag, string l_linestatus, date l_shipdate, date l_commitdate, date l_receiptdate, string l_shipinstruct, string l_shipmode, string l_comment) as lineitem,
  Time(Print(
  Sort(
    Aggregate(
      Calculate(
        Filter(ScanTable(lineitem), l_shipdate <= \"1998-09-02\"),
        l_extendedprice*(1-l_discount) as disc_price,
        l_extendedprice*(1-l_discount)*(1+l_tax) as charge
      ),
      keys(l_returnflag, l_linestatus), sum(l_quantity), sum(l_extendedprice), sum(disc_price), sum(charge), avg(l_quantity), avg(l_extendedprice), avg(l_discount), count(*)
    ),
    l_returnflag, l_linestatus
  )
  ))
)
```

- Q6

```
Print(
  Aggregate(
    Calculate(
      Filter(
        Scan(\"/Users/jun/src/tpch-dbgen/lineitem.tbl\", int l_orderkey, int l_partkey, int l_suppkey, int l_linenumber, double l_quantity, double l_extendedprice, double l_discount, double l_tax, string l_returnflag, string l_linestatus, date l_shipdate, date l_commitdate, date l_receiptdate, string l_shipinstruct, string l_shipmode, string l_comment),
        l_shipdate >= \"1994-01-01\"
        and l_shipdate <  \"1995-01-01\"
        and l_discount >= 0.05
        and l_discount <= 0.07
        and l_quantity < 24
      ),
      l_extendedprice*l_discount as revenue
    ),
    keys(), sum(revenue)
  )
)
```

- Q14

```
Calculate(
  Aggregate(
    CaseWhen(
      Calculate(
        HashJoin(
          Scan(\"/Users/jun/src/tpch-dbgen/part.tbl\", int p_partkey, string p_name, string p_mfgr, string p_brand, string p_type, int p_size, string p_container, double p_retailprice, string p_comment),
          Filter(
            Scan(\"/Users/jun/src/tpch-dbgen/lineitem.tbl\", int l_orderkey, int l_partkey, int l_suppkey, int l_linenumber, double l_quantity, double l_extendedprice, double l_discount, double l_tax, string l_returnflag, string l_linestatus, date l_shipdate, date l_commitdate, date l_receiptdate, string l_shipinstruct, string l_shipmode, string l_comment),
            l_shipdate >= \"1995-09-01\" and l_shipdate < \"1995-10-01\"),
          p_partkey, l_partkey
        ),
        l_extendedprice*(1-l_discount) as x
      ),
      p_type like \"PROMO%\" then x else 0 as cw
    ),
    keys(), sum(cw), sum(x)
  ),
  100*sum_cw/sum_x as promo_revenue
)
```

## リファレンス

- Ruby Y. Tahboub, Grégory M. Essertel, Tiark Rompf, "How to Architect a Query Compiler, Revisited", SIGMOD '18
