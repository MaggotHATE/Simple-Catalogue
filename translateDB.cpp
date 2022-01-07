#include "translateDB.h"
#include "translateDB.h"
#include "jsonTools.h"

translateDB::translateDB(std::string fileTranslateEn, std::vector<char*> translationsList, int itm) {
    fileTranslateEn = translationsList[itm];
    intro = destr(funcBaseGetFromJson("intro", fileTranslateEn));
    button_create = destr(funcBaseGetFromJson("button_create", fileTranslateEn));
    button_search = destr(funcBaseGetFromJson("button_search", fileTranslateEn));
    search_key = destr(funcBaseGetFromJson("search_key", fileTranslateEn));
    search_val = destr(funcBaseGetFromJson("search_val", fileTranslateEn));
    check_catalogue = destr(funcBaseGetFromJson("check_catalogue", fileTranslateEn));
    table_name = destr(funcBaseGetFromJson("table_name", fileTranslateEn));
    table_tags = destr(funcBaseGetFromJson("table_tags", fileTranslateEn));
    table_info = destr(funcBaseGetFromJson("table_info", fileTranslateEn));
    table_path = destr(funcBaseGetFromJson("table_path", fileTranslateEn));
    create_name = destr(funcBaseGetFromJson("create_name", fileTranslateEn));
    create_tags = destr(funcBaseGetFromJson("create_tags", fileTranslateEn));
    create_info = destr(funcBaseGetFromJson("create_info", fileTranslateEn));
    create_path = destr(funcBaseGetFromJson("create_path", fileTranslateEn));
    name_app = destr(funcBaseGetFromJson("name_app", fileTranslateEn));
    refresh = destr(funcBaseGetFromJson("refresh", fileTranslateEn));
    edit = destr(funcBaseGetFromJson("edit", fileTranslateEn));
    editTags = destr(funcBaseGetFromJson("editTags", fileTranslateEn));
    editInfo = destr(funcBaseGetFromJson("editInfo", fileTranslateEn));
    info = destr(funcBaseGetFromJson("info", fileTranslateEn));
    add_path = destr(funcBaseGetFromJson("add_path", fileTranslateEn));
    open_num = destr(funcBaseGetFromJson("open_num", fileTranslateEn));
    open_folder_num = destr(funcBaseGetFromJson("open_folder_num", fileTranslateEn));
    edit_path_num = destr(funcBaseGetFromJson("create_path", fileTranslateEn));
    toolTip = destr(funcBaseGetFromJson("toolTip", fileTranslateEn));
    popOK = destr(funcBaseGetFromJson("popOK", fileTranslateEn));
    popBACK = destr(funcBaseGetFromJson("popBACK", fileTranslateEn));

    nameSearch = button_search;
    nameSearch += ": ";
    nameSearch += table_name;

    tagsSearch = button_search;
    tagsSearch += ": ";
    tagsSearch += table_tags;

    pathSearch = button_search;
    pathSearch += ": ";
    pathSearch += table_path;

    infoSearch = button_search;
    infoSearch += ": ";
    infoSearch += table_info;


    item_current = itm;
}
//
//void translateDB::updateDB(std::string fileTranslateEn, std::vector<char*> translationsList) {
//    fileTranslateEn = translationsList[itm];
//    intro = destr(funcBaseGetFromJson("intro", fileTranslateEn));
//    button_create = destr(funcBaseGetFromJson("button_create", fileTranslateEn));
//    button_search = destr(funcBaseGetFromJson("button_search", fileTranslateEn));
//    search_key = destr(funcBaseGetFromJson("search_key", fileTranslateEn));
//    search_val = destr(funcBaseGetFromJson("search_val", fileTranslateEn));
//    check_catalogue = destr(funcBaseGetFromJson("check_catalogue", fileTranslateEn));
//    table_name = destr(funcBaseGetFromJson("table_name", fileTranslateEn));
//    table_tags = destr(funcBaseGetFromJson("table_tags", fileTranslateEn));
//    table_info = destr(funcBaseGetFromJson("table_info", fileTranslateEn));
//    table_path = destr(funcBaseGetFromJson("table_path", fileTranslateEn));
//    create_name = destr(funcBaseGetFromJson("create_name", fileTranslateEn));
//    create_tags = destr(funcBaseGetFromJson("create_tags", fileTranslateEn));
//    create_info = destr(funcBaseGetFromJson("create_info", fileTranslateEn));
//    create_path = destr(funcBaseGetFromJson("create_path", fileTranslateEn));
//    name_app = destr(funcBaseGetFromJson("name_app", fileTranslateEn));
//    refresh = destr(funcBaseGetFromJson("refresh", fileTranslateEn));
//    edit = destr(funcBaseGetFromJson("edit", fileTranslateEn));
//    editTags = destr(funcBaseGetFromJson("editTags", fileTranslateEn));
//    editInfo = destr(funcBaseGetFromJson("editInfo", fileTranslateEn));
//    info = destr(funcBaseGetFromJson("info", fileTranslateEn));
//    add_path = destr(funcBaseGetFromJson("add_path", fileTranslateEn));
//    open_num = destr(funcBaseGetFromJson("open_num", fileTranslateEn));
//    open_folder_num = destr(funcBaseGetFromJson("open_folder_num", fileTranslateEn));
//    edit_path_num = destr(funcBaseGetFromJson("create_path", fileTranslateEn));
//    toolTip = destr(funcBaseGetFromJson("toolTip", fileTranslateEn));
//    popOK = destr(funcBaseGetFromJson("popOK", fileTranslateEn));
//    popBACK = destr(funcBaseGetFromJson("popBACK", fileTranslateEn));
//
//    nameSearch = button_search;
//    nameSearch += ": ";
//    nameSearch += table_name;
//
//    tagsSearch = button_search;
//    tagsSearch += ": ";
//    tagsSearch += table_tags;
//
//    pathSearch = button_search;
//    pathSearch += ": ";
//    pathSearch += table_path;
//
//    infoSearch = button_search;
//    infoSearch += ": ";
//    infoSearch += table_info;
//
//}
