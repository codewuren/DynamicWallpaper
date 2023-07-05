// 文件：DynamicWallpaper.hpp
// 作者：CodeWuRen


#pragma once
#include <iostream>							// 标准I/O库
#include <Windows.h>						// Windows API
#include <string>							// 字符串
#include <vector>							// Vector容器
#include <fstream>							// 文件I/O库
#include <tchar.h>

// 变量
std::string FilePath;                       // 目标文件全路径
std::string Width;                          // 播放窗口长度
std::string Height;                         // 播放窗口宽度
std::vector <std::string> Arguments;		// 传给该程序的参数
std::string LastPlayedFileFullPath;			// 保存上一次播放文件的全路径

// 配置结构
struct Config {
	std::string ffplayFullPath;				// ffplay 的全路径
	std::string AutoPlayMode = "true";		// 是否自动播放上一次播放的文件
}conf;

/// <summary>
/// 创建新的配置文件，并提醒用户输入 ffplay 的全路径，最后写入默认配置
/// </summary>
void CreateConfigFile(Config* conf);

/// <summary>
/// 从配置文件中读取配置并赋值给 conf 中的元素
/// </summary>
/// <param name="conf"></param>
void ReadConfigFile(Config* conf);

/// <summary>
/// 回调函数，找到第二个名为 WorkerW 的窗口并隐藏，使播放窗口可见。
/// </summary>
/// <param name="hwnd"></param>
/// <param name="Lparam"></param>
/// <returns></returns>
BOOL CALLBACK EnumWindowsProc(_In_ HWND hwnd, _In_ LPARAM Lparam);
/// <summary>
/// 播放相应文件。
/// </summary>
/// <param name="VideoPath">播放文件全路径</param>
/// <param name="Width">播放窗口长度</param>
/// <param name="Height">播放窗口宽度</param>
void Play(std::string VideoPath, std::string Width, std::string Height);