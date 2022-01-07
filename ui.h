#pragma once
#include <tchar.h>
#include <string>
#include <array>
#include "testTools.h"
#include "libCardAssembly.h"
#include "uiTable.h"
#include "translateDB.h"


//#include "imgUIsort.h"

//static void funcShowTestMsenu1();
//void popLoading();
//void setTableOld();
//void setTable();



//void setTableClip(UIassembly& libCards);
//void setTableClipItm(std::vector<libCard> libCards, ImVector<my_item::MyItem>& items);


int funcCloseFileOpened();


//char* funcPopUpShow(char* newName);

//char* openfilename(char* filter = "Json Files (*.json)\0*.json\0", HWND owner = NULL);

//void setDataArrays();
//void setDataArrays(std::vector<libCard>& libCards);
//libCardAssembly setDataArrays1();
UIassembly setDataArrays2(std::string fileTranslateEn, std::vector<char*> translationsList, int idx);

//void setDataArraysItems(std::vector<libCard> libCards, ImVector<my_item::MyItem>& items);
//void updateDataArraysItems(std::vector<libCard> libCards, int n);
//void updateDataArrays(std::vector<libCard>& libCards, int idx = -1, char* name = "NULL", char* tags = "NULL", char* path = "NULL", std::map<char*, char*> info = {{"NULL","RESULT"}});


//void popPath(char buffName[64], char buffVal[64], char* filename);
//void popElementEditSimple(libCardAssembly& Cards, int row_n);
//void popElementEditDouble(libCardAssembly& Cards, int row_n);
//void loadTranslation(std::string fileTranslateEn, std::vector<char*> translationsList, translateDB& translationDB);


//std::string getPathUser();

bool popCreate(UIassembly Cards);
//void popSearch(libCardAssembly Cards);

void clearBuffers();
/*
extern char* newItemInfoBuffer[];


extern std::vector<libCard> libCards;
extern ImVector<my_item::MyItem> items;
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
