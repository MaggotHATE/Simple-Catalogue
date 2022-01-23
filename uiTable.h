#pragma once
#include <tchar.h>
#include <vector>
#include "uiClass.h"
#include "uiSingleEdit.h"
#include "uiDoubleEdit.h"
#include "uiEditPath.h"
#include "uiSearch.h"


class UItable {
protected:
    UIeditSingle tagUI;
    UIeditDouble infoUI;
    UIsearch searchUI;
    UIeditPath pathUI;
    std::vector<char*> names_;
    std::vector<char*> namesShort_;
public:
    void setTableClip(UIassembly& Cards);
    void setGenerated(std::string buttonEditName, std::string buttonInfoEditName, int row_n);
    void popSearch(UIassembly& Cards);
    void SearchBuffers(int size);
    void UItable::sortAndGenerate(UIassembly& Cards, int idx);
    void UItable::clearNamesAll();
};
