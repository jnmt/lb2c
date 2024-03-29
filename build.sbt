name := "lb2c"

version := "0.1"

scalaVersion := "2.11.2"

scalaOrganization := "org.scala-lang.virtualized"

resolvers += Resolver.sonatypeRepo("snapshots")

//libraryDependencies += "org.scala-lang.lms" %% "lms-core" % "0.9.1-SNAPSHOT" // TODO: How can we use latest one (flare_develop branch)?
libraryDependencies += "org.scala-lang.lms" %% "lms-core" % "1.0.0-SNAPSHOT"

libraryDependencies += "org.scala-lang.virtualized" % "scala-compiler" % "2.11.2"
libraryDependencies += "org.scala-lang.virtualized" % "scala-library" % "2.11.2"
libraryDependencies += "org.scala-lang.virtualized" % "scala-reflect" % "2.11.2"

libraryDependencies += "org.scalatest" % "scalatest_2.11" % "2.2.2"

scalacOptions += "-Yvirtualize"
scalacOptions += "-deprecation"
