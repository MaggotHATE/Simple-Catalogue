#pragma once
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>
#include <d3d9.h>
#include <tchar.h>
#include <string>
#include <json/json.h>
#include <json/reader.h>
#include <json/value.h>
#include <array>
#include "testTools.h"
#include <codecvt>
#include <locale>



//extern std::vector<libCard> libCards;
//extern ImVector<MyItem> items;
int hovered = -1;




std::vector<std::string> namesList;

std::string fileTranslateEn = "./translation/translation_en.json";
std::string fileTranslateDef = "./translation/translation_en.json";

std::map<std::string, std::map<std::string, std::string>> catalogueDB;
std::vector<char*> translationsList = funcFilesTypeInFolder("./translation", ".json");

//extern char* name_app;
//extern char* intro;
//extern char* button_create;
//extern char* button_search;
//extern char* search_key;
//extern char* search_val;
//extern char* check_catalogue;
//extern char* table_name;
//extern char* table_tags;
//extern char* table_info;
//extern char* table_path;
//extern char* create_name;
//extern char* create_tags;
//extern char* create_info;
//extern char* create_path;
//extern char* refresh;
//extern char* edit;
//extern char* editTags;
//extern char* editInfo;
//extern char* info;
//extern char* add_path;
//extern char* open_num;
//extern char* open_folder_num;
//extern char* edit_path_num;
//extern char* toolTip;
//extern char* popOK;
//extern char* popBACK;

char* fileNameTest = "test.json";
char* fillLine = "Enter category in '.json'";


char* langSwitch = destr(funcBaseGetFromJson("lang_list", fileTranslateDef));

bool show_another_window;
bool show_table;
bool can_update;
//extern int need_update;
bool hasLoaded;

int checkOpened;
int canShow = 0;
//extern int row_x;
//extern int item_current;

void setDataArraysMap();


/*
extern char* newItemInfoBuffer[];


extern std::vector<libCard> libCards;
extern ImVector<MyItem> items;
extern int hovered;


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
extern std::string fileTranslateEn;
extern std::string fileTranslateDef;

extern std::map<std::string, std::map<std::string, std::string>> catalogueDB;
extern std::vector<char*> translationsList;

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

extern char* fileNameTest;
extern char* fillLine;
extern char testName1[64];

extern char* langSwitch;

extern bool show_another_window;
extern bool show_table;
extern bool can_update;
extern bool hasLoaded;

extern int checkOpened;
extern int canShow;
extern int tempMapSize;
extern int row_x;
extern int item_current;*/

/*
char* newItemInfoBuffer[] = { "" };


std::vector<libCard> libCards;
static ImVector<MyItem> items;
int hovered = -1;


char  fileNameBuf[64] = "";
char fileNameBufSub[64] = "";
char fileNameNewBuff[64] = "";
char fileTagsNewBuff[64] = "";
char fileInfo1nNewBuff[64] = "";
char fileInfo1vNewBuff[64] = "";
char fileInfo2nNewBuff[64] = "";
char fileInfo2vNewBuff[64] = "";

char buffName[64] = "";
char* buffVal = "";
char* tempNamePop = "";
char* editName = "";
char editBuff[64] = "";

std::vector<std::string> namesList;

char* getPathOnly();
char* getPathUser();
std::string userPath = getPathUser();
std::string fileTranslateEn = "./translation/translation_en.json";
std::string fileTranslateDef = "./translation/translation_en.json";

std::map<std::string, std::map<std::string, std::string>> catalogueDB;
std::vector<char*> translationsList = funcFilesTypeInFolder("./translation", ".json");

char* name_app;
char* intro;
char* button_create;
char* check_catalogue;
char* table_name;
char* table_tags;
char* table_info;
char* table_path;
char* create_name;
char* create_tags;
char* create_info;
char* create_path;
char* refresh;
char* edit;
char* info;
char* add_path;
char* open_num;
char* open_folder_num;
char* edit_path_num;

char* fileNameTest = "test.json";
char* fillLine = "Enter category in '.json'";
char testName1[64] = "Not tagged";

char* langSwitch = destr(funcBaseGetFromJson("lang_list", fileTranslateDef));

bool show_another_window;
bool show_table;
bool can_update;
bool hasLoaded;

int checkOpened;
int canShow = 0;
int tempMapSize;
int row_x = 0;
static int item_current = 0;


*/
