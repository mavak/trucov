# Current Release Version #
10.1

# Introduction #
Trucov is an open source program that works with the GCC compiler to display the control flow of a program and its test coverage information. It assists developers to ensure their test cases have sufficient coverage.
Trucov simplifies and formalizes the way in which developers identify untested code in a simple to identify, visual way. Similar to Gcov, but better.

# Problem Statement #
If someone were to write a unit test with the goal of 90% coverage over the code, how is this 90% coverage verified? Not reaching test coverage goals can result in occurrences of untested code and may lead to error-prone software. Engineers need a standardized way to check the test coverage of functions, source files, and programs. This standardized process is Trucov.

# Key Features #

## Coverage Analysis ##
Trucov detects how many times any particular block, arc, or branch of code has been executed.

## Coverage Reports ##
```
   66% dog::bark(const string &) (3/6) branches
       path_name/dog.cpp:10: 2/4 branches: 11
          path_name/dog.cpp:14: destination: 15
          path_name/dog.cpp:23: destination: 15
       path_name/dog.cpp:25: 1/2 branches: 28
          path_name/dog.cpp:29: destination: 32
  100% dog::wagtail() (2/2) branches
```

## Coverage Graphs ##
Trucov can produce coverage graphs for any function.

![http://trucov.googlecode.com/hg/docs/web/switch.png](http://trucov.googlecode.com/hg/docs/web/switch.png)

## Command Line Tool ##
Trucov is available as a command line tool for more advanced users.
```
   $$ trucov report -s ../src/ -s ../include/ -b ../build/
   parsing gnco and gcda files.....
```

## GUI Tool (In development) ##
Trucov offers an easy to use GUI tool.

## Limitations ##
Programs must be compiled using GCC version 4 and above, therefore Trucov is restricted to working with C and C++ source code. The Trucov source code is licensed under the open source MIT License and all its restrictions apply.