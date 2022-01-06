#include <fstream>
#include <iostream> 
#include <imgui.h>
#include "uiSearch.h"
#include "testTools.h"


void UIsearch::SearchBuffers(int size) {
    readyBuffers(size);
    for (int i = 0; i < uiBuffers_.size(); i++) {
        memset(&(uiBuffers_[i][0]), 0, 64);
        std::cout << __FUNCTION__ << " = " << strlen(uiBuffers_[i]) << "\n";
    }
}

void UIsearch::popSearch(libCardAssembly uiData_) {

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
                if (uiBuffers_[1] != "" && uiBuffers_[1][0] != '\0') Stags = uiBuffers_[1];
                char* Spath = "--";
                if (uiBuffers_[2] != "" && uiBuffers_[2][0] != '\0') Spath = uiBuffers_[2];

                char* SinfoKey = "--";
                if (uiBuffers_[3] != "" && uiBuffers_[3][0] != '\0') SinfoKey = uiBuffers_[3];
                char* Sinfoval = "--";
                if (uiBuffers_[4] != "" && uiBuffers_[4][0] != '\0') Sinfoval = uiBuffers_[4];

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
                setTableClipItm(searchCards);
            }

            ImGui::SetItemDefaultFocus();
            ImGui::SameLine();

            ImGui::EndPopup();
        }
    }

}

void UIsearch::sortAndGenerate(libCardAssembly uiData_, int idx) {
    uiData_.getUI().sortUI(idx);
}

void UIsearch::setTableClipItm(libCardAssembly uiData_) {
    std::vector<libCard> libCards = uiData_.getCards();
    libUI items = uiData_.getUI();

    // Create item list

    const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();
    // Options
    static ImGuiTableFlags flags =
        ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Sortable | ImGuiTableFlags_ScrollY
        | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_NoBordersInBody | ImGuiTableFlags_ScrollX;

    if (ImGui::BeginTable(uiStrings_.check_catalogue, 5, flags))
    {
        // Declare columns
        // We use the "user_id" parameter of TableSetupColumn() to specify a user id that will be stored in the sort specifications.
        // This is so our sort function can identify a column given our own identifier. We could also identify them based on their index!
        // Demonstrate using a mixture of flags among available sort-related flags:
        // - ImGuiTableColumnFlags_DefaultSort
        // - ImGuiTableColumnFlags_NoSort / ImGuiTableColumnFlags_NoSortAscending / ImGuiTableColumnFlags_NoSortDescending
        // - ImGuiTableColumnFlags_PreferSortAscending / ImGuiTableColumnFlags_PreferSortDescending
        ImGui::TableSetupColumn("   #", ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_ID);
        ImGui::TableSetupColumn(uiStrings_.table_name, ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_Name);
        ImGui::TableSetupColumn(uiStrings_.table_tags, ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_Tags);
        ImGui::TableSetupColumn(uiStrings_.table_info, ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_Info);
        ImGui::TableSetupColumn(uiStrings_.table_path, ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_Path);//
        ImGui::TableSetupScrollFreeze(1, 1); // Make row always visible
        ImGui::TableHeadersRow();



        // Sort our data if sort specs have been changed!
        if (ImGuiTableSortSpecs* sorts_specs = ImGui::TableGetSortSpecs())
            if (sorts_specs->SpecsDirty)
            {
                MyItem::s_current_sort_specs1 = sorts_specs; // Store in variable accessible by the sort function.

                MyItem item = items.getAUI(0);
                int size = items.Size();

                //std::cout << size << " : " << sizeof(item) << ";  " << item.Name << "\n";

                if (size > 1) sortAndGenerate(uiData_, 0);
                // items.sortUI(0);
                //qsort(&item, (size_t)size, sizeof(item), MyItem::CompareWithSortSpecs1);

                MyItem::s_current_sort_specs1 = NULL;
                sorts_specs->SpecsDirty = false;
            }


        // Demonstrate using clipper for large vertical lists
        ImGuiListClipper clipper;
        clipper.Begin(items.Size());

        while (clipper.Step())
            for (int row_n = clipper.DisplayStart; row_n < clipper.DisplayEnd; row_n++)
            {

                ImGui::PushID(items.ID(row_n));
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%04d", items.ID(row_n));
                ImGui::TableNextColumn();

                char* name = items.Name(row_n);
                if (ImGui::Button(funcGetIdxName(name, 0))) openFile1(name);
                ImGui::TableNextColumn();

                ImGui::Text(items.Tags(row_n));
                ImGui::TableNextColumn();

                ImGui::Text(items.Info(row_n));
                ImGui::TableNextColumn();

                ImGui::Text(items.Path(row_n));

                ImGui::PopID();
            }

        ImGui::EndTable();
    }
}
