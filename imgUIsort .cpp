#include "imgUIsort.h"
using namespace my_item;

const ImGuiTableSortSpecs* MyItem::s_current_sort_specs1 = NULL;

int IMGUI_CDECL MyItem::CompareWithSortSpecs1(const void* lhs, const void* rhs)
{
	const MyItem* a = (const MyItem*) lhs;
	const MyItem* b = (const MyItem*) rhs;
	for(int n = 0; n < s_current_sort_specs1->SpecsCount; n++)
	{
		// Here we identify columns using the ColumnUserID value that we ourselves passed to TableSetupColumn()
		// We could also choose to identify columns based on their index (sort_spec->ColumnIndex), which is simpler!
		const ImGuiTableColumnSortSpecs* sort_spec = &s_current_sort_specs1->Specs[n];
		int delta = 0;
		switch(sort_spec->ColumnUserID)
		{
			case MyItemColumnID_ID:			delta = (a->ID - b->ID);                break;
			case MyItemColumnID_Name:		delta = (strcmp(a->Name, b->Name));     break;
			case MyItemColumnID_Tags:       delta = (strcmp(a->Tags, b->Tags));		break;
			case MyItemColumnID_Info:		delta = (strcmp(a->Info, b->Info));     break;
			case MyItemColumnID_Path:		delta = (strcmp(a->Path, b->Path));     break;
			default: IM_ASSERT(0); break;
		}
		if(delta > 0)
			return (sort_spec->SortDirection == ImGuiSortDirection_Ascending) ? +1 : -1;
		if(delta < 0)
			return (sort_spec->SortDirection == ImGuiSortDirection_Ascending) ? -1 : +1;
	}

	// qsort() is instable so always return a way to differenciate items.
	// Your own compare function may want to avoid fallback on implicit sort specs e.g. a Name compare if it wasn't already part of the sort specs.
	return (a->ID - b->ID);
}

void MyItem::Clear() {
    //delete(ID);
    //delete[](Name);
    //delete[](Tags);
    //delete[](Info);
    //delete[](Path);
}
