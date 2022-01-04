#pragma once

#include "libCardAssembly.h"
#include "uiCommons.h"
#include "translateDB.h"
#include "imgUIsort.h"
#include <tchar.h>
#include <string>
#include <array>


class UIassembly: public UIcommons {
protected:
    translateDB uiStrings_;
    std::map<int, std::map<char*, std::string>> uiGenerated_;
    libCardAssembly uiData_;

public:
    UIassembly() = default;
    UIassembly(translateDB _translations, libCardAssembly _data);

    void loadTransl(translateDB _translations);
    void setData(libCardAssembly _data);
    libCardAssembly& getData();
    void setGenereated(int row_n);

    void popEditSimple(int row_n);
    void popEditDouble(int row_n);

    void editTagsContext(int row_n);
    void editInfoContext(int row_n);

    void clearData();
    //void clearStrings();
    void clearGenerated();

};
