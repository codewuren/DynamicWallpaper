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
/// <param name="conf"></param>
void ReadConfigFile(Config* conf) {
	std::ifstream ConfigFile("config");
	std::string data;
	std::getline(ConfigFile,conf->ffplayFullPath);
	std::getline(ConfigFile, conf->AutoPlayMode);
	ConfigFile.close();
}

/// <summary>
/// 回调函数，找到第二个名为 WorkerW 的窗口并隐藏，使播放窗口可见。
/// </summary>
/// <param name="hwnd"></param>
/// <param name="Lparam"></param>
/// <returns></returns>
BOOL CALLBACK EnumWindowsProc(_In_ HWND hwnd, _In_ LPARAM Lparam)
{
	HWND hDefView = FindWindowEx(hwnd, 0, L"SHELLDLL_DefView", 0);
	if (hDefView != 0) {
		// 找到类名为 WorkerW窗口
		HWND hWorkerw = FindWindowEx(0, hwnd, L"WorkerW", 0);

		// 视频播放窗口
		HWND hFfplay = FindWindow(_T("SDL_app"), 0);

		// 移动到合适的位置
		SetWindowPos(hFfplay, NULL, 0, 0, std::stoi(Width), std::stoi(Height), SWP_SHOWWINDOW);

		// 隐藏第一个类名为 WorkerW 的窗口，使播放窗口可见
		ShowWindow(hWorkerw, SW_HIDE);

		return FALSE;
	}
	return TRUE;
}

/// <summary>
/// 播放相应文件。
/// </summary>
/// <param name="VideoPath">播放文件全路径</param>
/// <param name="Width">播放窗口长度</param>
/// <param name="Height">播放窗口宽度</param>
void Play(std::string VideoPath, std::string Width, std::string Height) {
	std::string argu = " " + VideoPath + " -noborder " +"-x " + Width + " -y " + Height + " -loop 0";
	std::cout << "指令：" << conf.ffplayFullPath << argu << std::endl;

	STARTUPINFO si{ 0 };
	PROCESS_INFORMATION pi{ 0 };

	std::wstring ffp = std::wstring(conf.ffplayFullPath.begin(), conf.ffplayFullPath.end());
	LPCWSTR Lffp = ffp.c_str();

	std::wstring w_argu = std::wstring(argu.begin(), argu.end());
	LPCWSTR Largu = w_argu.c_str();

	if (CreateProcess(Lffp, LPWSTR(Largu), 0, 0, 0, 0, 0, 0, &si, &pi)) {
		Sleep(300);
		HWND hProgman = FindWindow(L"Progman", 0);							// 找到PM窗口
		SendMessageTimeout(hProgman, 0x52C, 0, 0, 0, 100, 0);				// 给它发送 0x52C 的消息，使其分裂
		HWND hFfplay = FindWindow(L"SDL_app", 0);							// 找到视频播放窗口
		SetParent(hFfplay, hProgman);										// 将视频窗口设置为 PM 的子窗口
		EnumWindows(EnumWindowsProc, 0);									// 找到第二个 WorkerW 窗口并隐藏它
	}
	else {
		std::cout << "创建进程失败！\n";
		exit(1);
	}

	// 等待信息句柄结束，并将其关闭
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}