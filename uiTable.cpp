#include <fstream>
#include <iostream> 
#include "uiTable.h"
#include "testTools.h"

void UItable::setGenerated(std::string buttonEditName, std::string buttonInfoEditName, int row_n) {
    tagUI.buttonEditName = destr(buttonEditName);
    infoUI.buttonInfoEditName = destr(buttonInfoEditName);
}

void UItable::popSearch(UIassembly& Cards) {
    searchUI.popSearch(Cards.getData());
}

void UItable::SearchBuffers(int size) {
    searchUI.SearchBuffers(size);
}

void UItable::setTableClip(UIassembly& Cards) {

    //std::cout << __FUNCTION__ << " BEGINS " << "\n";

    libUI& items = Cards.getData().getUI();
    tagUI.uiStrings_ = Cards.getStrings();
    infoUI.uiStrings_ = Cards.getStrings();
    searchUI.uiStrings_ = Cards.getStrings();
    // Create item list
    
    const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();
    // Options
    static ImGuiTableFlags flags =
        ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Sortable | ImGuiTableFlags_ScrollY
        | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_NoBordersInBody | ImGuiTableFlags_ScrollX;

    if (ImGui::BeginTable(Cards.getStrings().check_catalogue, 5, flags))
    {
        // Declare columns
        // We use the "user_id" parameter of TableSetupColumn() to specify a user id that will be stored in the sort specifications.
        // This is so our sort function can identify a column given our own identifier. We could also identify them based on their index!
        // Demonstrate using a mixture of flags among available sort-related flags:
        // - ImGuiTableColumnFlags_DefaultSort
        // - ImGuiTableColumnFlags_NoSort / ImGuiTableColumnFlags_NoSortAscending / ImGuiTableColumnFlags_NoSortDescending
        // - ImGuiTableColumnFlags_PreferSortAscending / ImGuiTableColumnFlags_PreferSortDescending
        ImGui::TableSetupColumn("   #", ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_ID);
        ImGui::TableSetupColumn(Cards.getStrings().table_name, ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_Name);
        ImGui::TableSetupColumn(Cards.getStrings().table_tags, ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_Tags);
        ImGui::TableSetupColumn(Cards.getStrings().table_info, ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_Info);
        ImGui::TableSetupColumn(Cards.getStrings().table_path, ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_Path);//
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

                if (size > 1) Cards.sortAndGenerate(0);
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
                
                //int ID = items[row_n].ID;
                ImGui::PushID(items.ID(row_n));
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%04d", items.ID(row_n));
                ImGui::TableNextColumn();

                char* name = items.Name(row_n);
                if (ImGui::Button(funcGetIdxName(name, 0))) openFile1(name);
                ImGui::TableNextColumn();

                ImGui::Text(items.Tags(row_n));
                if (ImGui::IsItemHovered()) ImGui::SetTooltip(Cards.getStrings().toolTip);
                if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(1)) {
                    ImGui::OpenPopupContextItem(items.Tags(row_n));
                }
                //editTagsContext(Cards, ID);

                //if (ImGui::BeginPopup(items.Tags(row_n)))
                //{
                    //editTagsContext(Cards.getData(), row_n);
                tagUI.buttonEditName = destr(Cards.getGenerated(row_n, "buttonEditName"));
                tagUI.editTagsContext(Cards.getData(), row_n);
                //ImGui::EndPopup();
            //}

                ImGui::TableNextColumn();

                ImGui::Text(items.Info(row_n));
                if (ImGui::IsItemHovered()) ImGui::SetTooltip(Cards.getStrings().toolTip);
                if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(1)) {
                    ImGui::OpenPopupContextItem(items.Info(row_n));
                }
                //editInfoContext(Cards.getData(), row_n);
                infoUI.buttonInfoEditName = destr(Cards.getGenerated(row_n, "buttonInfoEditName"));
                infoUI.editInfoContext(Cards.getData(), row_n);

                ImGui::TableNextColumn();

                ImGui::Text(items.Path(row_n));
                if (ImGui::IsItemHovered()) ImGui::SetTooltip(Cards.getStrings().toolTip);
                if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(1)) {
                    ImGui::OpenPopupContextItem(name);
                }
                //editPathContext(Cards.getData(), row_n);
                pathUI.buttonOpenFile = destr(Cards.getGenerated(row_n, "buttonOpenFile"));
                pathUI.buttonOpenPath = destr(Cards.getGenerated(row_n, "buttonOpenPath"));
                pathUI.buttonPath = destr(Cards.getGenerated(row_n, "buttonPath"));
                pathUI.editPathContext(Cards.getData(), row_n);


                ImGui::PopID();
            }



        ImGui::EndTable();
    }
    //std::cout << __FUNCTION__ << " ENDS " << "\n";
}

