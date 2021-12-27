#pragma once
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include <d3d9.h>
#include <tchar.h>
#include <string>
#include <json/json.h>
#include <json/reader.h>
#include <json/value.h>
#include <fstream>
#include <iostream> 
#include <cstring>
#include <cstdlib>
#include <sys/stat.h>
#include <io.h>
#include <fcntl.h>
#include <array>
#include "testTools.h"
#include "jsonTools.h"
#include "imgUIsort.h"
#include <windows.h>
#include <codecvt>
#include <locale>
#include "imgUIsort.h"

//static void funcShowTestMsenu1();
//void popLoading();
//void setTableOld();
//void setTable();



void setTableClip(std::vector<libCard>& libCards);
void setTableClipItm(std::vector<libCard>& libCards, ImVector<MyItem> items);


int funcCloseFileOpened();


char* funcPopUpShow(char* newName);

//char* openfilename(char* filter = "Json Files (*.json)\0*.json\0", HWND owner = NULL);

//void setDataArrays();
void setDataArrays(std::vector<libCard>& libCards);
void setDataArraysItems(std::vector<libCard> libCards, ImVector<MyItem>& items);
void updateDataArraysItems(std::vector<libCard> libCards, int n);
void updateDataArrays(std::vector<libCard>& libCards, int idx = -1, char* name = "NULL", char* tags = "NULL", char* path = "NULL", std::map<char*, char*> info = {{"NULL","RESULT"}});
char* getFileNameOnly(char* fullName);
std::string getFileNameOnlyStr(char* fullName);
//void popPath(char buffName[64], char buffVal[64], char* filename);
void popElementEditSimple(std::vector<libCard>& libCards, char* filename);
void popElementEditDouble(std::vector<libCard>& libCards, char* filename);
void loadTranslation(std::string fileTranslateEn, std::vector<char*> translationsList);

char* getPathOnly();
char* getPathUser();

void popCreate();
void popSearch(std::vector<libCard> libCards);

void clearBuffers();
/*
extern char* newItemInfoBuffer[];


extern std::vector<libCard> libCards;
extern ImVector<MyItem> items;
extern int hovered = -1;


extern char  fileNameBuf[64];
extern char fileNameBufSub[64];
extern char fileNameNewBuff[64];
extern char fileTagsNewBuff[64];
extern char fileInfo1nNewBuff[64];
extern char fileInfo1vNewBuff[64];
extern char fileInfo2nNewBuff[64];
extern char fileInfo2vNewBuff[64];

extern char buffName[64];
extern char* buffVal;
extern char* tempNamePop;
extern char* editName;
extern char editBuff[64];

extern std::vector<std::string> namesList;

extern char* getPathOnly();
extern char* getPathUser();
extern std::string userPath;
extern std::string fileTranslateEn = "./translation/translation_en.json";
extern std::string fileTranslateDef = "./translation/translation_en.json";

extern std::map<std::string, std::map<std::string, std::string>> catalogueDB;
extern std::vector<char*> translationsList = funcFilesTypeInFolder("./translation", ".json");

extern char* name_app;
extern char* intro;
extern char* button_create;
extern char* check_catalogue;
extern char* table_name;
extern char* table_tags;
extern char* table_info;
extern char* table_path;
extern char* create_name;
extern char* create_tags;
extern char* create_info;
extern char* create_path;
extern char* refresh;
extern char* edit;
extern char* info;
extern char* add_path;
extern char* open_num;
extern char* open_folder_num;
extern char* edit_path_num;

extern char* fileNameTest = "test.json";
extern char* fillLine = "Enter category in '.json'";
extern char testName1[64] = "Not tagged";

extern char* langSwitch = destr(funcBaseGetFromJson("lang_list", fileTranslateDef));

extern bool show_another_window;
extern bool show_table;
extern bool can_update;
extern bool hasLoaded;

extern int checkOpened;
extern int canShow = 0;
extern int tempMapSize;
extern int row_x = 0;
extern int item_current = 0;



*/
