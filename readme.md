# OpenGL Learn

用于记录 OpenGL 学习。

## 环境

- 编译器：GCC 10.3.0 x86_64-w64-mingw32
- 操作系统：Windows 11 23H2
- 构建系统：Ninja
- IDE：vscode

## 配置 （VSCode）

1. 安装 C/C++ 插件。
2. 安装 CMake 插件。
3. 安装 CMake Tools 插件。
4. 安装 TDM-GCC（可选，如果希望使用）。
5. 安装 Ninja（可选，如果使用 TDM-GCC）。
6. 克隆仓库。
7. 配置 GLFW。

## 配置 GLFW

1. [下载 GLFW （二进制文件）](https://www.glfw.org/download.html)。
2. 解压 GLFW，并修改 CMakeLists 中 GLFW_DIR 的值。

## 配置 Ninja （如果使用）

1. [下载 Ninja](https://github.com/ninja-build/ninja/releases)。
2. 将 Ninja 添加到环境变量中，或者将 Ninja 的可执行文件放到 System32 目录下。
3. 重启终端/IDE。

## 注意

如果你修改了 assets 文件夹下的文件，需要手动删除 build 文件夹下的 assets 文件夹，然后重新编译。
