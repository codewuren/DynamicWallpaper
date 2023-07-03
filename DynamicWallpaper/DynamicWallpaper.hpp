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

// 配置结构
struct Config {
	std::string ffplayFullPath;
	std::string LastPlayedFileFullPath;
	bool AutoPlayMode = true;				// 是否自动播放上一次播放的文件
};

int CreateConfigFile() {
	// TODO：完成创建配置文件并写入默认配置
}