#pragma once
#include <tchar.h>
#include <vector>

class UIcommons {
protected:
    std::vector<char*> uiBuffers_;
public:
    void clearBuffers();
    void readyBuffers(int size);
};
