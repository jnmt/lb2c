name := "lb2c"

version := "0.1"

scalaVersion := "2.12.8"

resolvers += Resolver.sonatypeRepo("snapshots")

libraryDependencies += "org.scala-lang.virtualized" % "lms-clean_2.12" % "0.0.1-SNAPSHOT" // local

libraryDependencies += "org.scala-lang" % "scala-compiler" % scalaVersion.value % "compile"
libraryDependencies += "org.scala-lang" % "scala-library" % scalaVersion.value % "compile"
libraryDependencies += "org.scala-lang" % "scala-reflect" % scalaVersion.value % "compile"

libraryDependencies += "org.scala-lang.modules" %% "scala-parser-combinators" % "1.1.2"

autoCompilerPlugins := true
val paradiseVersion = "2.1.0"
addCompilerPlugin("org.scalamacros" % "paradise" % paradiseVersion cross CrossVersion.full)
