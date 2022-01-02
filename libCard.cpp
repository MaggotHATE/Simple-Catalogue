#include "libCard.h"
#include <fstream>
#include <iostream> 

//bool isdebug;



libCard::libCard(char* name_C, char* tags_C, char* path_C, CharMap info_C) : name_(name_C), tags_(tags_C), path_(path_C), info_(info_C)
{
    if (isdebug == true) {
        std::cout << "\n Created libCard: \n Name = " << name_ << "\n Tags = " << tags_ << "\n Path = " << path_ << "\n";

        CharMap::iterator it = info_.begin();
        // Iterate over the map using Iterator till end.
        while (it != info_.end())
        {
            // Accessing KEY from element pointed by it.
            char* key = it->first;
            // Accessing VALUE from element pointed by it.
            char* val = it->second;
            std::cout << "Info " << std::distance(it, info_.end()) << " = " << key << " : " << val << "; \n";
            // Increment the Iterator to point to next entry
            it++;
        }
        std::cout << "\n";
    }
}

char* libCard::getName() {
    return name_;
}

char* libCard::getTags() {
    return tags_;
}

char* libCard::getPath() {
    return path_;
}


CharMap libCard::getInfo() {
    return info_;
}

char* libCard::getInfoChar() {
    return funcAssembleFromMap(info_);
}

bool libCard::setName(char* name) {
    if (name != '\0') {
        name_ = destr(name);
        return true;
    }
    else {
        return false;
    }
}

bool libCard::setTags(char* tags) {
    if (tags != '\0') {
        tags_ = destr(tags);
        std::cout << "Set tags_ to " << tags << "\n";
        return true;
    }
    else {
        return false;
    }
}

bool libCard::setInfo(std::map<char*, char*> info) {
    if (!info.empty()) {
        info_ = info;
        return true;
    }
    else {
        return false;
    }
}

bool libCard::setPath(char* path) {
    if (path != '\0') {
        path_ = destr(path);
        return true;
        //std::cout << "Set path_ to " << path_ << "\n";
    }
    else {
        return false;
    }
}

int libCard::getFind(char* name, char* tags, char* path, char* infoKey, char* infoVal) {
    int result = 0;
    if (name != "--") {
        std::string Sname = name_;
        if (Sname.find(name) < Sname.npos) {
            result += 1;
            std::cout << "Found in name_: " << name << "\n";
        }
    }
    if (tags != "--") {
        std::string Stags = tags_;
        if (Stags.find(tags) < Stags.npos) {
            result += 2;
            std::cout << "Found in tags_: " << tags << "\n";
        }
    }
    if (path != "--") {
        std::string Spath = path_;
        if (Spath.find(path) < Spath.npos) {
            result += 4;
            std::cout << "Found in path_: " << path << "\n";
        }
    }
    if (infoKey != "--" || infoVal != "--") {
        std::map<char*, char*>::iterator it = info_.begin();
        // Iterate over the map using Iterator till end.
        int subCnt = 0;
        while (it != info_.end())
        {

            std::string key = it->first;
            std::string val = it->second;

            if (key.find(infoKey) < key.npos) {
                subCnt += 1;
            }
            if (val.find(infoVal) < val.npos) {
                subCnt += 1;
            }

            it++;
        }
        if (subCnt > 0) {
            result += 8;
            std::cout << "Found in info_: " << infoVal << " or " << infoVal << "\n";
        }
    }

    return result;
}

bool libCard::empty() {
    if (name_ || tags_ || path_) return false;
    return true;
}
