from conans import ConanFile, CMake

class LibjwtppConan(ConanFile):
    name = 'libjwtpp'
    version= 'master'
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    requires = "libjwt/master@rdeterre/stable"
    url = "https://github.com/rdeterre/libjwtpp"
    license = "LGPLv2.1"
    exports = "*"

    def build(self):
        cmake = CMake(self.settings)
        self.run('cmake "{}" {}'.format(self.conanfile_directory, cmake.command_line))
        self.run('cmake --build . {}'.format(cmake.build_config))

    def package(self):
        self.copy("jwt.hpp", dst='include/libjwtpp', src='include')
        self.copy("*.so", dst="lib", src=".")

    def package_info(self):
        self.cpp_info.libs = ["jwtpp"]
        self.cpp_info.includedirs = ['include']
