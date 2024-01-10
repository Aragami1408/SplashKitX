
<br/>
<p align="center">
  <h2 align="center">SplashKitX</h3>

  <p align="center">
    Vulkan 3D Game engine with SplashKit API design in mind
    <br/>
    <br/>
  </p>
</p>

![Downloads](https://img.shields.io/github/downloads/Aragami1408/SplashKitX/total) ![Contributors](https://img.shields.io/github/contributors/Aragami1408/SplashKitX?color=dark-green) ![Forks](https://img.shields.io/github/forks/Aragami1408/SplashKitX?style=social) ![Stargazers](https://img.shields.io/github/stars/Aragami1408/SplashKitX?style=social) ![Issues](https://img.shields.io/github/issues/Aragami1408/SplashKitX) ![License](https://img.shields.io/github/license/Aragami1408/SplashKitX)

## Table Of Contents

* [About the Project](#about-the-project)
* [Built With](#built-with)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Contributing](#contributing)
* [License](#license)

## About The Project

SplashKitX is a 2D/3D Game Engine written in C++ and Vulkan Graphics API. This game engine is pretty much experimental and currently not ready for production yet. Furthermore, this game engine is deeply inspired by [Kohi Game Engine](https://kohiengine.com/) and [SplashKit](https://splashkit.io/)

## Built With

This game engine is purely built by using Vulkan Graphics API. Platform layer for Windows and Linux are built by Win32 API and XCB/Xlib respectively.

## Getting Started

Before you ask, I **will never use** Visual Studio or any kinds of build systems (CMake, Meson, .etc). Visual Studio makes it really hard to migrate to other platforms (not to mention the dynamically linked architecture). As for build systems, they are awesome for cross-platform compilation, but utterly dogwater for Windows. However, using build scripts doesn't require any further installation, **you'll just need to run it directly from the command line!**

### Prerequisites

- [Clang](https://clang.llvm.org/) and [Vulkan SDK](https://vulkan.lunarg.com/sdk/home) is required. [Git](https://git-scm.com/) is recommended to clone this project
- For Windows Users: [Visual Studio Build Tools](https://visualstudio.microsoft.com/downloads/?q=build+tools#build-tools-for-visual-studio-2022)(Only if you don't have full Visual Studio Installation)
- For Linux Users: `libx11-dev`, `libxkbcommon-x11-dev` and `libx11-xcb-dev` are required
- For macOS Users: Currently macOS doesn't have a platform layer yet, but you can use [XQuartz](https://www.xquartz.org/) to install X11 and XCB dependencies (Trust me, it works on my MacBook).

### Installation

1. Clone the repo

```sh
git clone https://github.com/Aragami1408/SplashKitX.git
```

2. Build the engine and run the test program
- Linux/MacOS:
```sh
$ cd SplashKitX
$ chmod +x ./build-all.sh && ./build-all.sh
$ cd bin && ./SKXTest
```
- Windows:
```
$ cd SplashKitX
$ build-all
$ cd bin
$ SKXTest.exe
```

## Contributing

I am open to contributions from anyone who wants to improve this project. If you want to contribute, please follow the steps below:
* If you have suggestions for adding or removing projects, feel free to [open an issue](https://github.com/Aragami1408/SplashKitX/issues/new) to discuss it, or directly create a pull request after you edit the *README.md* file with necessary changes.
* Please make sure you check your spelling and grammar.
* Create individual PR for each suggestion.

### Creating A Pull Request

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

SplashKitX Game Engine is licensed by GPLv2. See `LICENSE` for more information.
