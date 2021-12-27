#pragma once
#include "imgui.h"
#include <ctype.h>          // toupper
#include <limits.h>         // INT_MIN, INT_MAX
#include <math.h>           // sqrtf, powf, cosf, sinf, floorf, ceilf
#include <stdio.h>          // vsnprintf, sscanf, printf
#include <stdlib.h>         // NULL, malloc, free, atoi
#include <stdint.h>         // intptr_t

#ifndef IMGUI_CDECL
#ifdef _MSC_VER
#define IMGUI_CDECL __cdecl
#else
#define IMGUI_CDECL
#endif
#endif


namespace
{
    // We are passing our own identifier to TableSetupColumn() to facilitate identifying columns in the sorting code.
    // This identifier will be passed down into ImGuiTableSortSpec::ColumnUserID.
    // But it is possible to omit the user id parameter of TableSetupColumn() and just use the column index instead! (ImGuiTableSortSpec::ColumnIndex)
    // If you don't use sorting, you will generally never care about giving column an ID!
    enum MyItemColumnID
    {
        MyItemColumnID_ID,
        MyItemColumnID_Name,
        MyItemColumnID_Tags,
        MyItemColumnID_Info,
        MyItemColumnID_Path
    };

    struct MyItem
    {
        int     ID;
        char* Name;
        char* Tags;
        char* Info;
        char* Path;


        // We have a problem which is affecting _only this demo_ and should not affect your code:
        // As we don't rely on std:: or other third-party library to compile dear imgui, we only have reliable access to qsort(),
        // however qsort doesn't allow passing user data to comparing function.
        // As a workaround, we are storing the sort specs in a static/global for the comparing function to access.
        // In your own use case you would probably pass the sort specs to your sorting/comparing functions directly and not use a global.
        // We could technically call ImGui::TableGetSortSpecs() in CompareWithSortSpecs(), but considering that this function is called
        // very often by the sorting algorithm it would be a little wasteful.
        static const ImGuiTableSortSpecs* s_current_sort_specs1;

        // Compare function to be used by qsort()
        static int IMGUI_CDECL CompareWithSortSpecs1(const void* lhs, const void* rhs)
        {
            const MyItem* a = (const MyItem*)lhs;
            const MyItem* b = (const MyItem*)rhs;
            for (int n = 0; n < s_current_sort_specs1->SpecsCount; n++)
            {
                // Here we identify columns using the ColumnUserID value that we ourselves passed to TableSetupColumn()
                // We could also choose to identify columns based on their index (sort_spec->ColumnIndex), which is simpler!
                const ImGuiTableColumnSortSpecs* sort_spec = &s_current_sort_specs1->Specs[n];
                int delta = 0;
                switch (sort_spec->ColumnUserID)
                {
                case MyItemColumnID_ID:             delta = (a->ID - b->ID);                break;
                case MyItemColumnID_Name:           delta = (strcmp(a->Name, b->Name));     break;
                case MyItemColumnID_Tags:       delta = (strcmp(a->Tags, b->Tags));    break;
                case MyItemColumnID_Info:    delta = (strcmp(a->Info, b->Info));     break;
                case MyItemColumnID_Path:    delta = (strcmp(a->Path, b->Path));     break;
                default: IM_ASSERT(0); break;
                }
                if (delta > 0)
                    return (sort_spec->SortDirection == ImGuiSortDirection_Ascending) ? +1 : -1;
                if (delta < 0)
                    return (sort_spec->SortDirection == ImGuiSortDirection_Ascending) ? -1 : +1;
            }

            // qsort() is instable so always return a way to differenciate items.
            // Your own compare function may want to avoid fallback on implicit sort specs e.g. a Name compare if it wasn't already part of the sort specs.
            return (a->ID - b->ID);
        }
    };
    const ImGuiTableSortSpecs* MyItem::s_current_sort_specs1 = NULL;
}
