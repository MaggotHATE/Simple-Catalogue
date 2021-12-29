#pragma once
#include <string>

class translateDB {
public:
    char* name_app;
    char* intro;
    char* button_create;
    char* button_search;
    char* search_key;
    char* search_val;
    std::string nameSearch;
    std::string tagsSearch;
    std::string pathSearch;
    std::string infoSearch;
    char* check_catalogue;
    char* table_name;
    char* table_tags;
    char* table_info;
    char* table_path;
    char* create_name;
    char* create_tags;
    char* create_info;
    char* create_path;
    char* refresh;
    char* edit;
    char* editTags;
    char* editInfo;
    char* info;
    char* add_path;
    char* open_num;
    char* open_folder_num;
    char* edit_path_num;
    char* toolTip;
    char* popOK;
    char* popBACK;
    int item_current = 0;
};
