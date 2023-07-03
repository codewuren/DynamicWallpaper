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

// ���ýṹ
struct Config {
	std::string ffplayFullPath;
	std::string LastPlayedFileFullPath;
	bool AutoPlayMode = true;				// �Ƿ��Զ�������һ�β��ŵ��ļ�
};

int CreateConfigFile() {
	// TODO����ɴ��������ļ���д��Ĭ������
}