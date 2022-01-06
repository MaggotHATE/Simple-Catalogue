#pragma once

#include "libCardAssembly.h"
#include "uiCommons.h"
#include "translateDB.h"
#include "imgUIsort.h"
#include <tchar.h>
#include <string>
#include <array>

class UIeditSingle : public UIcommons {
public:
    translateDB uiStrings_;
    char* buttonEditName;
    void editTagsContext(libCardAssembly& uiData_, int row_n);
    void popEditSimple(libCardAssembly& uiData_, int row_n);
};
