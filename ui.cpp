
#include <fstream>
#include <iostream>


#include "ui.h"

using namespace my_item;
//ImVector<MyItem> items;
//char* PROGRAM_NAME = _pgmptr;

//char* name_app;
//char* intro;
//char* button_create;
//char* button_search;
//char* search_key;
//char* search_val;
//std::string nameSearch;
//std::string tagsSearch;
//std::string pathSearch;
//std::string infoSearch;
//char* check_catalogue;
//char* table_name;
//char* table_tags;
//char* table_info;
//char* table_path;
//char* create_name;
//char* create_tags;
//char* create_info;
//char* create_path;
//char* refresh;
//char* edit;
//char* editTags;
//char* editInfo;
//char* info;
//char* add_path;
//char* open_num;
//char* open_folder_num;
//char* edit_path_num;
//char* toolTip;
//char* popOK;
//char* popBACK;
//int item_current = 0;

char* newItemInfoBuffer[] = { "" };

char  fileNameBuf[64] = "";
char fileNameBufSub[64] = "";
char fileNameNewBuff[64] = "";
char fileTagsNewBuff[64] = "";
char fileInfo1nNewBuff[64] = "";
char fileInfo1vNewBuff[64] = "";
char fileInfo2nNewBuff[64] = "";
char fileInfo2vNewBuff[64] = "";

char searchBuffName[64] = "";
char searchBuffTags[64] = "";
char searchBuffPath[64] = "";
char searchBuffInfoKey[64] = "";
char searchBuffInfoVal[64] = "";

char buffName[64] = "";
char* buffVal = "";
char* tempNamePop = "";
char* editName = "";
char* editBuff = new char[64];

char testName1[64] = "Not tagged";

char* getPathOnly();
//char* getPathUser();
std::string userPath = getPathUser();

//bool can_update;
//int need_update;
//int row_x = 0;
int tempMapSize;

std::vector<libCard> searchCards;
ImVector<MyItem> searchItems;


translateDB loadTranslationDB(std::string fileTranslateEn, std::vector<char*> translationsList, int item_current) {
    translateDB translationDB;
    fileTranslateEn = translationsList[item_current];
    translationDB.intro = destr(funcBaseGetFromJson("intro", fileTranslateEn));
    translationDB.button_create = destr(funcBaseGetFromJson("button_create", fileTranslateEn));
    translationDB.button_search = destr(funcBaseGetFromJson("button_search", fileTranslateEn));
    translationDB.search_key = destr(funcBaseGetFromJson("search_key", fileTranslateEn));
    translationDB.search_val = destr(funcBaseGetFromJson("search_val", fileTranslateEn));
    translationDB.check_catalogue = destr(funcBaseGetFromJson("check_catalogue", fileTranslateEn));
    translationDB.table_name = destr(funcBaseGetFromJson("table_name", fileTranslateEn));
    translationDB.table_tags = destr(funcBaseGetFromJson("table_tags", fileTranslateEn));
    translationDB.table_info = destr(funcBaseGetFromJson("table_info", fileTranslateEn));
    translationDB.table_path = destr(funcBaseGetFromJson("table_path", fileTranslateEn));
    translationDB.create_name = destr(funcBaseGetFromJson("create_name", fileTranslateEn));
    translationDB.create_tags = destr(funcBaseGetFromJson("create_tags", fileTranslateEn));
    translationDB.create_info = destr(funcBaseGetFromJson("create_info", fileTranslateEn));
    translationDB.create_path = destr(funcBaseGetFromJson("create_path", fileTranslateEn));
    translationDB.name_app = destr(funcBaseGetFromJson("name_app", fileTranslateEn));
    translationDB.refresh = destr(funcBaseGetFromJson("refresh", fileTranslateEn));
    translationDB.edit = destr(funcBaseGetFromJson("edit", fileTranslateEn));
    translationDB.editTags = destr(funcBaseGetFromJson("editTags", fileTranslateEn));
    translationDB.editInfo = destr(funcBaseGetFromJson("editInfo", fileTranslateEn));
    translationDB.info = destr(funcBaseGetFromJson("info", fileTranslateEn));
    translationDB.add_path = destr(funcBaseGetFromJson("add_path", fileTranslateEn));
    translationDB.open_num = destr(funcBaseGetFromJson("open_num", fileTranslateEn));
    translationDB.open_folder_num = destr(funcBaseGetFromJson("open_folder_num", fileTranslateEn));
    translationDB.edit_path_num = destr(funcBaseGetFromJson("create_path", fileTranslateEn));
    translationDB.toolTip = destr(funcBaseGetFromJson("toolTip", fileTranslateEn));
    translationDB.popOK = destr(funcBaseGetFromJson("popOK", fileTranslateEn));
    translationDB.popBACK = destr(funcBaseGetFromJson("popBACK", fileTranslateEn));
    translationDB.item_current = item_current;

    return translationDB;
}


//////




/////////////////////////////////////////////////////////////////// UI: popup windows


bool popCreate(UIassembly Cards) {
    bool result = false;

    std::string myPath = getPathUser();

    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal(Cards.getStrings().button_create, NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {

        ImGui::Separator();

        ImGui::Text(Cards.getStrings().create_name);
        ImGui::InputText(Cards.getStrings().table_name, fileNameNewBuff, 64);


        ImGui::TextWrapped(newItemInfoBuffer[0]);

        ImGui::TextWrapped(Cards.getStrings().create_tags);
        ImGui::InputText(Cards.getStrings().table_tags, fileTagsNewBuff, 64, ImGuiInputTextFlags_CharsNoBlank);
        ImGui::TextWrapped(Cards.getStrings().create_info);
        ImGui::InputText(" ", fileInfo1nNewBuff, 64);
        ImGui::SameLine();
        ImGui::InputText("  ", fileInfo1vNewBuff, 64);
        ImGui::InputText("   ", fileInfo2nNewBuff, 64);
        ImGui::SameLine();
        ImGui::InputText("    ", fileInfo2vNewBuff, 64);
        if (ImGui::Button(Cards.getStrings().create_path, ImVec2(120, 0))) {
            buffVal = winOpenFl();
            
        }
        ImGui::TextWrapped(Cards.getStrings().table_path);
        ImGui::SameLine();
        ImGui::TextWrapped(buffVal);



        if (ImGui::Button(Cards.getStrings().popOK, ImVec2(120, 0))) {

            copyChars2(testName1, fileNameNewBuff);
            newItemInfoBuffer[0] = fileNameNewBuff;
            newItemInfoBuffer[1] = fileTagsNewBuff;
            newItemInfoBuffer[2] = fileInfo1nNewBuff;
            newItemInfoBuffer[3] = fileInfo1vNewBuff;
            newItemInfoBuffer[4] = fileInfo2nNewBuff;
            newItemInfoBuffer[5] = fileInfo2vNewBuff;
            newItemInfoBuffer[6] = buffVal;
            char nameJson[64] = "userdata/";
            std::cout << nameJson << "\n";
            strcat(nameJson, newItemInfoBuffer[0]);
            std::cout << nameJson << "\n";
            strcat(nameJson, ".json");
            std::cout << nameJson << "\n";
            if (exist(nameJson) == 0) {
                funcWriteJson(newItemInfoBuffer, nameJson);

                openFileFolder(myPath);
            }
            else {

            }
            memset(&(fileNameNewBuff[0]), 0, 64);
            memset(&(fileTagsNewBuff[0]), 0, 64);
            memset(&(fileInfo1nNewBuff[0]), 0, 64);
            memset(&(fileInfo1vNewBuff[0]), 0, 64);
            memset(&(fileInfo2nNewBuff[0]), 0, 64);
            memset(&(fileInfo2vNewBuff[0]), 0, 64);
            ImGui::CloseCurrentPopup();
            clearBuffers();

            result = true;
        }
        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
        if (ImGui::Button(Cards.getStrings().popBACK, ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    }

    return result;
}



/////////////////////////////////////////////////////////////////// this is used for search only, bad code duplication, needs more work


/////////////////////////////////////////////////////////////////// DB: database setups and updates

//void setDataArrays(std::vector<libCard>& libCards)
//{
//
//    libCards.clear();
//
//    funcValidFilesProcessClass(getPathUser(), libCards);
//
//    setDataArraysItems(libCards, items);
//
//    //std::cout << libCards[0].getFind("--", "seri", "--", "--", "--") << "\n";
//    //std::cout << libCards[1].getFind("a", "b", "c", "d", "z") << "\n";
//}
//
//libCardAssembly setDataArrays1()
//{
//    std::vector<libCard> libCardsTemp;
//    funcValidFilesProcessClass(getPathUser(), libCardsTemp);
//	libCardAssembly Cards = libCardAssembly(libCardsTemp);
//
//    std::cout << Cards.getCards()[0].getFind("--", "seri", "--", "--", "--") << "\n";
//    std::cout << Cards.getCards()[0].getFind("a", "b", "c", "d", "z") << "\n";
//
//    return Cards;
//}

UIassembly setDataArrays2(std::string fileTranslateEn, std::vector<char*> translationsList, int idx)
{
    std::cout << __FUNCTION__ << "\n";

    std::vector<libCard> libCardsTemp;
    funcValidFilesProcessClass(getPathUser(), libCardsTemp);
    UIassembly uiCards = UIassembly(translateDB(fileTranslateEn, translationsList, idx), libCardAssembly(libCardsTemp));

    std::cout << uiCards.getData().getCards()[0].getFind("--", "seri", "--", "--", "--") << "\n";
    std::cout << uiCards.getData().getCards()[0].getFind("a", "b", "c", "d", "z") << "\n";

    return uiCards;
}

//void setDataArraysItems(std::vector<libCard> libCards, ImVector<MyItem>& items)
//{
//
//    items.clear();
//
//    if (items.Size == 0)
//    {
//        items.resize(libCards.size(), MyItem());
//
//        for (int n = 0; n < items.Size; n++)
//        {
//            const int template_n = n % libCards.size();
//            MyItem& item = items[n];
//            item.ID = n;
//
//            item.Name = libCards[template_n].getName();
//            item.Tags = libCards[template_n].getTags();
//            item.Path = libCards[template_n].getPath();
//            item.Info = libCards[template_n].getInfoChar();
//
//            
//        }
//    }
//}


void clearBuffers() {
    memset(&(fileNameNewBuff[0]), 0, 64);
    memset(&(fileTagsNewBuff[0]), 0, 64);
    memset(&(fileInfo1nNewBuff[0]), 0, 64);
    memset(&(fileInfo1vNewBuff[0]), 0, 64);
    memset(&(fileInfo2nNewBuff[0]), 0, 64);
    memset(&(fileInfo2vNewBuff[0]), 0, 64);
}

