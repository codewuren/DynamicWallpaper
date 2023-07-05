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
void CreateConfigFile(Config* conf);

/// <summary>
/// �������ļ��ж�ȡ���ò���ֵ�� conf �е�Ԫ��
/// </summary>
/// <param name="conf"></param>
void ReadConfigFile(Config* conf);

/// <summary>
/// �ص��������ҵ��ڶ�����Ϊ WorkerW �Ĵ��ڲ����أ�ʹ���Ŵ��ڿɼ���
/// </summary>
/// <param name="hwnd"></param>
/// <param name="Lparam"></param>
/// <returns></returns>
BOOL CALLBACK EnumWindowsProc(_In_ HWND hwnd, _In_ LPARAM Lparam);
/// <summary>
/// ������Ӧ�ļ���
/// </summary>
/// <param name="VideoPath">�����ļ�ȫ·��</param>
/// <param name="Width">���Ŵ��ڳ���</param>
/// <param name="Height">���Ŵ��ڿ��</param>
void Play(std::string VideoPath, std::string Width, std::string Height);