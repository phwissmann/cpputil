from conans import ConanFile, CMake, tools


class CpputilConan(ConanFile):
    name = "cpputil"
    version = "0.1"
    license = "MIT License"
    author = "Philipp Wissmann"
    url = "https://github.com/phwissmann/cpputil"
    description = "C++ Development Utilities"
    topics = ("Utilities")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    generators = "cmake"
    requires = "gtest/1.8.1"
    build_policy = "missing"
    exports_sources = "include/*"
    no_copy_source = True

    def source(self):
        self.run("git clone https://github.com/phwissmann/cpputil")

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="cpputil")
        cmake.build()
        cmake.test()


    def package(self):
        self.copy("*.h", dst="include/cpputil", src="cpputil/src")

    def package_id(self):
        self.info.header_only()

