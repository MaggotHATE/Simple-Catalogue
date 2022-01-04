#pragma once

#include "libUI.h"


class libCardAssembly 
{
public:
	//Absence of default constructor is equal to:
	libCardAssembly() = default;
    libCardAssembly(std::vector<libCard>& assemblyOf_I);

    libUI& getUI();
    std::vector<libCard>& getCards();
    libCard getACard(int idx);
    //my_item::MyItem getAUI(int idx);
    int getCardIdx(int idx);

    libCard getACardByUi(int idx);

    char* getCardElem(cardItem flag, int idx);

    void clearC();
    void clearV();

    bool setACard(libCard aCard, int idx);

    bool setCname(char* name, int idx);

    bool setCtags(char* name, int idx);

    bool setCpath(char* name, int idx);

    bool setCinfo(CharMap info, int idx);


    bool libCardAssembly::setData(int idx, char* name = "--", char* tags = "--", char* path = "--", std::map<char*, char*> inform = {{"NULL","NULL"}});

    private:
        libUI _assemblyView;
        std::vector<libCard> _assemblyOf;
		void setUp(std::vector<libCard>& assemblyOf_I);

};
