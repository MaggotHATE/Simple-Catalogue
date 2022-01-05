//#include "main.cpp"

/*
void setTableOld() {
    static ImGuiTableFlags flags =
        ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti
        | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_NoBordersInBody
        | ImGuiTableFlags_ScrollY;



    if (ImGui::BeginTable(check_catalogue, 4, flags))
    {

        ImGui::TableSetupColumn(table_name, ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn(table_tags, ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn(table_info, ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn(table_path, ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableHeadersRow();



        for (int row = 0; row < namesList.size(); row++)
        {
            //std::cout << "List Name = " << namesList[row] << ", tags: " << tagList[row] << "\n";
            //char* fileListName = getFileNameOnly( destr(namesList[row]) );
            //std::cout << "getFileNameOnly1 = " << getFileNameOnly(destr(namesList[row])) << "; tags: " << tagList[row] << "\n";
            //const char* fileTags = funcGetTags(fileListName);
            // 
            //char* nameOnly = getFileNameOnly(destr(namesList[row]));
            std::string nameOnlyStr = getFileNameOnly(destr(namesList[row]));
            char* nameOnly = destr(nameOnlyStr);
            char* namenameOnly = funcGetIdxName(nameOnly, 0);
            //std::cout << "List Name = " << funcGetIdxName(nameOnly, 0) << ", tags: " << catalogueDB[namesList[row]]["tags"] << "\n";
            ImGui::TableNextRow();
            for (int column = 0; column < 4; column++)
            {



                ImGui::TableSetColumnIndex(column);
                if (column == 1) {
                    //if (tagList.size() > row) {
                    ImGui::Text(destr(catalogueDB[namesList[row]]["tags"]), (column == 2) ? "Stretch" : "Fixed", column, row);
                    //}
                    //else {
                    //    ImGui::Text("No tags", (column == 2) ? "Stretch" : "Fixed", column, row);
                    //}

                    std::string buttonEditName = edit + funcGetIdxNameStr(nameOnlyStr, 0);

                    if (ImGui::Button(destr(buttonEditName))) {
                        editName = destr(namesList[row]);

                        copyChars2(editBuff, funcGetTags(editName));
                        ImGui::OpenPopup("Edit item");

                    }


                }
                else if (column == 0) {
                    if (ImGui::Button(namenameOnly)) openFile1(nameOnly);
                }
                else if (column == 2) {
                    //char* info = funcGetInfo(destr(namesList[row]));

                    if (catalogueDB[namesList[row]]["info"] != "\0") {
                        ImGui::Text(destr(catalogueDB[namesList[row]]["info"]), (column == 2) ? "Stretch" : "Fixed", column, row);

                    }
                    std::string buttonInfoEditName = edit + funcGetIdxNameStr(nameOnlyStr, 0) + info;
                    if (ImGui::Button(destr(buttonInfoEditName))) {
                        editName = destr(namesList[row]);

                        if (catalogueDB[namesList[row]]["info"] != "") {
                            std::vector<std::map<std::string, std::string>> tempMap = funcGetInfoPairs(destr(namesList[row]));

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

                        ImGui::OpenPopup("Edit info");

                    }
                    //else {
                     //   ImGui::Text("No info", (column == 2) ? "Stretch" : "Fixed", column, row);
                    //}

                }
                else {

                    std::string pathS = catalogueDB[namesList[row]]["path"];
                    char* path = destr(pathS);
                    //OemToCharA(path, path);
                    ImGui::Text(path, (column == 2) ? "Stretch" : "Fixed", column, row);
                    std::string jsonFileName = funcGetIdxNameStr(nameOnlyStr, 0);

                    if (path == userPath) {
                        std::string buttonPath = add_path + jsonFileName;

                        if (ImGui::Button(destr(buttonPath))) {
                            //buffVal = winOpenFl();
                            //wchar_t buffCT = ;
                            //std::wcout << L"Путь =" << buffCT << "\n";
                            //funcWriteJsonSimpleData2W("path", winOpenFlw(), destr(namesList[row]));
                            winOpenAndProcessFl(destr(namesList[row]));
                            can_update = true;
                        }
                    }
                    else {
                        //std::string intFileName = fileNameFull(catalogueDB[namesList[row]]["path"]) + " in " + namenameOnly;
                        //std::string buttonOpenFile = "Open " + funcGetIdxNameStr(nameOnlyStr, 0);
                        std::string buttonOpenFile = open_num + std::to_string(row);
                        if (ImGui::Button(destr(buttonOpenFile))) {

                            //wchar_t* buffCT = convStr2W(pathS);
                            //openFile1W(buffCT);
                            //openFile1(path);
                            //char* path1;
                            //wsprintfA(path1, "%S", pathS);
                            //OemToAnsi(path, path1);
                            std::cout << "path = " << path << "\n";
                            std::cout << "path1 = " << funcGetDataPathNew(nameOnly) << "\n";
                            //std::wstring path1 = charLocaleSwitch(path);
                            ShellExecuteA(NULL, "open", destr(funcGetDataPathNew(nameOnly)), NULL, NULL, SW_SHOWDEFAULT);
                            //funcOpenWinapi();
                        }
                        ImGui::SameLine();

                        std::string buttonOpenPath = open_folder_num + std::to_string(row);
                        if (ImGui::Button(destr(buttonOpenPath))) {


                            //wchar_t* buffCT = convStr2W(filePathFull(catalogueDB[namesList[row]]["path"]));
                            openFileFolder(destr(filePathFull(catalogueDB[namesList[row]]["path"])));
                            //openFileFolderW(buffCT);
                        }
                        ImGui::SameLine();
                        std::string buttonPath = edit_path_num + std::to_string(row);

                        if (ImGui::Button(destr(buttonPath))) {
                            //buffVal = winOpenFl();

                            //std::wstring bufW = winOpenFlw();
                            //std::wcout << "path = " << buffVal << "\n";
                            //wchar_t* buffCT = winOpenFlw();
                            //std::wcout << L"Путь =" << buffCT << "\n";
                            //funcWriteJsonSimpleData2W("path", winOpenFlw(), destr(namesList[row]));
                            //funcWriteJsonSimpleData2("path", winOpenFl(), destr(namesList[row]));
                            winOpenAndProcessFl(destr(namesList[row]));
                            //can_update = true;
                        }
                    }
                }
                //switch (column) {
                //    case 1: ImGui::Text(destr(fileTagsList[row]), (column == 2) ? "Stretch" : "Fixed", column, row);
                //    break;
                //    default: ImGui::Text(getFirstCategoryOnly(fileListName), (column == 2) ? "Stretch" : "Fixed", column, row);
                //    break;
                //}
            }
            //std::cout << "Finished: row" << row << "\n";
        }

        popElementEditSimple(editName);
        popElementEditDouble(tempNamePop, editName);
        //popPath(buffName, buffVal, addPathName);
        ImGui::EndTable();
    }
}

void setTable() {

    //std::cout << "libCards size = " << libCards.size() << "\n";
    static ImGuiTableFlags flags =
        ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti
        | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_NoBordersInBody
        | ImGuiTableFlags_ScrollY | ImGuiTableFlags_ScrollX;



    if (ImGui::BeginTable(check_catalogue, 4, flags))
    {

        ImGui::TableSetupColumn(table_name, ImGuiTableColumnFlags_DefaultSort | ImGuiTableFlags_SizingFixedFit);//, MyItemColumnID_Name);
        ImGui::TableSetupColumn(table_tags, ImGuiTableFlags_SizingFixedFit);//, MyItemColumnID_Tags);
        ImGui::TableSetupColumn(table_info, ImGuiTableFlags_SizingFixedFit);//, MyItemColumnID_Info);
        ImGui::TableSetupColumn(table_path, ImGuiTableFlags_SizingFixedFit);//, MyItemColumnID_Path);//
        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableHeadersRow();



        for (int row = 0; row < libCards.size(); row++)
        {
            //std::cout << "List Name = " << namesList[row] << ", tags: " << tagList[row] << "\n";
            //char* fileListName = getFileNameOnly( destr(namesList[row]) );
            //std::cout << "getFileNameOnly1 = " << getFileNameOnly(destr(namesList[row])) << "; tags: " << tagList[row] << "\n";
            //const char* fileTags = funcGetTags(fileListName);
            // 
            //char* nameOnly = getFileNameOnly(destr(namesList[row]));
            std::string nameOnlyStr = getFileNameOnly(libCards[row].getName());
            char* nameOnly = destr(nameOnlyStr);
            char* namenameOnly = funcGetIdxName(nameOnly, 0);
            //std::cout << "List Name = " << funcGetIdxName(nameOnly, 0) << ", tags: " << catalogueDB[namesList[row]]["tags"] << "\n";
            ImGui::TableNextRow();
            for (int column = 0; column < 4; column++)
            {



                ImGui::TableSetColumnIndex(column);
                if (column == 1) {
                    //if (tagList.size() > row) {

                    //}
                    //else {
                    //    ImGui::Text("No tags", (column == 2) ? "Stretch" : "Fixed", column, row);
                    //}

                    std::string buttonEditName = edit + funcGetIdxNameStr(nameOnlyStr, 0);

                    if (ImGui::SmallButton(destr(buttonEditName))) {
                        editName = libCards[row].getName();

                        copyChars2(editBuff, libCards[row].getTags());
                        ImGui::OpenPopup("Edit item");

                    }
                    ImGui::Text(libCards[row].getTags(), (column == 2) ? "Stretch" : "Fixed", column, row);

                }
                else if (column == 0) {
                    if (ImGui::Button(namenameOnly)) openFile1(nameOnly);
                }
                else if (column == 2) {
                    //char* info = funcGetInfo(destr(namesList[row]));
                    char* infoG = funcAssembleFromMap(libCards[row].getInfo());

                    std::string buttonInfoEditName = edit + funcGetIdxNameStr(nameOnlyStr, 0) + info;
                    if (ImGui::SmallButton(destr(buttonInfoEditName))) {
                        editName = libCards[row].getName();

                        if (infoG != "") {
                            std::vector<std::map<std::string, std::string>> tempMap = funcGetInfoPairs(libCards[row].getName());

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

                        ImGui::OpenPopup("Edit info");

                    }
                    //else {
                     //   ImGui::Text("No info", (column == 2) ? "Stretch" : "Fixed", column, row);
                    //}
                    if (infoG != "\0") {
                        ImGui::Text(infoG, (column == 2) ? "Stretch" : "Fixed", column, row);

                    }

                }
                else {

                    std::string pathS = libCards[row].getPath();
                    char* path = libCards[row].getPath();
                    //OemToCharA(path, path);
                    ImGui::Text(path, (column == 2) ? "Stretch" : "Fixed", column, row);
                    std::string jsonFileName = funcGetIdxNameStr(nameOnlyStr, 0);

                    if (path == userPath) {
                        std::string buttonPath = add_path + jsonFileName;

                        if (ImGui::SmallButton(destr(buttonPath))) {
                            //buffVal = winOpenFl();
                            //wchar_t buffCT = ;
                            //std::wcout << L"Путь =" << buffCT << "\n";
                            //funcWriteJsonSimpleData2W("path", winOpenFlw(), destr(namesList[row]));
                            winOpenAndProcessFl(libCards[row].getName());
                            can_update = true;
                        }
                    }
                    else {
                        //std::string intFileName = fileNameFull(catalogueDB[namesList[row]]["path"]) + " in " + namenameOnly;
                        //std::string buttonOpenFile = "Open " + funcGetIdxNameStr(nameOnlyStr, 0);
                        std::string buttonOpenFile = open_num + std::to_string(row);
                        if (ImGui::SmallButton(destr(buttonOpenFile))) {

                            //wchar_t* buffCT = convStr2W(pathS);
                            //openFile1W(buffCT);
                            //openFile1(path);
                            //char* path1;
                            //wsprintfA(path1, "%S", pathS);
                            //OemToAnsi(path, path1);
                            std::cout << "path = " << path << "\n";
                            std::cout << "path1 = " << funcGetDataPathNew(nameOnly) << "\n";
                            //std::wstring path1 = charLocaleSwitch(path);
                            ShellExecuteA(NULL, "open", destr(funcGetDataPathNew(nameOnly)), NULL, NULL, SW_SHOWDEFAULT);
                            //funcOpenWinapi();
                        }
                        ImGui::SameLine();

                        std::string buttonOpenPath = open_folder_num + std::to_string(row);
                        if (ImGui::SmallButton(destr(buttonOpenPath))) {


                            //wchar_t* buffCT = convStr2W(filePathFull(catalogueDB[namesList[row]]["path"]));
                            openFileFolder(destr(filePathFull(libCards[row].getPath())));
                            //openFileFolderW(buffCT);
                        }
                        ImGui::SameLine();
                        std::string buttonPath = edit_path_num + std::to_string(row);

                        if (ImGui::SmallButton(destr(buttonPath))) {
                            //buffVal = winOpenFl();

                            //std::wstring bufW = winOpenFlw();
                            //std::wcout << "path = " << buffVal << "\n";
                            //wchar_t* buffCT = winOpenFlw();
                            //std::wcout << L"Путь =" << buffCT << "\n";
                            //funcWriteJsonSimpleData2W("path", winOpenFlw(), destr(namesList[row]));
                            //funcWriteJsonSimpleData2("path", winOpenFl(), destr(namesList[row]));
                            winOpenAndProcessFl(libCards[row].getName());
                            //can_update = true;
                        }
                    }
                }
                //switch (column) {
                //    case 1: ImGui::Text(destr(fileTagsList[row]), (column == 2) ? "Stretch" : "Fixed", column, row);
                //    break;
                //    default: ImGui::Text(getFirstCategoryOnly(fileListName), (column == 2) ? "Stretch" : "Fixed", column, row);
                //    break;
                //}
            }
            //std::cout << "Finished: row" << row << "\n";
        }

        popElementEditSimple(editName);
        popElementEditDouble(tempNamePop, editName);
        //popPath(buffName, buffVal, addPathName);
        ImGui::EndTable();
    }
}

void funcShowTestMsenu1()
{
    if (ImGui::BeginMenuBar())
    {

        if (ImGui::BeginMenu(funcParseJsonTest("translation_en", "menu1", 0)))
        {
            if (ImGui::MenuItem(funcParseJsonTest("translation_en", "menu1", 3), "CTRL+O")) {
                //LPOPENFILENAMEA testFile;
                //GetOpenFileNameA(testFile);
                //funcParseJsonFilename();
                //fileNameTest = openfilename();
                fileNameTest = winOpenFl();
                fileNameTest = getFileNameOnly(fileNameTest);
                if (exist(fileNameTest) == 1) {

                    fillLine = getFirstCategoryOnly(fileNameTest);
                    if (funcHasTags(fileNameTest) != "NULL")
                    {
                        strcpy_s(testName1,"Valid json is loaded");
                    }
                    else {
                        strcpy_s(testName1, "Not a valid json!");
                    }
                    //testName1 = _strdup(funcHasTags(fileNameTest));


                    //if ( == "NULL_JSON") {
                    //    fillLine = "Enter category in '.json'";
                    //}
                    //else
                    //{
                    //    fillLine = "Valid category entered!";
                    //}
                }
            }
            ImGui::EndMenu();
        }
        char* menuRoot = funcParseJsonTest("translation_en", "menu1", 1);
        if (ImGui::BeginMenu(menuRoot))
        {

            if (ImGui::MenuItem(funcParseJsonTest("translation_en", menuRoot, 0), "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem(funcParseJsonTest("translation_en", menuRoot, 1), "CTRL+X")) {}
            if (ImGui::MenuItem(funcParseJsonTest("translation_en", menuRoot, 2), "CTRL+C")) {}
            if (ImGui::MenuItem(funcParseJsonTest("translation_en", menuRoot, 3), "CTRL+V")) { ImGui::OpenPopup("Delete?"); }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu(funcParseJsonTest("translation_en", "menu1", 2))) {
            if (ImGui::MenuItem(funcParseJsonTest("translation_en", funcParseJsonTest("translation_en", "menu1", 2), 0), "CTRL+Q")) { show_another_window = false; }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

}


//void setDataArrays() {
//    namesList.clear();
//    tagList.clear();
//    infoList.clear();
//    pathList.clear();
//    funcValidFilesProcess(userPath, namesList, tagList, infoList, pathList);
//    can_update = false;
//}


ImGuiTableColumnFlags TableGetRowFlags(int row_n)
{
    ImGuiContext& g = *GImGui;
    ImGuiTable* table = g.CurrentTable;
    if (!table)
        return ImGuiTableRowFlags_None;

    row_n = table->CurrentRow;

    std::cout << " row_n = " << row_n << "\n";
    //if (row_n == table->CurrentRow)

    return table->RowFlags;
}

in main:

        // 3. Show another simple window.
        if (show_another_window)
        {
            //another_window_name = funcParseJsonTest();
            ImGui::Begin( funcParseJsonTest("translation_en","window1",0) , &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)

            ImGui::Text( funcParseJsonTest("translation_en", "window1", 1) );
           // ImGui::MenuItem("Test menu one", NULL, &show_test_menu1);
            char* myPath = getPathUser();


            ImGui::InputText(fillLine, fileNameBuf, 64);

            if (ImGui::Button("Open this file", ImVec2(120, 0))) {
                if (exist2(fileNameBuf)) {
                    openFileFolder(myPath);
                }
                else {
                    ImGui::Text("No such file!");
                }
            }

            ImGui::Text(fileNameTest);


            ImGui::Text(myPath);

            ImGui::Text(fillLine);
            ImGui::Text(testName1);

            if (fileNameTest != "test.json" && fileNameTest != "NULL_JSON") {
                ImGui::InputText("Subcategory", fileNameBufSub, 64);
            }

           // if (canShow == 1) {



            //}

            if (ImGui::Button(funcParseJsonTest("translation_en", "window1", 2))) {
                show_another_window = false;
                funcCloseFileOpened();
            }

            ImGui::End();
        }



        // Rendering

*/



/*


char* funcPopUpShow(char* newName) {



    return newName;
}



void popLoading() {
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));


    if (ImGui::BeginPopupModal("Loading", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {


        ImGui::Text("Loading...");
        ImGui::Separator();

        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
        if (hasLoaded) { ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    }


void popPath(char buffName[64], char* buffVal, char* filename) {
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    //char* pathValue = "";

    if (ImGui::BeginPopupModal("Add path", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {


        ImGui::Text(filename);
        ImGui::Separator();

        //static int unused_i = 0;
        //ImGui::Combo("Combo", &unused_i, "Delete\0Delete harder\0");

        ImGui::InputText("Info name", buffName, 64);
        ImGui::SameLine();
        //ImGui::InputText("Info value", buffVal, 64);
        if (ImGui::Button("Choose a file", ImVec2(120, 0))) {
            buffVal = winOpenFl();
        }

        if (ImGui::Button(popOK, ImVec2(120, 0))) {
            funcWriteJsonSimpleData(buffName, buffVal, filename);
            ImGui::CloseCurrentPopup();
        }
        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
        if (ImGui::Button(popBACK, ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    }

}




wchar_t* WINAPI winOpenFlw()
{
    wchar_t* winOpenResult = L"NULL";
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
        COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr))
    {
        IFileOpenDialog* pFileOpen;

        // Create the FileOpenDialog object.
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
            IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

        if (SUCCEEDED(hr))
        {
            // Show the Open dialog box.
            hr = pFileOpen->Show(NULL);

            // Get the file name from the dialog box.
            if (SUCCEEDED(hr))
            {
                IShellItem* pItem;
                hr = pFileOpen->GetResult(&pItem);
                if (SUCCEEDED(hr))
                {
                    wchar_t* pszFilePath;


                    //hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                    // Display the file name to the user.
                    if (SUCCEEDED(hr))
                    {
                        //std::wcout << "PATH1 = " << pszFilePath << "\n";
                        //MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
                        //fs::path(pszFilePath);

                        winOpenResult = pszFilePath;
                        //std::fstream fs;
                        //fs.open(buffer, std::fstream::in | std::fstream::out | std::fstream::app);
                        //Json::Value root;
                        //fs >> root;
                        //winOpenResult = strdup(root["testread1"]["warrior1"][0].asCString());
                        //CoTaskMemFree(pszFilePath);
                    }
                    pItem->Release();
                }
            }
            pFileOpen->Release();
        }
        CoUninitialize();
    }
    MessageBoxW(NULL, winOpenResult, L"File Path", MB_OK);

    return winOpenResult;
}

/////////////////////////////////////////////////////////////////// old Win32 windows functionality, doesn't work

void funcOpenWinapi() {
    OPENFILENAME ofn = { 0 };
    TCHAR szFile[260] = { 0 };
    HWND hwnd;              // owner window
    HANDLE hf;              // file handle

    // Initialize remaining fields of OPENFILENAME structure
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = _T("All\0*.*\0Text\0*.TXT\0");
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn) == TRUE)
        hf = CreateFile(ofn.lpstrFile,
            GENERIC_READ,
            0,
            (LPSECURITY_ATTRIBUTES)NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            (HANDLE)NULL);
}


}




void updateDataArrays(std::vector<libCard>& libCards, int idx, char* name, char* tags , char* path , std::map<char*, char*> info ) {
    if (idx > -1) {

        if (name != "NULL") {
            libCards[idx].setName(name);
            items[idx].Name = name;
        }
        if (tags != "NULL") {
            libCards[idx].setTags(tags);
            items[idx].Tags = tags;
        }
        if (path != "NULL") {
            libCards[idx].setPath(path);
            items[idx].Path = path;
        }
        if (info["NULL"] != "RESULT") {
            libCards[idx].setInfo(info);
            items[idx].Info = funcAssembleFromMap(libCards[idx].getInfo());
        }

        need_update = -1;
        std::cout << "SET: \n NAME = " << libCards[idx].setName(name) << "\n TAGS = " << libCards[row_x].getTags() << "\n PATH = " << libCards[row_x].getPath() << "\n";
        std::cout << "\n Upd: " << libCards[idx].getName() << " at #" << idx << " to " << libCards[idx].getPath() << "\n";
    }
}

void updateDataArraysItems(std::vector<libCard> libCards, int n)
{

    items[n].Name = libCards[n].getName();
    items[n].Tags = libCards[n].getTags();
    items[n].Path = libCards[n].getPath();
    items[n].Info = funcAssembleFromMap(libCards[n].getInfo());
    //need_update = -1;
    std::cout << "Upd: " << libCards[n].getName() << " at #" << n << " to " << libCards[n].getPath() << "\n";
    std::cout << "Result: " << items[n].Path << " at #" << n << "\n";
}


//////////////////////////////////////// OLD UI






void popElementEditSimple(libCardAssembly& Cards, int row_n) {
    //std::vector<libCard> libCards = Cards.getCards();
    //ImVector<MyItem> items = Cards.getUI();

    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    //char* pathValue = "";

    if (ImGui::BeginPopupModal(editTags, NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {

        //int row_x = Cards.getCardIdx(row_n);
        char* filename = Cards.getCardElem(CNAME, row_n);
        ImGui::Text(destr(stringConvert(filename, CP_THREAD_ACP, 0, CP_UTF8, 0)));
        ImGui::Separator();


        ImGui::InputText(table_tags, editBuff, 64, ImGuiInputTextFlags_CharsNoBlank);

        //std::cout << "PreTags = " << Cards.getUI()[row_x].Tags << " vs " << Cards.getCards()[Cards.getUI()[row_x].ID].getTags() << "\n";

        if (ImGui::Button(popOK, ImVec2(120, 0))) {

            funcWriteJson_tags(editBuff, filename);
            //can_update = true;

            //Cards.getCards()[row_x].setTags(editBuff);
            //Cards.getUI()[row_n].Tags = Cards.getCards()[row_x].getTags();
            Cards.setData(row_n, "--", editBuff);


            //std::cout << "Tags = " << Cards.getUI()[row_x].Tags << " vs " << Cards.getCards()[row_x].getTags() << " FROM " << editBuff << "\n";

            ImGui::CloseCurrentPopup();
        }
        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
        if (ImGui::Button(popBACK, ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    }
}

void popElementEditDouble(libCardAssembly& Cards, int row_n) {
    std::vector<libCard> libCards = Cards.getCards();

    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    //char* pathValue = "";

    if (ImGui::BeginPopupModal(editInfo, NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {

        char* filename = Cards.getCardElem(CNAME, row_n);
        ImGui::Text(filename);
        ImGui::Separator();


        ImGui::Text(create_info);
        //ImGui::Text("");
        ImGui::InputText(('#' + std::to_string(1) + " key").c_str(), fileInfo1nNewBuff, 64);
        ImGui::SameLine();
        ImGui::InputText(('#' + std::to_string(1) + " val").c_str(), fileInfo1vNewBuff, 64);
        ImGui::InputText(('#' + std::to_string(2) + " key").c_str(), fileInfo2nNewBuff, 64);
        ImGui::SameLine();
        ImGui::InputText(('#' + std::to_string(2) + " val").c_str(), fileInfo2vNewBuff, 64);

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
            //std::cout << numBuff << " funcWriteJsonSimpleSubData val[1] = " << destr(fileInfo2vNewBuff) << "\n";
            funcWriteJsonSimpleSubData(numBuff, name, value, filename);
            std::map<char*, char*> infoMapG = funcGetInfoMap(filename);

            //Cards.getCards()[row_x].setInfo(infoMapG);
            //Cards.getUI()[row_n].Info = funcAssembleFromMap(Cards.getCards()[row_x].getInfo());

            Cards.setData(row_n, "--", "--","--", infoMapG);

            //std::cout << "Path = " << Cards.getUI()[row_x].Info << " vs " << funcAssembleFromMap(Cards.getCards()[row_x].getInfo()) << "; " << row_n << "\n";
            //can_update = true;
            ImGui::CloseCurrentPopup();
        }
        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
        if (ImGui::Button(popBACK, ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    }

}


/////////////////////////////////////////////////////////////////// UI: context menus (tags and info use popups to keep editing popups working)
/////////////////////////////////////////////////////////////////// needs more work

void editPathContext(libCardAssembly& Cards, int row_n) {
    std::vector<libCard> libCards = Cards.getCards();
    libUI items = Cards.getUI();

    if (ImGui::BeginPopup(items.getAUI(row_n).Name))
    {
        //MyItem* item = &items[row_n];

        std::string buttonOpenFile = open_num + std::to_string(row_n);
        //ImGui::SmallButton(destr(buttonOpenFile));
        if (ImGui::Selectable(destr(buttonOpenFile))) {

            int row_x = Cards.getCardIdx(row_n);
           // std::cout << "path = " << item->Path << "; " << row_n << "\n";
            std::cout << "path1 = " << funcGetDataPathNew(getFileNameOnly(Cards.getCards()[row_x].getName())) << "\n";

            ShellExecuteA(NULL, "open", destr(stringConvert(Cards.getCards()[row_x].getPath(), CP_UTF8, 0, CP_THREAD_ACP, 0)), NULL, NULL, SW_SHOWDEFAULT);
            ImGui::CloseCurrentPopup();
        }
        //ImGui::SameLine();
        std::string buttonOpenPath = open_folder_num + std::to_string(row_n);
        if (ImGui::Selectable(destr(buttonOpenPath))) {


            int row_x = Cards.getCardIdx(row_n);
            char* value2 = destr(stringConvert(filePathFull(Cards.getCards()[row_x].getPath()), CP_UTF8, 0, CP_THREAD_ACP, 0));

            openFileFolder(value2);

            ImGui::CloseCurrentPopup();
        }
        //ImGui::SameLine();
        std::string buttonPath = edit_path_num + std::to_string(row_n);

        if (ImGui::Selectable(destr(buttonPath))) {


            int row_x = Cards.getCardIdx(row_n);
            std::cout << "\n BEGIN Path = " << Cards.getUI().getAUI(row_x).Path << " vs " << Cards.getCards()[row_x].getPath() << "; " << row_n << "\n";


            char* newPath = winOpenAndProcessFl(Cards.getCards()[row_x].getName());

            if (newPath != "NULL") {

                //Cards.getCards()[row_x].setPath(newPath);
                //Cards.getUI()[row_n].Path = Cards.getCards()[row_x].getPath();

                Cards.setData(row_n, "--", "--", newPath);

                std::cout << "Path = " << Cards.getUI().getAUI(row_x).Path << " vs " << Cards.getCards()[row_x].getPath() << "; " << row_n << "\n";
                ImGui::CloseCurrentPopup();
            }


        }
        ImGui::EndPopup();
    }

}

void editTagsContext(libCardAssembly& Cards, int row_n) {



    if (ImGui::BeginPopup(Cards.getUI().Tags(row_n))) {



        char* tempName = Cards.getCards()[Cards.getCardIdx(row_n)].getName();
        std::string nameOnlyStr = getFileNameOnly(tempName);
        std::string buttonEditName = editTags + funcGetIdxNameStr(nameOnlyStr, 0);
        //std::cout << "\n" << "BEFORE " << ": " << row_n << "; " << tempName << "\n";

        if (ImGui::SmallButton(destr(buttonEditName))) {

            int row_x = Cards.getCardIdx(row_n);
            editName = Cards.getCards()[row_x].getName();
            char* Ttags = Cards.getCards()[row_x].getTags();

            //std::cout << "\n" << "AFTER " << ": " << Ttags << "; " << "\n";
            copyChars2(editBuff, Ttags);



            //std::cout << "Button Tags = " << editName << " with " << Ttags << "; " << row_n << "\n";

            //ImGui::CloseCurrentPopup();
            ImGui::OpenPopup(editTags);
        }

        popElementEditSimple(Cards, row_n);

        ImGui::EndPopup();
   }
}

void editInfoContext(libCardAssembly& Cards, int row_n) {


    std::vector<libCard> libCards = Cards.getCards();
    libUI items = Cards.getUI();

    if (ImGui::BeginPopup(items.getAUI(row_n).Info))
    {

        int row_x = Cards.getCardIdx(row_n);
        //MyItem* item = &items[row_n];

        char* tempName = libCards[row_x].getName();

        std::string nameOnlyStr = getFileNameOnly(tempName);


        std::string buttonInfoEditName = editInfo + funcGetIdxNameStr(nameOnlyStr, 0);
        if (ImGui::SmallButton(destr(buttonInfoEditName))) {

            //char* nameOnly = destr(nameOnlyStr);
            char* infoG = libCards[row_x].getInfoChar();

            editName = libCards[row_x].getName();

            if (infoG != "") {
                std::vector<std::map<std::string, std::string>> tempMap = funcGetInfoPairs(libCards[row_x].getName());

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
            //tempNamePop = funcGetIdxName(nameOnly, 0);

            ImGui::OpenPopup(editInfo);
        }

        popElementEditDouble(Cards, row_n);

        ImGui::EndPopup();
    }
}



*/
