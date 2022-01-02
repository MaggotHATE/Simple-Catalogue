#pragma once
#include "libCard.h"

class libUI{
public:
    libUI() = default;
    libUI(std::vector<libCard>&assemblyOf_I);

    my_item::MyItem getAUI(int idx);

    int Size();



    bool setAUI(my_item::MyItem aUI, int idx);

    bool setName(char* name, int idx);

    bool setTags(char* name, int idx);

    bool setPath(char* name, int idx);

    bool setInfo(CharMap info, int idx);

    int ID(int idx);

    char* Name(int idx);

    char* Tags(int idx);

    char* Path(int idx);

    char* Info(int idx);

    void clearV();
private:
    ImVector<my_item::MyItem> _assemblyView;
    void setUp(std::vector<libCard>& assemblyOf_I);
};
