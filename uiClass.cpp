#include <fstream>
#include <iostream> 
#include <imgui.h>
#include "uiClass.h"
#include "testTools.h"



void UIassembly::loadTransl(translateDB _translations) {
    uiStrings_ = _translations;
}

void UIassembly::setData(libCardAssembly _data) {
    uiData_ = _data;
}

libCardAssembly& UIassembly::getData() {
    return uiData_ ;
}

translateDB& UIassembly::getStrings() {
    return uiStrings_;
}

void UIassembly::setStrings(std::string fileTranslateEn, std::vector<char*> translationsList, int item_current) {
    uiStrings_ = translateDB(fileTranslateEn, translationsList, item_current);
}

void UIassembly::setGenereated(int row_n) {
    uiGenerated_[row_n]["name"] = uiData_.getCardElem(CNAME, row_n);
    uiGenerated_[row_n]["nameOnlyStr"] = getFileNameOnly(destr(uiGenerated_[row_n]["name"]));
    uiGenerated_[row_n]["buttonEditName"] = destr(uiStrings_.editTags + funcGetIdxNameStr(uiGenerated_[row_n]["nameOnlyStr"], 0));
    uiGenerated_[row_n]["buttonInfoEditName"] = destr(uiStrings_.editInfo + funcGetIdxNameStr(uiGenerated_[row_n]["nameOnlyStr"], 0));
    uiGenerated_[row_n]["buttonPath"] = destr(uiStrings_.edit_path_num + std::to_string(row_n));
    uiGenerated_[row_n]["buttonOpenPath"] = destr(uiStrings_.open_folder_num + std::to_string(row_n));
    uiGenerated_[row_n]["buttonOpenFile"] = destr(uiStrings_.open_num + std::to_string(row_n));
}

char* UIassembly::getGenerated(int row_n, char* stringName) {
    return uiGenerated_[row_n][stringName];
}

UIassembly::UIassembly(translateDB _translations, libCardAssembly _data, char*& Config) {

    clearData();

    loadTransl(_translations);
    setData(_data);
    //if (_data.getUI().Size() > 1) sortAndGenerate(0);
    for (int i = 0; i < uiData_.getCards().size(); i++) {
        setGenereated(i);
        std::cout << __FUNCTION__ << " : " << i << " = " << uiGenerated_[i]["buttonInfoEditName"] << "\n";
    }
    pathConfig = Config;
}

void UIassembly::sortAndGenerate(int idx) {
    uiData_.getUI().sortUI(idx);

    for (int i = 0; i < uiData_.getCards().size(); i++) {
        setGenereated(i);
        std::cout << __FUNCTION__ << " : " << i << " = " << uiGenerated_[i]["buttonInfoEditName"] << "\n";
    }
}

void UIassembly::clearData() {
    std::cout << __FUNCTION__ << " START " << "\n";
    uiData_.clearC();
    uiData_.clearV();
}
//void UIassembly::clearStrings() {
//
//}
void UIassembly::clearGenerated() {
    std::cout << __FUNCTION__ << " START " << "\n";
    for (int i = 0; i < uiData_.getCards().size(); i++) {
        //delete(uiGenerated_[i]["name"]);
        delete(uiGenerated_[i]["nameOnlyStr"]);
        delete(uiGenerated_[i]["buttonEditName"]);
        delete(uiGenerated_[i]["buttonInfoEditName"]);
        delete(uiGenerated_[i]["buttonPath"]);
        delete(uiGenerated_[i]["buttonOpenPath"]);
        delete(uiGenerated_[i]["buttonOpenFile"]);
    }

    uiGenerated_.clear();
}

void UIassembly::clear() {
    clearGenerated();
    clearData();
    std::cout << __FUNCTION__ << " FINISHED " << "\n";
}


