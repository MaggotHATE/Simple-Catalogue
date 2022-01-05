#pragma once
#include <tchar.h>
#include <vector>

class UIcommons {
protected:
    std::vector<char*> uiBuffers_;
    bool isEmptyItem(int idx);
public:
    void clearBuffers();
    void readyBuffers(int size);
    void clearXBuffers(int i, int j);
};
