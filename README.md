# `string_view` Standalone

[![Ubuntu Build Status](https://github.com/bitwizeshift/string_view-standalone/workflows/Ubuntu/badge.svg?branch=master)](https://github.com/bitwizeshift/string_view-standalone/actions?query=workflow%3AUbuntu)
[![macOS Build Status](https://github.com/bitwizeshift/string_view-standalone/workflows/macOS/badge.svg?branch=master)](https://github.com/bitwizeshift/string_view-standalone/actions?query=workflow%3AmacOS)
[![Windows Build Status](https://github.com/bitwizeshift/string_view-standalone/workflows/Windows/badge.svg?branch=master)](https://github.com/bitwizeshift/string_view-standalone/actions?query=workflow%3AWindows)
[![Coverage Status](https://coveralls.io/repos/github/bitwizeshift/string_view-standalone/badge.svg?branch=master)](https://coveralls.io/github/bitwizeshift/string_view-standalone?branch=master)
[![Github Issues](https://img.shields.io/github/issues/bitwizeshift/string_view-standalone.svg)](http://github.com/bitwizeshift/string_view-standalone/issues)
<br/>
[![Github Releases](https://img.shields.io/github/release/bitwizeshift/string_view-standalone.svg)](https://github.com/bitwizeshift/string_view-standalone/releases)
[![Tested Compilers](https://img.shields.io/badge/compilers-gcc%20%7C%20clang-blue.svg)](#tested-compilers)
[![Documentation](https://img.shields.io/badge/docs-doxygen-blue.svg)](http://bitwizeshift.github.io/string_view-standalone)
[![GitHub License](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/bitwizeshift/string_view-standalone/master/LICENSE.md)

## What is `string_view` Standalone?

C++17 introduced lightweight, non-owning strings referred to as `string_view` to the standard. Unlike `std::string`, which performs memory allocations
and copies for most string operations (such as `substr`), the `string_view` only observes and does not modify the entry.
This can massively decrease the memory footprint and provide a large optimization for immutable strings for things like parsing and tokenization. As a
result, such a type can be an asset in older c++ versions for systems that may not support the newer standards.

The full type, `basic_string_view` is templated on a both `CharT` and `Traits` to allow viewing of contiguous char-like sequences of data, and for
simple conversion between `std::basic_string` and `basic_string_view`.

This library is written to be as-compatible with the c++17 spec as possible

## Rationale

C++17 is still undergoing the standardization process (although currently is considered 'feature-complete'). Although non-owning strings are available in
many other libraries, such as boost, Bloomberg STD, QT -- all of them come with rather large dependencies and have slightly different functionality and
signatures.

By releasing this library as a standalone include, it provides future-proof support to older compilers with easy accessibility.
It also allows using the newer feature-set in older versions, and facilitates easy upgrades to the new standard as compilers upgrade and newer
c++ versions become available.

## Tested Compilers

The following compilers are currently being tested through continuous integration with [Travis](https://travis-ci.org/bitwizeshift/string_view-standalone).

Note that `bpstd::string_view` only works on compiler that provide proper conformance for c++11, meaning this
does not properly work on g++ before 4.8

| Compiler              | Operating System                   |
|-----------------------|------------------------------------|
| g++ 4.9.3             | Ubuntu 14.04.3 TLS                 |
| g++ 5.3.0             | Ubuntu 14.04.3 TLS                 |
| g++ 6.1.1             | Ubuntu 14.04.3 TLS                 |
| clang 3.5.0           | Ubuntu 14.04.3 TLS                 |
| clang 3.6.2           | Ubuntu 14.04.3 TLS                 |
| clang 3.8.0           | Ubuntu 14.04.3 TLS                 |
| clang xcode 6.0       | Darwin Kernel 13.4.0 (OSX 10.9.5)  |
| clang xcode 6.1       | Darwin Kernel 14.3.0 (OSX 10.10.3) |
| clang xcode 7.0       | Darwin Kernel 14.5.0 (OSX 10.10.5) |
| clang xcode 7.3       | Darwin Kernel 15.5.0 (OSX 10.11.5) |
| clang xcode 8.0       | Darwin Kernel 15.6.0 (OSX 10.11.6) |
| Visual Studio 14 2015	| Windows Server 2012 R2 (x64)       |

## License

<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

The class is licensed under the [MIT License](http://opensource.org/licenses/MIT):

> Copyright &copy; 2016-2021 [Matthew Rodusek](http://bitwizeshift.github.com/)
>
> Permission is hereby granted, free of charge, to any person obtaining a copy
> of this software and associated documentation files (the "Software"), to deal
> in the Software without restriction, including without limitation the rights
> to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
> copies of the Software, and to permit persons to whom the Software is
> furnished to do so, subject to the following conditions:
>
> The above copyright notice and this permission notice shall be included in all
> copies or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
> IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
> FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
> AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
> LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
> OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
> SOFTWARE.

## References

- [`basic_string_view` on cpp-reference](http://en.cppreference.com/w/cpp/string/basic_string_view)
