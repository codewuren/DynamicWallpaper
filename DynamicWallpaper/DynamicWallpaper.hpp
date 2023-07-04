// �ļ���DynamicWallpaper.hpp
// ���ߣ�CodeWuRen


#pragma once
#include <iostream>							// ��׼I/O��
#include <Windows.h>						// Windows API
#include <string>							// �ַ���
#include <vector>							// Vector����
#include <fstream>							// �ļ�I/O��

// ����
std::string FilePath;                       // Ŀ���ļ�ȫ·��
std::string Width;                          // ���Ŵ��ڳ���
std::string Height;                         // ���Ŵ��ڿ��
std::vector <std::string> Arguments;		// �����ó���Ĳ���
std::string LastPlayedFileFullPath;			// ������һ�β����ļ���ȫ·��

// ���ýṹ
struct Config {
	std::string ffplayFullPath;				// ffplay ��ȫ·��
	std::string AutoPlayMode = "true";				// �Ƿ��Զ�������һ�β��ŵ��ļ�
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
void ReadConfigFile(Config* conf) {
	std::ifstream ConfigFile("config");
	// TODO���������ļ��л�ȡ������ã�����ֵ�� conf �е�Ԫ��
	std::string data;
	std::getline(ConfigFile,conf->ffplayFullPath);
	std::getline(ConfigFile, conf->AutoPlayMode);
	ConfigFile.close();
}