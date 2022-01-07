#pragma once
#include "libCardAssembly.h"
#include "uiCommons.h"
#include "translateDB.h"
#include "imgUIsort.h"
#include <tchar.h>
#include <string>
#include <array>

using namespace my_item;

class UIsearch : public UIcommons {
protected:
    std::vector<libCard> searchCards;
    ImVector<MyItem> searchItems;
public:
    translateDB uiStrings_;
    //char* buttonEditName;

    void popSearch(libCardAssembly uiData_);
    void setTableClipItm(libCardAssembly uiData_);
    void SearchBuffers(int size);
    void sortAndGenerate(libCardAssembly uiData_, int idx);
};
