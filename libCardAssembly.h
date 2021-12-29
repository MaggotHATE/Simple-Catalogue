#pragma once

#include "libCard.h"

class libCardAssembly {
public:
    //libCardAssembly(std::vector<libCard> assemblyOf_I);
    void setUp(std::vector<libCard> assemblyOf_I);
    ImVector<MyItem> getView();
    std::vector<libCard> getCards();
    libCard getACard(int idx);
    MyItem getAView(int idx);
    void clearC();
    void clearV();
    std::vector<libCard> _assemblyOf;
    ImVector<MyItem> _assemblyView;

    //private:
    //    std::vector<libCard> _assemblyOf;
    //    ImVector<MyItem> _assemblyView;

};
