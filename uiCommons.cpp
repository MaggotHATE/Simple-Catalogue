#include "uiCommons.h"
#include <fstream>
#include <iostream>

void UIcommons::clearBuffers() {
    std::cout << __FUNCTION__ << " all " << uiBuffers_.size() << "\n";
    for (int i = 0; i < uiBuffers_.size(); i++) {
        std::cout << " deleting " << uiBuffers_[i] << "\n";
        if (!isEmptyItem(i)) delete[](uiBuffers_[i]);
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

void UIcommons::clearXBuffers(int i, int j) {
    for (int x = i; x <= j; x++) {
        delete(uiBuffers_[x]);
    }
}

bool UIcommons::isEmptyItem(int idx) {
    if (uiBuffers_[idx] != "" && uiBuffers_[idx][0] != '\0') return false; else return true;
}
