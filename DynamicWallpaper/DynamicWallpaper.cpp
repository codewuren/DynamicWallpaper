#include <iostream>     // 标准I/O库
#include <Windows.h>    // Windows API
#include <string>       // 字符串
#include <vector>       // Vector容器


/// <summary>
/// 主函数
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
int main(int argc, char** argv) {
    std::string FilePath;                       // 目标文件全路径
    std::string Width;                          // 播放窗口长度
    std::string Height;                         // 播放窗口宽度
    std::vector < std::string> Arguments;       // 传给该程序的参数

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
    std::cout << "FilePath: " << FilePath << "\n" << "Width: " << Width << "\n" << "Height: " << Height << "\n";
    return 0;
}

