## Build (developer)

This uses [vcpkg](https://github.com/microsoft/vcpkg) to install the dependencies needed to build as developer:

* [Boost.Test](https://github.com/boostorg/test) (latest version) for unit testing

### Linux, MacOS

```bash
git clone git@github.com:rscherrer/speciome.git
cd speciome
cp CMakeLists_devel.txt CMakeLists.txt # developer configuration
git submodule add https://github.com/microsoft/vcpkg
git submodule update --init --remote
mkdir build && cd build
cmake ..
cmake --build .
```

Executables for tests are built in `bin/tests/`.

### Windows

```cmd
git clone git@github.com:rscherrer/speciome.git
cd speciome
copy CMakeLists_devel.txt CMakeLists.txt :: developer configuration
git submodule add https://github.com/microsoft/vcpkg
git submodule update --init --remote
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

Executables for tests are built in `bin/tests/`.

### IDEs

```bash
git clone git@github.com:rscherrer/speciome.git
cd speciome
cp CMakeLists_devel.txt CMakeLists.txt # developer configuration
git submodule update --init --recursive
mkdir build
cd build
# Generate VisualStudio project files
cmake -G "Visual Studio 17 2022" -A x64 ..
# Generate Xcode project files (Xcode must be installed)
cmake -G Xcode    
```