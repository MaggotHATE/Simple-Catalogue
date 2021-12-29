#pragma once
#include <Windows.h>
#include <tchar.h>
#include <string>
#include <json/json.h>
#include <json/reader.h>
#include <json/value.h>
#include <cstring>
#include <cstdlib>
#include <locale>
#include <shobjidl.h>
#include <codecvt>
#include "imgUIsort.h"


extern bool isdebug;

char* wchar_to_char(const wchar_t* pwchar);
char* wide_to_char1(const WCHAR* source);
void jsonRewriteFile(Json::Value root, char* filename, bool isUTF8);
//void funcParseJsonFilename();
Json::Value funcGetJson(char*& filename);
int funcWriteJson(char* newItemInfoBuffer[], char* filename);
int funcWriteJsonSimpleData(char* key, char* value, char* filename);
int funcWriteJsonSimpleData2(char* key, char* value, char* filename);
int funcWriteJsonSimpleData2W(char* key, wchar_t* value, char* filename);
int funcWriteJsonSimpleData3(char* key, std::string value, char* filename);
int funcWriteJsonSimpleSubData(int buf, char* key[], char* value[], char*& filename);
int funcWriteJsonSimpleSubDataStr(int buf, std::string key[], std::string value[], char*& filename);
int funcWriteJsonWriterData(char* key, char* value, char* filename);
int funcWriteJson_tags(char* tags, char* filename);
const char* funcHasTags(char* filename);
char* funcGetIdxName(char*& filename, int idx);
std::string funcGetIdxNameStr(std::string filename, int idx);
char* getFirstCategoryOnly(char* filename);
char* funcParseJsonTest(char* category, char* windowX, int idx, char* filename = "translation_en.json");
int exist(const char* name);
int exist2(const char* name);
bool is_file_exist(const char* fileName);
char* funcGetTags(char* filename);
char* funcGetInfo(char* filename);
std::map<char*, char*> funcGetInfoMap(char* filename);
std::vector<std::map<std::string, std::string>> funcGetInfoPairs(char* filename);
std::string funcGetDataPath(char* filename);
std::string funcGetDataPathNew(char* filename);
const char* funcHasName(char* filename, char* namename);
char* destr(const std::string s);
wchar_t* destrW(const std::wstring s);
char* destrC(const std::string s);
char* convToChar(std::string* s);
std::string stringConvert(const std::string s, int baseCP, DWORD bFlags, int needCP, DWORD nFlags);
int funcFixPath(char* filename);
int funcFixPath2(char* filename);
int funcFixPath3(Json::Value root, char* filename);
std::string funcBaseGetFromJson(std::string key, std::string& filename);
wchar_t* convertCharArrayToLPCWSTR(const char* charArray);
char* funcAssembleFromMap(std::map<char*, char*> charMap);
