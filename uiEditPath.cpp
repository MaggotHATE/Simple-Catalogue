#include <fstream>
#include <iostream> 
#include <imgui.h>
#include "uiEditPath.h"
#include "testTools.h"

void UIeditPath::editPathContext(libCardAssembly& uiData_, int row_n, std::map<std::string, char*> buttonsNames) {

    if (ImGui::BeginPopup(uiData_.getCardElem(CNAME, row_n)))
    {
        //MyItem* item = &items[row_n];


        if (ImGui::Selectable(buttonsNames["buttonOpenFile"])) {

            int row_x = uiData_.getCardIdx(row_n);

            std::cout << "path1 = " << funcGetDataPathNew(getFileNameOnly(uiData_.getCards()[row_x].getName())) << "\n";

            ShellExecuteA(NULL, "open", destr(stringConvert(uiData_.getCards()[row_x].getPath(), CP_UTF8, 0, CP_THREAD_ACP, 0)), NULL, NULL, SW_SHOWDEFAULT);
            ImGui::CloseCurrentPopup();
        }

        if (ImGui::Selectable(buttonsNames["buttonOpenPath"])) {


            int row_x = uiData_.getCardIdx(row_n);
            char* value2 = destr(stringConvert(filePathFull(uiData_.getCards()[row_x].getPath()), CP_UTF8, 0, CP_THREAD_ACP, 0));

            openFileFolder(value2);

            ImGui::CloseCurrentPopup();
        }
        //ImGui::SameLine();


        if (ImGui::Selectable(buttonsNames["buttonPath"])) {


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
