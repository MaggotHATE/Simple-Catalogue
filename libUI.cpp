#include "libUI.h"

#include <fstream>
#include <iostream> 
#include <imgui.h>

using namespace my_item;

libUI::libUI(std::vector<libCard>& assemblyOf_I)
{
    setUp(assemblyOf_I);
}

void libUI::setUp(std::vector<libCard>& assemblyOf_I)
{
    clearV();

    _assemblyView.resize(assemblyOf_I.size(), MyItem());

    for (int n = 0; n < _assemblyView.Size; n++)
    {
        const int template_n = n % assemblyOf_I.size();
        MyItem& item = _assemblyView[n];
        item.ID = n;

        item.Name = assemblyOf_I[template_n].getName();
        item.Tags = assemblyOf_I[template_n].getTags();
        item.Path = assemblyOf_I[template_n].getPath();
        item.Info = funcAssembleFromMap(assemblyOf_I[template_n].getInfo());


    }

    std::cout << __FUNCTION__ << ": " << _assemblyView[0].Name << "\n";
}

void libUI::clearV() {
    _assemblyView.clear();
}

MyItem libUI::getAUI(int idx) {
    std::cout << __FUNCTION__ << " size " << sizeof(_assemblyView[idx]) << "\n";
    return _assemblyView[idx];
}

int libUI::Size() {
    std::cout << __FUNCTION__ << ": " << _assemblyView.Size << "\n";
    return _assemblyView.Size;
}

int libUI::ID(int idx) {
    return _assemblyView[idx].ID;
}

char* libUI::Name(int idx) {
    return _assemblyView[idx].Name;
}

char* libUI::Tags(int idx) {
    return _assemblyView[idx].Tags;
}

char* libUI::Path(int idx) {
    return _assemblyView[idx].Path;
}

char* libUI::Info(int idx) {
    return _assemblyView[idx].Info;
}

bool libUI::setAUI(my_item::MyItem aUI, int idx) {
    _assemblyView[idx] = aUI;
}

bool libUI::setName(char* name, int idx) {
    _assemblyView[idx].Name = destr(name);

    return true;
}

bool libUI::setTags(char* tags, int idx) {
    _assemblyView[idx].Tags = destr(tags);

    return true;
}

bool libUI::setPath(char* path, int idx) {
    _assemblyView[idx].Path = destr(path);

    return true;
}

bool libUI::setInfo(CharMap info, int idx) {
    _assemblyView[idx].Info = funcAssembleFromMap(info);

    return true;
}
