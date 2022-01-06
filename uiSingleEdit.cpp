#include <fstream>
#include <iostream> 
#include <imgui.h>
#include "uiSingleEdit.h"
#include "testTools.h"


void UIeditSingle::popEditSimple(libCardAssembly& uiData_, int row_n) {

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

void UIeditSingle::editTagsContext(libCardAssembly& uiData_, int row_n) {

    if (ImGui::BeginPopup(uiData_.getUI().Tags(row_n))) {


        //
        if (ImGui::SmallButton(buttonEditName)) {

            int row_x = uiData_.getCardIdx(row_n);

            readyBuffers(1);

            uiBuffers_[0] = destr(uiData_.getCards()[row_x].getTags());
            //std::cout << __FUNCTION__ << " readyBuffers " << "\n";


            ImGui::OpenPopup(uiStrings_.editTags);
        }

        popEditSimple(uiData_, row_n);

        ImGui::EndPopup();
    }
}

