#pragma once
#include <windows.h>
#include "jsonTools.h"
#include "libCard.h"

#include <string>
#include <vector>
#include <map>


char* WINAPI winOpenFl();
//wchar_t* WINAPI winOpenFlw();
char* WINAPI winOpenAndProcessFl(char* filename);
std::string getPathExe();
void openFileFolder(const std::string& path);
void openFile1(char* path);
void openFile1W(wchar_t* path);
void openFileFolderW(wchar_t* path);
void copyChars(char copy[64], char paste[64]);
void copyChars2(char copy[64], char paste[64]);
std::wstring charLocaleSwitch(char* input);
wchar_t* convStr2W(std::string& pathT);
std::vector<std::string> getMapKeys(std::map<std::string, std::string> inMap);
std::vector<std::string> funcFilesInFolder(std::string path);
std::vector<std::string> funcValidFilesInFolder(std::string path);
std::vector<std::string> funcValidFilesInFolderTags(std::string path);
std::vector<char*> funcFilesTypeInFolder(std::string path, std::string type);
std::string filePathFull(std::string filename);
std::string fileNameFull(std::string filename);
int funcValidFilesProcess(std::string path, std::vector<std::string>& names, std::vector<std::string>& tags, std::vector<std::string>& info, std::vector<std::string>& paths);
int funcValidFilesProcessMaps(std::string path, std::vector<std::string>& names, std::map<std::string, std::map<std::string, std::string>>& tagsANDinfo);
int funcValidFilesProcessClass(std::string path, std::vector<libCard>& libCards);
//void funcOpenWinapi();


