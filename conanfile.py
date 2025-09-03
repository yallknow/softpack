from conan import ConanFile


class ExampleRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("boost/1.88.0")
        self.requires("box2d/3.1.0")
        self.requires("imgui/1.91.8-docking", override=True)
        self.requires("imgui-sfml/2.6.1")
