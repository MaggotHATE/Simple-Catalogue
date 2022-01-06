#pragma once

#include "libCardAssembly.h"
#include "uiCommons.h"
#include "translateDB.h"
#include "imgUIsort.h"
#include <tchar.h>
#include <string>
#include <array>

class UIeditDouble : public UIcommons {
public:
    translateDB uiStrings_;
    char* buttonInfoEditName;
    void popEditDouble(libCardAssembly& uiData_, int row_n);
    void editInfoContext(libCardAssembly& uiData_, int row_n);
};

