#pragma once

#include "imgUIsort.h"
#include "jsonTools.h"


enum cardItem {
    CNAME = 1,
    CTAGS = 2,
    CPATH = 4,
    CINFO = 8
};


class libCard {
public:
    libCard(char* name_C, char* tags_C, char* path_C, CharMap info_C);

    char* getName();
    char* getTags();
    char* getPath();
    bool setName(char* name);
    bool setTags(char* tags);
    bool setPath(char* path);
    CharMap getInfo();
    char* getInfoChar();
    bool setInfo(CharMap info);
    int getFind(char* name = "--", char* tags = "--", char* path = "--", char* infoKey = "--", char* infoVal = "--");
    bool empty();

    char* getItem(cardItem flag, int idx);

private:
    char* name_;
    char* tags_;
    char* path_;
    CharMap info_;
};


