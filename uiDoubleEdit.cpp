#include <fstream>
#include <iostream> 
#include <imgui.h>
#include "uiDoubleEdit.h"
#include "testTools.h"

void UIeditDouble::popEditDouble(libCardAssembly& uiData_, int row_n) {

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

        for (int i = 0; i < uiBuffers_.size(); i += 2) {
            //std::cout << i << " KEY " << i + 1 << "\n";
            ImGui::InputText(('#' + std::to_string(i) + " key").c_str(), uiBuffers_[i], 64);
            ImGui::SameLine();
            //std::cout << i << " VAL " << i + 1 << "\n";
            ImGui::InputText(('#' + std::to_string(i) + " val").c_str(), uiBuffers_[i + 1], 64);

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

void UIeditDouble::editInfoContext(libCardAssembly& uiData_, int row_n) {


    if (ImGui::BeginPopup(uiData_.getUI().getAUI(row_n).Info))
    {

        int row_x = uiData_.getCardIdx(row_n);
        int tempMapSize = 1;
        //MyItem* item = &items[row_n];

        if (ImGui::SmallButton(buttonInfoEditName)) {

            char* infoG = uiData_.getACard(row_x).getInfoChar();

            if (infoG != "") {
                std::vector<std::map<std::string, std::string>> tempMap = funcGetInfoPairs(uiData_.getCardElem(CNAME, row_n));
                tempMapSize = tempMap.size();

                readyBuffers(tempMap.size() * 2);

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

        popEditDouble(uiData_, row_n);

        ImGui::EndPopup();
    }
}
