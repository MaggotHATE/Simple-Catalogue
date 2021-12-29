
#include <fstream>
#include <iostream>


#include "ui.h"

//ImVector<MyItem> items;
char* PROGRAM_NAME = _pgmptr;

char* name_app;
char* intro;
char* button_create;
char* button_search;
char* search_key;
char* search_val;
std::string nameSearch;
std::string tagsSearch;
std::string pathSearch;
std::string infoSearch;
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
char* editTags;
char* editInfo;
char* info;
char* add_path;
char* open_num;
char* open_folder_num;
char* edit_path_num;
char* toolTip;
char* popOK;
char* popBACK;
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
char editBuff[64] = "";

char testName1[64] = "Not tagged";

char* getPathOnly();
char* getPathUser();
std::string userPath = getPathUser();

//bool can_update;
//int need_update;
//int row_x = 0;
int tempMapSize;

std::vector<libCard> searchCards;
ImVector<MyItem> searchItems;


void loadTranslation(std::string fileTranslateEn, std::vector<char*> translationsList, translateDB& translationDB) {
    fileTranslateEn = translationsList[translationDB.item_current];
    intro = destr(funcBaseGetFromJson("intro", fileTranslateEn));
    button_create = destr(funcBaseGetFromJson("button_create", fileTranslateEn));
    button_search = destr(funcBaseGetFromJson("button_search", fileTranslateEn));
    search_key = destr(funcBaseGetFromJson("search_key", fileTranslateEn));
    search_val = destr(funcBaseGetFromJson("search_val", fileTranslateEn));
    check_catalogue = destr(funcBaseGetFromJson("check_catalogue", fileTranslateEn));
    table_name = destr(funcBaseGetFromJson("table_name", fileTranslateEn));
    table_tags = destr(funcBaseGetFromJson("table_tags", fileTranslateEn));
    table_info = destr(funcBaseGetFromJson("table_info", fileTranslateEn));
    table_path = destr(funcBaseGetFromJson("table_path", fileTranslateEn));
    create_name = destr(funcBaseGetFromJson("create_name", fileTranslateEn));
    create_tags = destr(funcBaseGetFromJson("create_tags", fileTranslateEn));
    create_info = destr(funcBaseGetFromJson("create_info", fileTranslateEn));
    create_path = destr(funcBaseGetFromJson("create_path", fileTranslateEn));
    name_app = destr(funcBaseGetFromJson("name_app", fileTranslateEn));
    refresh = destr(funcBaseGetFromJson("refresh", fileTranslateEn));
    edit = destr(funcBaseGetFromJson("edit", fileTranslateEn));
    editTags = destr(funcBaseGetFromJson("editTags", fileTranslateEn));
    editInfo = destr(funcBaseGetFromJson("editInfo", fileTranslateEn));
    info = destr(funcBaseGetFromJson("info", fileTranslateEn));
    add_path = destr(funcBaseGetFromJson("add_path", fileTranslateEn));
    open_num = destr(funcBaseGetFromJson("open_num", fileTranslateEn));
    open_folder_num = destr(funcBaseGetFromJson("open_folder_num", fileTranslateEn));
    edit_path_num = destr(funcBaseGetFromJson("create_path", fileTranslateEn));
    toolTip = destr(funcBaseGetFromJson("toolTip", fileTranslateEn));
    popOK = destr(funcBaseGetFromJson("popOK", fileTranslateEn));
    popBACK = destr(funcBaseGetFromJson("popBACK", fileTranslateEn));

    nameSearch = button_search;
    nameSearch += ": ";
    nameSearch += table_name;

    tagsSearch = button_search;
    tagsSearch += ": ";
    tagsSearch += table_tags;

    pathSearch = button_search;
    pathSearch += ": ";
    pathSearch += table_path;

    infoSearch = button_search;
    infoSearch += ": ";
    infoSearch += table_info;

    

    translationDB.name_app = name_app;
    translationDB.intro = intro;
    translationDB.button_create = button_create;
    translationDB.refresh = refresh;
    translationDB.button_search = button_search;
    translationDB.check_catalogue = check_catalogue;

    //std::cout << __FUNCTION__ << " finished" << "\n";

}



/////////////////////////////////////////////////////////////////// misc functions, used here only

char* getFileNameOnly(char* fullName) {
    //std::cout << __FUNCTION__ << "\n";

    std::string convString;
    std::string pathString;
    char* myPath = getPathExe();
    
    convString.assign(fullName);
    pathString.assign(myPath);

    int defPos = pathString.find(PROGRAM_NAME);
    pathString.erase(defPos);
    int pathLen = pathString.length();
    //defPos = convString.find("example_win32_directx9.exe");
    convString.erase(0, pathLen);
    char* result = _strdup(convString.c_str());
    //canShow = 1;
    return result;
}

std::string getFileNameOnlyStr(char* fullName) {
    std::string convString;
    std::string pathString;
    char* myPath = getPathExe();
    //std::cout << __FUNCTION__ << "\n";
    convString.assign(fullName);
    pathString.assign(myPath);

    int defPos = pathString.find(PROGRAM_NAME);
    pathString.erase(defPos);
    int pathLen = pathString.length();
    //defPos = convString.find("example_win32_directx9.exe");
    convString.erase(0, pathLen);
    std::string result = convString;
    //canShow = 1;
    return result;
}

char* getPathOnly() {
    std::string pathString;
    char* myPath = getPathExe();
    //std::cout << __FUNCTION__ << "\n";
    pathString.assign(myPath);

    int defPos = pathString.find(PROGRAM_NAME);
    pathString.erase(defPos);

    char* result = _strdup(pathString.c_str());
    //canShow = 1;
    return result;
}

char* getPathUser() {
    std::string pathString;
    char* myPath = getPathExe();
    //std::cout << __FUNCTION__ << "\n";
    pathString.assign(myPath);

    int defPos = pathString.find(PROGRAM_NAME);
    pathString.erase(defPos);
    pathString += "userdata\\";

    char* result = _strdup(pathString.c_str());
    //canShow = 1;
    return result;
}

/////////////////////////////////////////////////////////////////// UI: popup windows



void popElementEditSimple(libCardAssembly& Cards, int row_n) {
    //std::vector<libCard> libCards = Cards._assemblyOf;
    //ImVector<MyItem> items = Cards._assemblyView;

    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    //char* pathValue = "";

    if (ImGui::BeginPopupModal(editTags, NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {

        
        char* filename = Cards._assemblyOf[row_n].getName();
        ImGui::Text(filename);
        ImGui::Separator();

        ImGui::InputText(table_tags, editBuff, 64, ImGuiInputTextFlags_CharsNoBlank);

        //std::cout << "PreTags = " << items[row_x].Tags << " vs " << libCards[row_x].getTags() << "\n";

        if (ImGui::Button(popOK, ImVec2(120, 0))) {

            funcWriteJson_tags(editBuff, filename);
            //can_update = true;

            Cards._assemblyOf[row_n].setTags(editBuff);
            Cards._assemblyView[row_n].Tags = Cards._assemblyOf[row_n].getTags();

            std::cout << "Tags = " << Cards._assemblyView[row_n].Tags << " vs " << Cards._assemblyOf[row_n].getTags() << " FROM " << editBuff << "\n";

            ImGui::CloseCurrentPopup();
        }
        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
        if (ImGui::Button(popBACK, ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    }
}

void popElementEditDouble(libCardAssembly& Cards, int row_n) {
    std::vector<libCard> libCards = Cards._assemblyOf;
    ImVector<MyItem> items = Cards._assemblyView;

    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    //char* pathValue = "";

    if (ImGui::BeginPopupModal(editInfo, NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {

        char* filename = Cards._assemblyOf[row_n].getName();
        ImGui::Text(filename);
        ImGui::Separator();


        ImGui::Text(create_info);
        //ImGui::Text("");
        ImGui::InputText(" ", fileInfo1nNewBuff, 64);
        ImGui::SameLine();
        ImGui::InputText("  ", fileInfo1vNewBuff, 64);
        ImGui::InputText("   ", fileInfo2nNewBuff, 64);
        ImGui::SameLine();
        ImGui::InputText("    ", fileInfo2vNewBuff, 64);

        if (ImGui::Button(popOK, ImVec2(120, 0))) {

            char* name[2];
            char* value[2];
            int numBuff = 1;
            name[0] = destr(fileInfo1nNewBuff);
            value[0] = destr(fileInfo1vNewBuff);


            if (fileInfo2nNewBuff[0] != '\0' && fileInfo2vNewBuff[0] != '\0') {
                numBuff = 2;
                name[1] = destr(fileInfo2nNewBuff);
                value[1] = destr(fileInfo2vNewBuff);
            }
            std::cout << numBuff << " funcWriteJsonSimpleSubData val[1] = " << destr(fileInfo2vNewBuff) << "\n";
            funcWriteJsonSimpleSubData(numBuff, name, value, filename);
            std::map<char*, char*> infoMapG = funcGetInfoMap(filename);

            Cards._assemblyOf[row_n].setInfo(infoMapG);
            Cards._assemblyView[row_n].Info = funcAssembleFromMap(Cards._assemblyOf[row_n].getInfo());

            std::cout << "Path = " << Cards._assemblyView[row_n].Info << " vs " << funcAssembleFromMap(Cards._assemblyOf[row_n].getInfo()) << "; " << row_n << "\n";
            //can_update = true;
            ImGui::CloseCurrentPopup();
        }
        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
        if (ImGui::Button(popBACK, ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    }

}


bool popCreate() {
    bool result = false;

    char* myPath = getPathUser();

    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal(button_create, NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {

        ImGui::Separator();

        ImGui::Text(create_name);
        ImGui::InputText(table_name, fileNameNewBuff, 64);


        ImGui::TextWrapped(newItemInfoBuffer[0]);

        ImGui::TextWrapped(create_tags);
        ImGui::InputText(table_tags, fileTagsNewBuff, 64, ImGuiInputTextFlags_CharsNoBlank);
        ImGui::TextWrapped(create_info);
        ImGui::InputText(" ", fileInfo1nNewBuff, 64);
        ImGui::SameLine();
        ImGui::InputText("  ", fileInfo1vNewBuff, 64);
        ImGui::InputText("   ", fileInfo2nNewBuff, 64);
        ImGui::SameLine();
        ImGui::InputText("    ", fileInfo2vNewBuff, 64);
        if (ImGui::Button(create_path, ImVec2(120, 0))) {
            buffVal = winOpenFl();
            
        }
        ImGui::TextWrapped(table_path);
        ImGui::SameLine();
        ImGui::TextWrapped(buffVal);



        if (ImGui::Button(popOK, ImVec2(120, 0))) {

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
        if (ImGui::Button(popBACK, ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    }

    return result;
}

void popSearch(libCardAssembly Cards) {
    std::vector<libCard> libCards = Cards._assemblyOf;
    //ImVector<MyItem> items = Cards._assemblyView;

    char* myPath = getPathUser();

    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    ImGuiIO io = ImGui::GetIO();
    ImGui::SetNextWindowSize({ 2 * io.DisplaySize.x / 3, 2 * io.DisplaySize.y / 3 });

    if (ImGui::BeginPopupModal(button_search, NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {

        ImGui::Separator();


        ImGui::Text(destr(nameSearch));
        ImGui::InputText(table_name, searchBuffName, 64, ImGuiInputTextFlags_CharsNoBlank);

        ImGui::Text(destr(tagsSearch));
        ImGui::InputText(table_tags, searchBuffTags, 64, ImGuiInputTextFlags_CharsNoBlank);

        ImGui::Text(destr(pathSearch));
        ImGui::InputText(table_path, searchBuffPath, 64, ImGuiInputTextFlags_CharsNoBlank);

        ImGui::Text(destr(infoSearch));
        ImGui::InputText(search_key, searchBuffInfoKey, 64, ImGuiInputTextFlags_CharsNoBlank);
        ImGui::SameLine();
        ImGui::InputText(search_val, searchBuffInfoVal, 64, ImGuiInputTextFlags_CharsNoBlank);




        if (ImGui::Button(popOK, ImVec2(120, 0))) {

            searchCards.clear();
            char* Sname = "--";
            if (searchBuffName != "" && searchBuffName[0] != '\0') Sname = searchBuffName;
            char* Stags = "--";
            if (searchBuffTags != "" && searchBuffTags[0] != '\0') Stags = searchBuffTags;
            char* Spath = "--";
            if (searchBuffPath != "" && searchBuffPath[0] != '\0') Spath = searchBuffPath;

            char* SinfoKey = "--";
            if (searchBuffInfoKey != "" && searchBuffInfoKey[0] != '\0') SinfoKey = searchBuffInfoKey;
            char* Sinfoval = "--";
            if (searchBuffInfoVal != "" && searchBuffInfoVal[0] != '\0') Sinfoval = searchBuffInfoVal;

            if (searchCards.empty()) {
                for (int n = 0; n < Cards._assemblyOf.size(); n++)
                {
                    if (Cards._assemblyOf[n].getFind(Sname, Stags, Spath, SinfoKey, Sinfoval) > 0) searchCards.push_back(Cards._assemblyOf[n]);
                }
                setDataArraysItems(searchCards, searchItems);
            }


        }
        if (ImGui::Button(popBACK, ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }

        if (!searchCards.empty()) {
            setTableClipItm(searchCards, searchItems);
        }

        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();

        ImGui::EndPopup();
    }

}

/////////////////////////////////////////////////////////////////// UI: context menus (tags and info use popups to keep editing popups working)
/////////////////////////////////////////////////////////////////// needs more work

void editPathContext(libCardAssembly& Cards, int row_n) {
    std::vector<libCard> libCards = Cards._assemblyOf;
    ImVector<MyItem> items = Cards._assemblyView;

    if (ImGui::BeginPopup(items[row_n].Name))
    {
        //MyItem* item = &items[row_n];
        std::string buttonOpenFile = open_num + std::to_string(row_n);
        //ImGui::SmallButton(destr(buttonOpenFile));
        if (ImGui::Selectable(destr(buttonOpenFile))) {


           // std::cout << "path = " << item->Path << "; " << row_n << "\n";
            std::cout << "path1 = " << funcGetDataPathNew(getFileNameOnly(Cards._assemblyOf[row_n].getName())) << "\n";

            ShellExecuteA(NULL, "open", destr(stringConvert(Cards._assemblyOf[row_n].getPath(), CP_UTF8, 0, CP_THREAD_ACP, 0)), NULL, NULL, SW_SHOWDEFAULT);
            ImGui::CloseCurrentPopup();
        }
        //ImGui::SameLine();
        std::string buttonOpenPath = open_folder_num + std::to_string(row_n);
        if (ImGui::Selectable(destr(buttonOpenPath))) {



            char* value2 = destr(stringConvert(filePathFull(Cards._assemblyOf[row_n].getPath()), CP_UTF8, 0, CP_THREAD_ACP, 0));

            openFileFolder(value2);

            ImGui::CloseCurrentPopup();
        }
        //ImGui::SameLine();
        std::string buttonPath = edit_path_num + std::to_string(row_n);

        if (ImGui::Selectable(destr(buttonPath))) {

            std::cout << "\n BEGIN Path = " << Cards._assemblyView[row_n].Path << " vs " << Cards._assemblyOf[row_n].getPath() << "; " << row_n << "\n";


            char* newPath = winOpenAndProcessFl(Cards._assemblyOf[row_n].getName());

            if (newPath != "NULL") {

                Cards._assemblyOf[row_n].setPath(newPath);
                Cards._assemblyView[row_n].Path = Cards._assemblyOf[row_n].getPath();

                std::cout << "Path = " << Cards._assemblyView[row_n].Path << " vs " << Cards._assemblyOf[row_n].getPath() << "; " << row_n << "\n";
                ImGui::CloseCurrentPopup();
            }


        }
        ImGui::EndPopup();
    }

}

void editTagsContext(libCardAssembly& Cards, int row_n) {



    if (ImGui::BeginPopup(Cards._assemblyView[row_n].Tags)) {

        char* tempName = Cards._assemblyOf[row_n].getName();
        std::string nameOnlyStr = getFileNameOnly(tempName);
        std::string buttonEditName = editTags + funcGetIdxNameStr(nameOnlyStr, 0);

        if (ImGui::SmallButton(destr(buttonEditName))) {


            editName = Cards._assemblyOf[row_n].getName();
            char* Ttags = Cards._assemblyOf[row_n].getTags();

            std::cout << "\n" << "AFTER " << ": " << Ttags << "; " << "\n";
            copyChars2(editBuff, Ttags);



            std::cout << "Button Tags = " << editName << " with " << Ttags << "; " << row_n << "\n";

            //ImGui::CloseCurrentPopup();
            ImGui::OpenPopup(editTags);
        }

        popElementEditSimple(Cards, row_n);

        ImGui::EndPopup();
    }
}

void editInfoContext(libCardAssembly& Cards, int row_n) {


    std::vector<libCard> libCards = Cards._assemblyOf;
    ImVector<MyItem> items = Cards._assemblyView;

    if (ImGui::BeginPopup(items[row_n].Info))
    {

        MyItem* item = &items[row_n];
    
        char* tempName = libCards[row_n].getName();

        std::string nameOnlyStr = getFileNameOnly(tempName);
        char* nameOnly = destr(nameOnlyStr);
        char* infoG = funcAssembleFromMap(libCards[row_n].getInfo());

        std::string buttonInfoEditName = editInfo + funcGetIdxNameStr(nameOnlyStr, 0);
        if (ImGui::SmallButton(destr(buttonInfoEditName))) {
            editName = libCards[row_n].getName();

            if (infoG != "") {
                std::vector<std::map<std::string, std::string>> tempMap = funcGetInfoPairs(libCards[row_n].getName());

                tempMapSize = tempMap.size();
                std::cout << "tempMapSize = " << tempMapSize << "\n";

                if (tempMapSize == 1) {
                    std::cout << "case 1" << "\n";
                    copyChars2(fileInfo1nNewBuff, destr(tempMap[0]["key"]));
                    copyChars2(fileInfo1vNewBuff, destr(tempMap[0]["val"]));
                    memset(&(fileInfo2nNewBuff[0]), 0, 64);
                    memset(&(fileInfo2vNewBuff[0]), 0, 64);
                }
                else {
                    std::cout << "case 2" << "\n";
                    copyChars2(fileInfo1nNewBuff, destr(tempMap[0]["key"]));
                    copyChars2(fileInfo1vNewBuff, destr(tempMap[0]["val"]));
                    copyChars2(fileInfo2nNewBuff, destr(tempMap[1]["key"]));
                    copyChars2(fileInfo2vNewBuff, destr(tempMap[1]["val"]));
                }
            }
            else
            {
                memset(&(fileInfo1nNewBuff[0]), 0, 64);
                memset(&(fileInfo1vNewBuff[0]), 0, 64);
                memset(&(fileInfo2nNewBuff[0]), 0, 64);
                memset(&(fileInfo2vNewBuff[0]), 0, 64);
                tempMapSize = 2;
            }
            tempNamePop = funcGetIdxName(nameOnly, 0);

            ImGui::OpenPopup(editInfo);
        }

        popElementEditDouble(Cards, row_n);

        ImGui::EndPopup();
    }
}

/////////////////////////////////////////////////////////////////// UI: tables

void setTableClip(libCardAssembly& Cards) {

    std::vector<libCard> libCards = Cards._assemblyOf;
    ImVector<MyItem> items = Cards._assemblyView;
    // Create item list

    const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();
    // Options
    static ImGuiTableFlags flags =
        ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Sortable | ImGuiTableFlags_ScrollY
        | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_NoBordersInBody | ImGuiTableFlags_ScrollX;

    if (ImGui::BeginTable(check_catalogue, 5, flags))
    {
        // Declare columns
        // We use the "user_id" parameter of TableSetupColumn() to specify a user id that will be stored in the sort specifications.
        // This is so our sort function can identify a column given our own identifier. We could also identify them based on their index!
        // Demonstrate using a mixture of flags among available sort-related flags:
        // - ImGuiTableColumnFlags_DefaultSort
        // - ImGuiTableColumnFlags_NoSort / ImGuiTableColumnFlags_NoSortAscending / ImGuiTableColumnFlags_NoSortDescending
        // - ImGuiTableColumnFlags_PreferSortAscending / ImGuiTableColumnFlags_PreferSortDescending
        ImGui::TableSetupColumn("   #", ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_ID);
        ImGui::TableSetupColumn(table_name, ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_Name);
        ImGui::TableSetupColumn(table_tags, ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_Tags);
        ImGui::TableSetupColumn(table_info, ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_Info);
        ImGui::TableSetupColumn(table_path, ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_Path);//
        ImGui::TableSetupScrollFreeze(1, 1); // Make row always visible
        ImGui::TableHeadersRow();

       

        // Sort our data if sort specs have been changed!
        if (ImGuiTableSortSpecs* sorts_specs = ImGui::TableGetSortSpecs())
            if (sorts_specs->SpecsDirty)
            {
                MyItem::s_current_sort_specs1 = sorts_specs; // Store in variable accessible by the sort function.
                if (items.Size > 1)
                    qsort(&items[0], (size_t)items.Size, sizeof(items[0]), MyItem::CompareWithSortSpecs1);
                //std::cout << items.Size << " : " << sizeof(items[0]) << "\n";
                MyItem::s_current_sort_specs1 = NULL;
                sorts_specs->SpecsDirty = false;
            }


        // Demonstrate using clipper for large vertical lists
        ImGuiListClipper clipper;
        clipper.Begin(items.Size);

        while (clipper.Step())
            for (int row_n = clipper.DisplayStart; row_n < clipper.DisplayEnd; row_n++)
            {


                ImGui::PushID(items[row_n].ID);
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%04d", items[row_n].ID);
                ImGui::TableNextColumn();

                if (ImGui::Button(funcGetIdxName(items[row_n].Name, 0))) openFile1(items[row_n].Name);
                ImGui::TableNextColumn();

                ImGui::Text(items[row_n].Tags);
                if (ImGui::IsItemHovered()) ImGui::SetTooltip(toolTip);

                if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(1)) {
                    //row_x = items[row_n].ID;
                    //if (isdebug == true) std::cout << items[row_n].ID << " : " << row_x << "\n";
                    ImGui::OpenPopupContextItem(items[row_n].Tags);
                } 

                editTagsContext(Cards, row_n);

                ImGui::TableNextColumn();

                ImGui::Text(items[row_n].Info);
                if (ImGui::IsItemHovered()) ImGui::SetTooltip(toolTip);

                if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(1)) {
                    //row_x = items[row_n].ID;
                    //if (isdebug == true) std::cout << row_x << " : " << row_n << "\n";
                    ImGui::OpenPopupContextItem(items[row_n].Info);
                }

                
                editInfoContext(Cards, row_n);

                ImGui::TableNextColumn();

                ImGui::Text(items[row_n].Path);
                if (ImGui::IsItemHovered()) ImGui::SetTooltip(toolTip);

                if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(1)) {
                    //row_x = items[row_n].ID;
                    //if (isdebug == true) std::cout << row_x << " : " << row_n << "\n";
                    ImGui::OpenPopupContextItem(items[row_n].Name);
                }

                editPathContext(Cards, row_n);


                ImGui::PopID();
            }



        ImGui::EndTable();
    }
}

/////////////////////////////////////////////////////////////////// this is used for search only, bad code duplication, needs more work

void setTableClipItm(std::vector<libCard> libCards, ImVector<MyItem>& items) {
    //std::vector<libCard> libCards = Cards._assemblyOf;
    //ImVector<MyItem> items = Cards._assemblyView;

    // Create item list

    const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();
    // Options
    static ImGuiTableFlags flags =
        ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Sortable | ImGuiTableFlags_ScrollY
        | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_NoBordersInBody | ImGuiTableFlags_ScrollX;

    if (ImGui::BeginTable(check_catalogue, 5, flags))
    {
        // Declare columns
        // We use the "user_id" parameter of TableSetupColumn() to specify a user id that will be stored in the sort specifications.
        // This is so our sort function can identify a column given our own identifier. We could also identify them based on their index!
        // Demonstrate using a mixture of flags among available sort-related flags:
        // - ImGuiTableColumnFlags_DefaultSort
        // - ImGuiTableColumnFlags_NoSort / ImGuiTableColumnFlags_NoSortAscending / ImGuiTableColumnFlags_NoSortDescending
        // - ImGuiTableColumnFlags_PreferSortAscending / ImGuiTableColumnFlags_PreferSortDescending
        ImGui::TableSetupColumn("   #", ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_ID);
        ImGui::TableSetupColumn(table_name, ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_Name);
        ImGui::TableSetupColumn(table_tags, ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_Tags);
        ImGui::TableSetupColumn(table_info, ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_Info);
        ImGui::TableSetupColumn(table_path, ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_Path);//
        ImGui::TableSetupScrollFreeze(1, 1); // Make row always visible
        ImGui::TableHeadersRow();



        // Sort our data if sort specs have been changed!
        if (ImGuiTableSortSpecs* sorts_specs = ImGui::TableGetSortSpecs())
            if (sorts_specs->SpecsDirty)
            {
                MyItem::s_current_sort_specs1 = sorts_specs; // Store in variable accessible by the sort function.
                if (items.Size > 1)
                    qsort(&items[0], (size_t)items.Size, sizeof(items[0]), MyItem::CompareWithSortSpecs1);
                //std::cout << items.Size << " : " << sizeof(items[0]) << "\n";
                MyItem::s_current_sort_specs1 = NULL;
                sorts_specs->SpecsDirty = false;
            }


        // Demonstrate using clipper for large vertical lists
        ImGuiListClipper clipper;
        clipper.Begin(items.Size);

        while (clipper.Step())
            for (int row_n = clipper.DisplayStart; row_n < clipper.DisplayEnd; row_n++)
            {
                // Display a data item
                //MyItem* item = &items[row_n];
                //if (row_n == 16) {
                //    std::cout << items[row_n].Path << " : " << row_n << "\n";
                //}

                ImGui::PushID(items[row_n].ID);
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%04d", items[row_n].ID);
                ImGui::TableNextColumn();
                //ImGui::SmallButton(funcGetIdxName(item->Name,0));
                if (ImGui::Button(funcGetIdxName(items[row_n].Name, 0))) openFile1(items[row_n].Name);
                ImGui::TableNextColumn();

                ImGui::Text(items[row_n].Tags);
                if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(1)) {
                    //row_x = items[row_n].ID;
                    //if (isdebug == true) std::cout << items[row_n].ID << " : " << row_x << "\n";
                    ImGui::OpenPopupContextItem(items[row_n].Tags);
                }
                //if (ImGui::BeginPopup(items[row_n].Tags))
                //{
                //    editTagsContext(libCards);
                //    ImGui::EndPopup();
                //}
                //editTagsContext(Cards, row_n);
                ImGui::TableNextColumn();

                ImGui::Text(items[row_n].Info);
                //const char* lines[] = { item->Info };
                //for (int i = 0; i < IM_ARRAYSIZE(lines); i++)
                //    if (lines[i])
                //        ImGui::BulletText("%s", lines[i]);
                if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(1)) {
                    //row_x = items[row_n].ID;
                    //if (isdebug == true) std::cout << row_x << " : " << row_n << "\n";
                    ImGui::OpenPopupContextItem(items[row_n].Info);
                }
                if (ImGui::BeginPopup(items[row_n].Info))
                {
                    //editInfoContext(Cards);
                    ImGui::EndPopup();
                }
                ImGui::TableNextColumn();

                ImGui::Text(items[row_n].Path);
                if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(1)) {
                    //row_x = items[row_n].ID;
                   // if (isdebug == true) std::cout << row_x << " : " << row_n << "\n";
                    ImGui::OpenPopupContextItem(items[row_n].Name);
                }
                //if (ImGui::BeginPopup(items[row_n].Name))
                //{
                //    editPathContext(libCards);
                //    ImGui::EndPopup();
                //}
                //editPathContext(Cards, row_n);

                ImGui::PopID();
            }



        //popElementEditSimple(editName);
        //popElementEditDouble(tempNamePop, editName);
        ImGui::EndTable();
    }
}

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

libCardAssembly setDataArrays1()
{
    libCardAssembly Cards;

    std::vector<libCard> libCardsTemp;

    funcValidFilesProcessClass(getPathUser(), libCardsTemp);

    Cards.setUp(libCardsTemp);

    std::cout << Cards._assemblyOf[0].getFind("--", "seri", "--", "--", "--") << "\n";
    std::cout << Cards._assemblyOf[0].getFind("a", "b", "c", "d", "z") << "\n";

    return Cards;
}

void setDataArraysItems(std::vector<libCard> libCards, ImVector<MyItem>& items)
{

    items.clear();

    if (items.Size == 0)
    {
        items.resize(libCards.size(), MyItem());

        for (int n = 0; n < items.Size; n++)
        {
            const int template_n = n % libCards.size();
            MyItem& item = items[n];
            item.ID = n;

            item.Name = libCards[template_n].getName();
            item.Tags = libCards[template_n].getTags();
            item.Path = libCards[template_n].getPath();
            item.Info = funcAssembleFromMap(libCards[template_n].getInfo());

            
        }
    }
}


void clearBuffers() {
    memset(&(fileNameNewBuff[0]), 0, 64);
    memset(&(fileTagsNewBuff[0]), 0, 64);
    memset(&(fileInfo1nNewBuff[0]), 0, 64);
    memset(&(fileInfo1vNewBuff[0]), 0, 64);
    memset(&(fileInfo2nNewBuff[0]), 0, 64);
    memset(&(fileInfo2vNewBuff[0]), 0, 64);
}

