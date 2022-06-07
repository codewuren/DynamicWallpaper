#include <windows.h>
#include <iostream>
#include <io.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <tchar.h>

std::string GetProgramDir() {   
    char exeFullPath[MAX_PATH]; // Full path
    std::string strPath = "";
    GetModuleFileName(NULL, LPSTR(exeFullPath), MAX_PATH);
    strPath = exeFullPath;    // Get full path of the file
    int pos = strPath.find_last_of('\\', strPath.length());
    return strPath.substr(0, pos);  // Return the directory without the file name
}   

// Get files which has the specified format
void GetAllFormatFiles(std::string path, std::vector<std::string>& files, std::string format) {  
	// File handle
	long hFile = 0;  
	// File information 
	struct _finddata_t fileinfo;  
	std::string p;
	// If has this kind of file
	if((hFile = _findfirst(p.assign(path).append("\\*" + format).c_str(), &fileinfo)) !=  -1) {  
		do {
			// Is a folder 
			if ((fileinfo.attrib &  _A_SUBDIR)) {  
				if (strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0) {
					GetAllFormatFiles(p.assign(path).append("\\").append(fileinfo.name), files,format); 
				}
			}
			else files.push_back(p.assign("\\videos").append("\\").append(fileinfo.name) );  
		}while (_findnext(hFile, &fileinfo) == 0);  
 
		_findclose(hFile); 
	} 
} 


BOOL CALLBACK EnumWindowsProc(_In_ HWND hwnd, _In_ LPARAM Lparam) {
	HWND hDefView = FindWindowEx(hwnd, 0, _T("SHELLDLL_DefView"), 0);
	if (hDefView != 0) {
		// Find the next window which's class name is WorkerW
		HWND hWorkerw = FindWindowEx(0, hwnd, _T("WorkerW"), 0);
		HWND hFfplay = FindWindow(_T("SDL_app"), 0); // Video window
		SetWindowPos(hFfplay, NULL, 0, 0, 2560, 1440, SWP_SHOWWINDOW); // Move to a suitable position
		SetParent(hFfplay, hWorkerw);
		return FALSE;	
	}
	return TRUE;
}

void BeforeExit() {
	std::string FileDir = GetProgramDir();
	STARTUPINFO si { sizeof(si) }; 
	PROCESS_INFORMATION pi{ 0 };
	if (CreateProcess(LPSTR((FileDir + "\\refreshWallpaper.exe").c_str()), NULL, 0, 0, 0, 0, 0, 0, &si, &pi)) {
		std::cout << std::endl << "Create process successfully" << std::endl;
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle ( pi.hProcess );
    CloseHandle ( pi.hThread );
}

void PlayVideo(std::string FileDir, LPWSTR lpParameter) {
	STARTUPINFO si { sizeof(si) }; 
	PROCESS_INFORMATION pi{ 0 };
    if (CreateProcess(LPSTR((FileDir + "\\ffplay.exe").c_str()), LPSTR(lpParameter), 0, 0, 0, 0, 0, 0, &si, &pi)) {
		Sleep(200);
		HWND hProgman = FindWindow(_T("Progman"), 0); // Find the PM window
		SendMessageTimeout(hProgman, 0x52C, 0, 0, 0, 100, 0); // Send message
		EnumWindows(EnumWindowsProc, 0); // Set video window to PM window's Subwindow
	}
	WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle ( pi.hProcess );
    CloseHandle ( pi.hThread );
}

int main() {
	atexit (BeforeExit);
	std::cout << "Input screen size(like 1280 720): ";
	std::string sw, sh;
	std::cin >> sw >> sh;
    std::vector<std::string> Files;
    std::string FilePath = ".\\videos";
    std::string FileFormat = ".mp4";
	std::string FileDir = GetProgramDir();
    GetAllFormatFiles(FilePath, Files, FileFormat);
	std::cout << "Numbers\t" << '|' << '\t' << "Videos" << std::endl;
    for (int i = 0; i < Files.size(); i++) {
		std::cout << i << '\t' << '|'  << '\t' << (FileDir + Files[i]).c_str() << std::endl;
	}
	std::cout << "Which one you need?\n";
	std::cout << "Input: ";
	int num;
	std::cin >> num;
	PlayVideo(FileDir, LPWSTR((" " + FileDir + Files[num] +  " -noborder" + " -x " + sw + " -y " + sh + " -loop 0 ").c_str()));
	return 0;
}