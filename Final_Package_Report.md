# Scope #
This scope of this document lists the finalized features included in final Trucov release, the future features planned, the functional testing summary, and the unit test summary per source file that was unit tested.

# Missing / Incomplete Features #

## [Issue 124](https://code.google.com/p/trucov/issues/detail?id=124) ##
Generate report and graphs at the same time, using a command accumulation system. As of now, one command may only be invoked each time. The solution involves adding a --add-command option, where multiple commands may be specified.

## [Issue 131](https://code.google.com/p/trucov/issues/detail?id=131) ##
Add cache file. The flag is "--cache-file", and a cache file system will export the Parser data structure to a file. When a cache file is to be used, Trucov will skip all parsing of the gcno and gcda files, and build a data structure directly from the file, and continue with the selected command.

## [Issue 138](https://code.google.com/p/trucov/issues/detail?id=138) ##
Add objective c support. This requires function names to not be demangled by c++filt and objective c file extensions must be added when searching for source files.

## [Issue 139](https://code.google.com/p/trucov/issues/detail?id=139) ##
Add java support. GCC can compile java; this requires function names to not be demangled by c++filt and java file extensions must be added when searching for source files.

## [Issue 154](https://code.google.com/p/trucov/issues/detail?id=154) ##
Trucov will not compile with newer versions of Boosts. This is a result of deprecated libraries of spirit. Trucov will need to have "classic" includes to compile with the new versions of boost spirit; e.g. include "classic\_parser.hpp" instead of "parser.hpp".

# Testing #
Testing is split up into functional tests, and unit tests.

## Functional ##
All functional test pass. Functional tests check Trucov commands, selection, option flags, and the config file with command line options. All functional tests invoke the Trucov command line tool.

## Unit Test ##

|89% Total|| | |
|:--------|:|:|:|
|Source File|Unit Test|Percentage|Notes|
|command.h|command\_unittest.cpp|100%|None|
|command.cpp|command\_unittest.cpp|68%|None|
|config.cpp|config\_unittest.cpp|79%|Boost and compiler generated functions bring coverage below 90%.|
|coverage\_creator.h|coverage\_creator\_unittest.cpp|100%|None|
|coverage\_creator.cpp|coverage\_creator\_unittest.cpp|75%|Needs to run over a program with inlined data for additional coverage.|
|dot\_creator.h|dot\_creator\_unittest.cpp|100%|None|
|dot\_creator.cpp|dot\_creator\_unittest.cpp|78%|Needs to run over a program with inlined data for additional coverage.|
|gcda\_actors.h|gcda\_actors\_unittest.cpp|100%|None|
|gcda\_grammar.h|gcda\_grammar\_unittest.cpp|100%|None|
|gcno\_actors.h|gcno\_actors\_unittest.cpp|100%|None|
|gcno\_grammar.h|gcno\_grammar\_unittest.cpp|100%|None|
|parser.h |parser\_unittest.cpp|100%|None|
|parser.cpp|parser\_unittest.cpp|80%|None|
|parser\_builder.h|parser\_builder\_unittest.cpp|100%|None|
|parser\_builder.cpp|parser\_builder\_unittest.cpp|78%|A compiler generated constructor and the static initialization function bring the percentage below 90%.|
|prims.h  |prims\_unittest.cpp|85%|Missing coverage on compiler generated template overloads.|
|record.h |record\_unittest.cpp|100%|None|
|record.cpp|record\_unittest.cpp|98%|None|
|source\_file.h|source\_file\_unittest.cpp|100%|None|
|revision\_script\_manager.cpp|revision\_script\_manager\_unittest.cpp|69%|A compiler generated constructor, destructor, and the static initialization function prevents full coverage.|
|selector.cpp|selector\_unittest.cpp|83%|A compiler generated constructor and the static initialization function prevents full coverage.|
|tru\_utility.cpp|tru\_utility\_unittest.cpp|67%|None|