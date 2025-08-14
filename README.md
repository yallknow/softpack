# softpack

How to start:
1. **`python -m pip install --upgrade pip conan`**
2. **`conan profile detect`**
3.
  - Debug:
    - **`conan install . --output-folder build -s compiler.cppstd=23 -s build_type=Debug --update --build=missing`**
  - Release:
    - **`conan install . --output-folder build -s compiler.cppstd=23 -s build_type=Release --update --build=missing`**
4. **`cmake -S . -B build`**
