// �ļ���DynamicWallpaper.hpp
// ���ߣ�CodeWuRen


#pragma once
#include <iostream>							// ��׼I/O��
#include <Windows.h>						// Windows API
#include <string>							// �ַ���
#include <vector>							// Vector����
#include <fstream>							// �ļ�I/O��
#include <tchar.h>

// ����
std::string FilePath;                       // Ŀ���ļ�ȫ·��
std::string Width;                          // ���Ŵ��ڳ���
std::string Height;                         // ���Ŵ��ڿ��
std::vector <std::string> Arguments;		// �����ó���Ĳ���
std::string LastPlayedFileFullPath;			// ������һ�β����ļ���ȫ·��

// ���ýṹ
struct Config {
	std::string ffplayFullPath;				// ffplay ��ȫ·��
	std::string AutoPlayMode = "true";		// �Ƿ��Զ�������һ�β��ŵ��ļ�
}conf;

/// <summary>
/// �����µ������ļ����������û����� ffplay ��ȫ·�������д��Ĭ������
/// </summary>
void CreateConfigFile(Config* conf) {
	std::ofstream NewConfigFile("config");

	// ��ȡ ffplay ��ȫ·��
	if (conf->ffplayFullPath == "") {
		std::cout << "Please input the full path of your ffplay!\n";
		std::cin >> conf->ffplayFullPath;
	}

	// д��Ĭ�����ò��ر��ļ������
	NewConfigFile << conf->ffplayFullPath << std::endl;
	NewConfigFile << conf->AutoPlayMode << std::endl;
	NewConfigFile.close();
}

/// <summary>
/// �������ļ��ж�ȡ���ò���ֵ�� conf �е�Ԫ��
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
/// �ص��������ҵ��ڶ�����Ϊ WorkerW �Ĵ��ڲ����أ�ʹ���Ŵ��ڿɼ���
/// </summary>
/// <param name="hwnd"></param>
/// <param name="Lparam"></param>
/// <returns></returns>
BOOL CALLBACK EnumWindowsProc(_In_ HWND hwnd, _In_ LPARAM Lparam)
{
	HWND hDefView = FindWindowEx(hwnd, 0, L"SHELLDLL_DefView", 0);
	if (hDefView != 0) {
		// �ҵ�����Ϊ WorkerW����
		HWND hWorkerw = FindWindowEx(0, hwnd, L"WorkerW", 0);

		// ��Ƶ���Ŵ���
		HWND hFfplay = FindWindow(_T("SDL_app"), 0);

		// �ƶ������ʵ�λ��
		SetWindowPos(hFfplay, NULL, 0, 0, std::stoi(Width), std::stoi(Height), SWP_SHOWWINDOW);

		// ���ص�һ������Ϊ WorkerW �Ĵ��ڣ�ʹ���Ŵ��ڿɼ�
		ShowWindow(hWorkerw, SW_HIDE);

		return FALSE;
	}
	return TRUE;
}

/// <summary>
/// ������Ӧ�ļ���
/// </summary>
/// <param name="VideoPath">�����ļ�ȫ·��</param>
/// <param name="Width">���Ŵ��ڳ���</param>
/// <param name="Height">���Ŵ��ڿ��</param>
void Play(std::string VideoPath, std::string Width, std::string Height) {
	std::string argu = " " + VideoPath + " -noborder " +"-x " + Width + " -y " + Height + " -loop 0";
	std::cout << "ָ�" << conf.ffplayFullPath << argu << std::endl;

	STARTUPINFO si{ 0 };
	PROCESS_INFORMATION pi{ 0 };

	std::wstring ffp = std::wstring(conf.ffplayFullPath.begin(), conf.ffplayFullPath.end());
	LPCWSTR Lffp = ffp.c_str();

	std::wstring w_argu = std::wstring(argu.begin(), argu.end());
	LPCWSTR Largu = w_argu.c_str();

	if (CreateProcess(Lffp, LPWSTR(Largu), 0, 0, 0, 0, 0, 0, &si, &pi)) {
		Sleep(300);
		HWND hProgman = FindWindow(L"Progman", 0);							// �ҵ�PM����
		SendMessageTimeout(hProgman, 0x52C, 0, 0, 0, 100, 0);				// �������� 0x52C ����Ϣ��ʹ�����
		HWND hFfplay = FindWindow(L"SDL_app", 0);							// �ҵ���Ƶ���Ŵ���
		SetParent(hFfplay, hProgman);										// ����Ƶ��������Ϊ PM ���Ӵ���
		EnumWindows(EnumWindowsProc, 0);									// �ҵ��ڶ��� WorkerW ���ڲ�������
	}
	else {
		std::cout << "��������ʧ�ܣ�\n";
		exit(1);
	}

	// �ȴ���Ϣ���������������ر�
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}