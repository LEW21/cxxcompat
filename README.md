cxxcompat
=========

C++ compatibility header-only library. Implements as much of C++11/14 as is possible without compiler help.

Implemented C++ version
-----------------------
The plan is to always implement the latest working draft of C++. Currently, this is [N3690](http://isocpp.org/files/papers/N3690.pdf) - C++14 committee draft from 2013-05-15.

Supported compilers
-------------------
- clang 3.2+ (3.0+?) (with libc++ or libstdc++ 4.6+)
- gcc 4.6+

The long-term plan is to always support the default compiler of all supported Fedora and openSUSE versions, and latest Ubuntu LTS and Debian stable that was released at least half a year ago. This gives approximately:
- gcc 4.6.3 - until 10.2014 (Ubuntu 12.04 LTS)
- gcc 4.7.2 - until 10.2015 (Debian 7.0)
- gcc 4.8.x - until 10.2016?

This currently means that we support each gcc version for ~3,5 years.

Other compilers should be supported in their latest version, and, if this isn't a big burden, older ones too - still, NOT older than the versions in the distributions listed above.

How to use?
-----------
Probably the easiest way to use it is to add an git submodule to your project, and then add -Icxxcompat/include to the CXXFLAGS.

How to build tests?
-------------------
	mkdir build
	cd build
	cmake ..
	make
	make test

If you want to test under another compiler, simply remove your `build` directory,
	export CXX=/usr/bin/compiler-binary
and follow listed steps once more.
