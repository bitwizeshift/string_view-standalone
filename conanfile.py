#!/usr/bin/env python3

from conans import ConanFile, CMake

class StringViewStandaloneConan(ConanFile):

  # Package Info
  name = "StringViewStandalone"
  version = "1.0.0"
  description = "Modern C++ compatible string_view implementation"
  url = "https://github.com/bitwizeshift/string_view-standalone"
  author = "Matthew Rodusek <matthew.rodusek@gmail.com>"
  license = "MIT"
  generators = "cmake"

  # Sources
  exports = ("LICENSE")
  exports_sources = ("cmake/*",
                     "include/*",
                     "single_include/*",
                     "tests/*",
                     "CMakeLists.txt",
                     "LICENSE")

  # Settings
  options = {}
  default_options = {}
  build_requires = ("Catch2/2.7.1@catchorg/stable")

  def source(self):
    pass

  def build(self):
    pass

  def test(self):
    pass

  def package(self):
    cmake = CMake(self)
    cmake.definitions["BPSTD_COMPILE_UNIT_TESTS"] = "ON"
    cmake.configure()

    # Compile and run the unit tests
    cmake.build()
    cmake.build(target="test")

    cmake.install()

    self.copy(pattern="LICENSE", dst="licenses")
    return

  def package_id(self):
    # self.info.header_only()
    return