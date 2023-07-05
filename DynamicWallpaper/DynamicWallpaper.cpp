// 文件：DynamicWallpaper.cpp
// 作者：CodeWuRen


// 头文件
#include "DynamicWallpaper.hpp"


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

    // 检测程序调用是否正确
    if (FilePath == "" || Width == "" || Height == "") {
        std::cout << "程序调用错误！\n";
        exit(1);
    }

    // 检测配置文件是否存在
    std::ifstream Check("config");
    if (!Check.good()) {
        std::cout << "Config file didn't exist!\nWe will create a new config file for you!\n";
        // TODO: 创建一个新的配置文件写入本地，同时文件中需含有默认配置。
        Config NewConf;
        CreateConfigFile(&NewConf);
    }

    // 读取配置
    ReadConfigFile(&conf);

    // 输出配置
    std::cout << conf.ffplayFullPath << std::endl << conf.AutoPlayMode << std::endl;

    // 播放
    Play(FilePath, Width, Height);

    // 输出相应参数值
    std::cout << "FilePath: " << FilePath << "\n" << "Width: " << Width << "\n" << "Height: " << Height << "\n";
    return 0;
}

