// 文件：DynamicWallpaper.hpp
// 作者：CodeWuRen


#pragma once
#include <iostream>							// 标准I/O库
#include <Windows.h>						// Windows API
#include <string>							// 字符串
#include <vector>							// Vector容器
#include <fstream>							// 文件I/O库

// 变量
std::string FilePath;                       // 目标文件全路径
std::string Width;                          // 播放窗口长度
std::string Height;                         // 播放窗口宽度
std::vector <std::string> Arguments;		// 传给该程序的参数
std::string LastPlayedFileFullPath;			// 保存上一次播放文件的全路径

// 配置结构
struct Config {
	std::string ffplayFullPath;				// ffplay 的全路径
	std::string AutoPlayMode = "true";				// 是否自动播放上一次播放的文件
}conf;

/// <summary>
/// 创建新的配置文件，并提醒用户输入 ffplay 的全路径，最后写入默认配置
/// </summary>
void CreateConfigFile(Config* conf) {
	std::ofstream NewConfigFile("config");

	// 获取 ffplay 的全路径
	if (conf->ffplayFullPath == "") {
		std::cout << "Please input the full path of your ffplay!\n";
		std::cin >> conf->ffplayFullPath;
	}

	// 写入默认配置并关闭文件输出流
	NewConfigFile << conf->ffplayFullPath << std::endl;
	NewConfigFile << conf->AutoPlayMode << std::endl;
	NewConfigFile.close();
}

/// <summary>
/// 从配置文件中读取配置并赋值给 conf 中的元素
/// </summary>
void ReadConfigFile(Config* conf) {
	std::ifstream ConfigFile("config");
	// TODO：从配置文件中获取相关配置，并赋值给 conf 中的元素
	std::string data;
	std::getline(ConfigFile,conf->ffplayFullPath);
	std::getline(ConfigFile, conf->AutoPlayMode);
	ConfigFile.close();
}