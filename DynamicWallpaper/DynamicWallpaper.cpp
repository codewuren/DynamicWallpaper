// 文件：DynamicWallpaper.cpp
// 作者：CodeWuRen


// 头文件
#include <iostream>                 // 标准I/O库
#include <Windows.h>                // Windows API
#include <string>                   // 字符串
#include <vector>                   // Vector容器
#include "DynamicWallpaper.hpp"     // 必需的变量


/// <summary>
/// 主函数
/// </summary>
int main(int argc, char** argv) {
    // 将所有参数放入Vector容器中，char** 中的元素无法直接与 char* 比较。
    for (int i = 1; i < argc; i++) {
        Arguments.push_back(argv[i]);
    }

    // 比较 Arguments 容器中的所有元素，获得 FilePath, Width, Height 的值。
    for (int i = 0; i < argc - 1; i++) {
        if (Arguments[i] == "-f") {
            FilePath = Arguments[i + 1];
        }
        else if (Arguments[i] == "-x") {
            Width = Arguments[i + 1];
        }
        else if (Arguments[i] == "-y") {
            Height = Arguments[i + 1];
        }
    }

    // 输出相应参数值
    std::cout << "FilePath: " << FilePath << "\n" << "Width: " << Width << "\n" << "Height: " << Height << "\n";
    return 0;
}

