# Fewo-Blacklist [![Build Status](https://travis-ci.org/freefallcid/Fewo-Blacklist.svg?branch=master)](https://travis-ci.org/freefallcid/Fewo-Blacklist) [![Build Status](https://travis-ci.org/freefallcid/Fewo-Blacklist.svg?branch=sqlite)](https://travis-ci.org/freefallcid/Fewo-Blacklist)

A simple command line tool to manage a blacklist.
The following two files need to exist in the (actual) working directory.

* `daten.txt` - can be empty
* `counter.txt` - write a single zero (`0`) into the first line

**You can also create those files with `make reset`.**

## For example

### Put the files into your home directory

You can run the tool in your home directory.
It does not care where the binary file is, as long as you are in your home directory.

### Put the files into a separate directory under your home directory

If you put the two files into `.fewo` in your home directory, you have to go into that directory first and run the command then.
It does not care where the binary file is, as long as you are in that specific directory.

### Change the source code to use absolute paths

Open main.cpp and re-define the filename of those two files (that information is on line 80 and 81).

``` C++
  const char * cFilename = "daten.txt";
  const char * cCounter  = "counter.txt";
```

You can easily change this to something else and compile again.

``` C++
  const char * cFilename = "/var/lib/blacklist/daten.txt";
  const char * cCounter  = "/var/lib/blacklist/counter.txt";
```

## Others

Feedback and suggenstions welcome!
