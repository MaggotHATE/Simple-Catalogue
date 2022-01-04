#include "uiCommons.h"
#include <fstream>
#include <iostream>

void UIcommons::clearBuffers() {
    for (int i = 0; i < uiBuffers_.size(); i++) {
        delete(uiBuffers_[i]);
    }
    uiBuffers_.clear();
}

void UIcommons::readyBuffers(int size) {
    clearBuffers();
    uiBuffers_.resize(size);
    for (int i = 0; i < uiBuffers_.size(); i++) {
        uiBuffers_[i] = new char[64];
    }

    std::cout << __FUNCTION__ << " to " << uiBuffers_.size() << "\n";
}
