#include <fstream>
#include <iostream> 
#include <imgui.h>
#include "uiClass.h"
#include "testTools.h"



void UIassembly::loadTransl(translateDB _translations) {
    uiStrings_ = _translations;
}

void UIassembly::setData(libCardAssembly _data) {
    uiData_ = _data;
}

libCardAssembly& UIassembly::getData() {
    return uiData_ ;
}

translateDB& UIassembly::getStrings() {
    return uiStrings_;
}

void UIassembly::setStrings(std::string fileTranslateEn, std::vector<char*> translationsList, int item_current) {
    uiStrings_ = translateDB(fileTranslateEn, translationsList, item_current);
}

void UIassembly::SearchBuffers(int size){
    readyBuffers(size);
    for (int i = 0; i < uiBuffers_.size(); i++) {
        uiBuffers_[i] = "";
    }
}

void UIassembly::setGenereated(int row_n) {
    uiGenerated_[row_n]["name"] = uiData_.getCardElem(CNAME, row_n);
    uiGenerated_[row_n]["nameOnlyStr"] = getFileNameOnly(destr(uiGenerated_[row_n]["name"]));
    uiGenerated_[row_n]["buttonEditName"] = uiStrings_.editTags + funcGetIdxNameStr(uiGenerated_[row_n]["nameOnlyStr"], 0);
    uiGenerated_[row_n]["buttonInfoEditName"] = uiStrings_.editInfo + funcGetIdxNameStr(uiGenerated_[row_n]["nameOnlyStr"], 0);
    uiGenerated_[row_n]["buttonPath"] = uiStrings_.edit_path_num + std::to_string(row_n);
    uiGenerated_[row_n]["buttonOpenPath"] = uiStrings_.open_folder_num + std::to_string(row_n);
    uiGenerated_[row_n]["buttonOpenFile"] = uiStrings_.open_num + std::to_string(row_n);
}

UIassembly::UIassembly(translateDB _translations, libCardAssembly _data) {

    clearData();

    loadTransl(_translations);
    setData(_data);


}

void UIassembly::sortAndGenerate(int idx) {
    uiData_.getUI().sortUI(idx);

    for (int i = 0; i < uiData_.getCards().size(); i++) {
        setGenereated(i);
        std::cout << __FUNCTION__ << " : " << i << " = " << uiGenerated_[i]["buttonInfoEditName"] << "\n";
    }
}

void UIassembly::clearData() {
    uiData_.clearC();
    uiData_.clearV();
}
//void UIassembly::clearStrings() {
//
//}
void UIassembly::clearGenerated() {
    uiGenerated_.clear();
}

void UIassembly::clear() {
    clearGenerated();
    clearData();
    std::cout << __FUNCTION__ << " FINISHED " << "\n";
}

void UIassembly::popEditSimple(int row_n) {

    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal(uiStrings_.editTags, NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {

        char* filename = uiData_.getCardElem(CNAME, row_n);
        ImGui::Text(destr(stringConvert(filename, CP_THREAD_ACP, 0, CP_UTF8, 0)));
        ImGui::Separator();

        ImGui::InputText(uiStrings_.table_tags, uiBuffers_[0], 64, ImGuiInputTextFlags_CharsNoBlank);


        if (ImGui::Button(uiStrings_.popOK, ImVec2(120, 0))) {

            funcWriteJson_tags(uiBuffers_[0], filename);

            uiData_.setData(row_n, "--", uiBuffers_[0]);

            ImGui::CloseCurrentPopup();
        }
        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
        if (ImGui::Button(uiStrings_.popBACK, ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    }
}

void UIassembly::editTagsContext(int row_n) {

    if (ImGui::BeginPopup(uiData_.getUI().Tags(row_n))) {

        
        //
        if (ImGui::SmallButton(destr(uiGenerated_[row_n]["buttonEditName"]))) {
            
            int row_x = uiData_.getCardIdx(row_n);
            
            readyBuffers(1);

            uiBuffers_[0] = destr(uiData_.getCards()[row_x].getTags());
            //std::cout << __FUNCTION__ << " readyBuffers " << "\n";
            

            ImGui::OpenPopup(uiStrings_.editTags);
        }

        popEditSimple(row_n);

        ImGui::EndPopup();
    }
}

void UIassembly::popEditDouble(int row_n) {

    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    //char* pathValue = "";

    //std::cout << __FUNCTION__ << " start " << "\n";

    if (ImGui::BeginPopupModal(uiStrings_.editInfo, NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {

        char* filename = uiData_.getCardElem(CNAME, row_n);
        ImGui::Text(filename);
        ImGui::Separator();


        ImGui::Text(uiStrings_.create_info);
        //ImGui::Text("");

        //std::cout << __FUNCTION__ << " : " << uiBuffers_.size() << "\n";

        for (int i = 0; i < uiBuffers_.size(); i+=2) {
            //std::cout << i << " KEY " << i + 1 << "\n";
            ImGui::InputText(('#' + std::to_string(i) + " key").c_str(), uiBuffers_[i], 64);
            ImGui::SameLine();
            //std::cout << i << " VAL " << i + 1 << "\n";
            ImGui::InputText(('#' + std::to_string(i) + " val").c_str(), uiBuffers_[i+1], 64);

        }

        if (ImGui::Button(uiStrings_.popOK, ImVec2(120, 0))) {

            std::cout << uiBuffers_[0] << " : " << uiBuffers_[1] << "\n";
            //std::cout << numBuff << " funcWriteJsonSimpleSubData val[1] = " << destr(fileInfo2vNewBuff) << "\n";

            funcWriteJsonInfoClass(uiBuffers_, filename);
            std::map<char*, char*> infoMapG = funcGetInfoMap(filename);

            //Cards.getCards()[row_x].setInfo(infoMapG);
            //Cards.getUI()[row_n].Info = funcAssembleFromMap(Cards.getCards()[row_x].getInfo());

            uiData_.setData(row_n, "--", "--", "--", infoMapG);

            //std::cout << "Path = " << Cards.getUI()[row_x].Info << " vs " << funcAssembleFromMap(Cards.getCards()[row_x].getInfo()) << "; " << row_n << "\n";
            //can_update = true;
            ImGui::CloseCurrentPopup();
        }
        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
        if (ImGui::Button(uiStrings_.popBACK, ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    }

}

void UIassembly::editInfoContext(int row_n) {


    if (ImGui::BeginPopup(uiData_.getUI().getAUI(row_n).Info))
    {

        int row_x = uiData_.getCardIdx(row_n);
        int tempMapSize = 1;
        //MyItem* item = &items[row_n];

        if (ImGui::SmallButton(destr(uiGenerated_[row_n]["buttonInfoEditName"]))) {

            char* infoG = uiData_.getACard(row_x).getInfoChar();

            if (infoG != "") {
                std::vector<std::map<std::string, std::string>> tempMap = funcGetInfoPairs(uiData_.getCardElem(CNAME, row_n));
                tempMapSize = tempMap.size();

                readyBuffers(tempMap.size()*2);
                
                std::cout << "tempMapSize = " << tempMapSize << "\n";

                if (tempMapSize == 1) {
                    std::cout << "case 1" << "\n";
                    uiBuffers_[0] = destr(tempMap[0]["key"]);
                    uiBuffers_[1] = destr(tempMap[0]["val"]);
                    std::cout << uiBuffers_[0] << " : " << uiBuffers_[1] << "\n";
                }
                else {
                    std::cout << "case 2" << "\n";
                    uiBuffers_[0] = destr(tempMap[0]["key"]);
                    uiBuffers_[1] = destr(tempMap[0]["val"]);
                    uiBuffers_[2] = destr(tempMap[1]["key"]);
                    uiBuffers_[3] = destr(tempMap[1]["val"]);
                    std::cout << uiBuffers_[2] << " : " << uiBuffers_[3] << "\n";
                }
            }
            else
            {
                memset(&(uiBuffers_[0]), 0, 64);
                memset(&(uiBuffers_[1]), 0, 64);
                memset(&(uiBuffers_[2]), 0, 64);
                memset(&(uiBuffers_[3]), 0, 64);
                tempMapSize = 2;
            }

            std::cout << "Finished " << __FUNCTION__ << "\n";
            ImGui::OpenPopup(uiStrings_.editInfo);
        }

        popEditDouble(row_n);

        ImGui::EndPopup();
    }
}

void UIassembly::editPathContext(int row_n) {

    if (ImGui::BeginPopup(uiData_.getCardElem(CNAME, row_n)))
    {
        //MyItem* item = &items[row_n];

        
        if (ImGui::Selectable(destr(uiGenerated_[row_n]["buttonOpenFile"]))) {

            int row_x = uiData_.getCardIdx(row_n);

            std::cout << "path1 = " << funcGetDataPathNew(getFileNameOnly(uiData_.getCards()[row_x].getName())) << "\n";

            ShellExecuteA(NULL, "open", destr(stringConvert(uiData_.getCards()[row_x].getPath(), CP_UTF8, 0, CP_THREAD_ACP, 0)), NULL, NULL, SW_SHOWDEFAULT);
            ImGui::CloseCurrentPopup();
        }
        
        if (ImGui::Selectable(destr(uiGenerated_[row_n]["buttonOpenPath"]))) {


            int row_x = uiData_.getCardIdx(row_n);
            char* value2 = destr(stringConvert(filePathFull(uiData_.getCards()[row_x].getPath()), CP_UTF8, 0, CP_THREAD_ACP, 0));

            openFileFolder(value2);

            ImGui::CloseCurrentPopup();
        }
        //ImGui::SameLine();
        

        if (ImGui::Selectable(destr(uiGenerated_[row_n]["buttonPath"]))) {


            int row_x = uiData_.getCardIdx(row_n);
            std::cout << "\n BEGIN Path = " << uiData_.getUI().getAUI(row_x).Path << " vs " << uiData_.getCards()[row_x].getPath() << "; " << row_n << "\n";


            char* newPath = winOpenAndProcessFl(uiData_.getCards()[row_x].getName());

            if (newPath != "NULL") {

                //Cards.getCards()[row_x].setPath(newPath);
                //Cards.getUI()[row_n].Path = Cards.getCards()[row_x].getPath();

                uiData_.setData(row_n, "--", "--", newPath);

                std::cout << "Path = " << uiData_.getUI().getAUI(row_x).Path << " vs " << uiData_.getCards()[row_x].getPath() << "; " << row_n << "\n";
                ImGui::CloseCurrentPopup();
            }


        }
        ImGui::EndPopup();
    }

}


void UIassembly::popSearch() {

    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    ImGuiIO io = ImGui::GetIO();
    ImGui::SetNextWindowSize({ 2 * io.DisplaySize.x / 3, 2 * io.DisplaySize.y / 3 });

    if (ImGui::BeginPopupModal(uiStrings_.button_search, NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {

        ImGui::Separator();

        if (uiBuffers_.size() == 5) {

            ImGui::Text(destr(uiStrings_.nameSearch));
            ImGui::InputText(uiStrings_.table_name, uiBuffers_[0], 64, ImGuiInputTextFlags_CharsNoBlank);

            ImGui::Text(destr(uiStrings_.tagsSearch));
            ImGui::InputText(uiStrings_.table_tags, uiBuffers_[1], 64, ImGuiInputTextFlags_CharsNoBlank);

            ImGui::Text(destr(uiStrings_.pathSearch));
            ImGui::InputText(uiStrings_.table_path, uiBuffers_[2], 64, ImGuiInputTextFlags_CharsNoBlank);

            ImGui::Text(destr(uiStrings_.infoSearch));
            ImGui::InputText(uiStrings_.search_key, uiBuffers_[3], 64, ImGuiInputTextFlags_CharsNoBlank);
            ImGui::SameLine();
            ImGui::InputText(uiStrings_.search_val, uiBuffers_[4], 64, ImGuiInputTextFlags_CharsNoBlank);




            if (ImGui::Button(uiStrings_.popOK, ImVec2(120, 0))) {

                searchCards.clear();
                char* Sname = "--";
                if (uiBuffers_[0] != "" && uiBuffers_[0][0] != '\0') Sname = uiBuffers_[0];
                char* Stags = "--";
                if (uiBuffers_[1] != "" && uiBuffers_[0][1] != '\0') Stags = uiBuffers_[1];
                char* Spath = "--";
                if (uiBuffers_[2] != "" && uiBuffers_[0][2] != '\0') Spath = uiBuffers_[2];

                char* SinfoKey = "--";
                if (uiBuffers_[3] != "" && uiBuffers_[0][3] != '\0') SinfoKey = uiBuffers_[3];
                char* Sinfoval = "--";
                if (uiBuffers_[4] != "" && uiBuffers_[0][4] != '\0') Sinfoval = uiBuffers_[4];

                if (searchCards.empty()) {
                    for (int n = 0; n < uiData_.getCards().size(); n++)
                    {
                        if (uiData_.getCards()[n].getFind(Sname, Stags, Spath, SinfoKey, Sinfoval) > 0) searchCards.push_back(uiData_.getCards()[n]);
                    }
                    //setDataArraysItems(searchCards, searchItems);

                    searchItems.clear();

                    if (searchItems.Size == 0)
                    {
                        searchItems.resize(searchCards.size(), MyItem());

                        for (int n = 0; n < searchItems.Size; n++)
                        {
                            const int template_n = n % searchCards.size();
                            MyItem& item = searchItems[n];
                            item.ID = n;

                            item.Name = searchCards[template_n].getName();
                            item.Tags = searchCards[template_n].getTags();
                            item.Path = searchCards[template_n].getPath();
                            item.Info = searchCards[template_n].getInfoChar();


                        }
                    }
                }


            }
            if (ImGui::Button(uiStrings_.popBACK, ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }

            if (!searchCards.empty()) {
                //setTableClipItm(searchCards, searchItems);
            }

            ImGui::SetItemDefaultFocus();
            ImGui::SameLine();

            ImGui::EndPopup();
        }
    }

}

