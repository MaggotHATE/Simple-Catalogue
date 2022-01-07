#pragma once
#include "libCardAssembly.h"
#include "uiCommons.h"
#include "translateDB.h"
#include "imgUIsort.h"
#include <tchar.h>
#include <string>
#include <array>

class UIeditPath : public UIcommons {
public:
    translateDB uiStrings_;
    //char* buttonOpenFile;
    //char* buttonOpenPath;
    //char* buttonPath;
    void editPathContext(libCardAssembly& uiData_, int row_n, std::map<std::string, char*> buttonsNames);

};
