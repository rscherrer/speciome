## Build (developer)

We use [vcpkg](https://github.com/microsoft/vcpkg) to install the dependencies needed to build as developer:

* [Boost.Test](https://github.com/boostorg/test) (latest version)

### Linux, MacOS

```bash
git clone git@github.com:rscherrer/speciome.git
cd speciome
git submodule add https://github.com/microsoft/vcpkg
git submodule update --init --remote
mkdir build && cd build
cmake ..
cmake --build .
```

### Windows

```cmd
git clone git@github.com:rscherrer/speciome.git
cd speciome
git submodule add https://github.com/microsoft/vcpkg
git submodule update --init --remote
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### IDEs

```bash
git clone git@github.com:rscherrer/speciome.git
cd speciome
git submodule update --init --recursive
mkdir build
cd build
# Generate VisualStudio project files
cmake -G "Visual Studio 17 2022" -A x64 ..
# Generate Xcode project files (Xcode must be installed)
cmake -G Xcode    
```