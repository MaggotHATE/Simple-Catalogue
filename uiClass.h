#pragma once

#include "libCardAssembly.h"
#include "uiCommons.h"
#include "translateDB.h"
#include "imgUIsort.h"
#include <tchar.h>
#include <string>
#include <array>

using namespace my_item;

class UIassembly: public UIcommons {
protected:
    translateDB uiStrings_;
    std::map<int, std::map<std::string, char*>> uiGenerated_;
    libCardAssembly uiData_;
    std::vector<libCard> searchCards;
    ImVector<MyItem> searchItems;
    //UIcommons searchBuffers;
public:
    UIassembly() = default;
    UIassembly(translateDB _translations, libCardAssembly _data);

    void loadTransl(translateDB _translations);
    void setData(libCardAssembly _data);
    libCardAssembly& getData();
    translateDB& getStrings();
    char* getGenerated(int row_n, char* stringName);
    //void SearchBuffers(int size);
    void setStrings(std::string fileTranslateEn, std::vector<char*> translationsList, int item_current);
    void setGenereated(int row_n);

    //void popEditSimple(int row_n);
    //void popEditDouble(int row_n);
    //void popSearch();

    //void editTagsContext(int row_n);
    //void editInfoContext(int row_n);
    //void editPathContext(int row_n);

    void sortAndGenerate(int idx);

    void clearData();
    //void clearStrings();
    void clearGenerated();

    void clear();

};
