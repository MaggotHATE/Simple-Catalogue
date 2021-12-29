#pragma once

#include "libCard.h"

class libCardAssembly 
{
public:
	//Absence of default constructor is equal to:
	libCardAssembly() = default;
    libCardAssembly(std::vector<libCard>& assemblyOf_I);
	

    ImVector<my_item::MyItem>& getView();
    std::vector<libCard> getCards();
    libCard getACard(int idx);
    my_item::MyItem getAView(int idx);
    void clearC();
    void clearV();
    //*
	std::vector<libCard> _assemblyOf;
    ImVector<my_item::MyItem> _assemblyView;
	//*/
    private:
		void setUp(std::vector<libCard>& assemblyOf_I);
        /*
		std::vector<libCard> _assemblyOf;
        ImVector<my_item::MyItem> _assemblyView;
		//*/
};
