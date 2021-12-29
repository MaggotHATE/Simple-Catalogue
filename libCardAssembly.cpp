#include "libCardAssembly.h"
#include <fstream>
#include <iostream> 
#include <imgui.h>

using namespace my_item;
// Hey, mom, look, constructor!
libCardAssembly::libCardAssembly(std::vector<libCard>& assemblyOf_I)
{
	setUp(assemblyOf_I);
}

void libCardAssembly::setUp(std::vector<libCard>& assemblyOf_I)
{

    clearC();
    clearV();

    _assemblyOf = assemblyOf_I;
    //_assemblyView = assemblyView_I;

    _assemblyView.resize(_assemblyOf.size(), MyItem());

    for (int n = 0; n < _assemblyView.Size; n++)
    {
        const int template_n = n % _assemblyOf.size();
        MyItem& item = _assemblyView[n];
        item.ID = n;

        item.Name = _assemblyOf[template_n].getName();
        item.Tags = _assemblyOf[template_n].getTags();
        item.Path = _assemblyOf[template_n].getPath();
        item.Info = funcAssembleFromMap(_assemblyOf[template_n].getInfo());


    }

    std::cout << __FUNCTION__ << ": " << _assemblyView[0].Name << "\n";
}

ImVector<MyItem>& libCardAssembly::getView() {
    return _assemblyView;
}

std::vector<libCard> libCardAssembly::getCards() {
    return _assemblyOf;
}

libCard libCardAssembly::getACard(int idx) {
    return _assemblyOf[idx];
}

MyItem libCardAssembly::getAView(int idx) {
    return _assemblyView[0];
}

void libCardAssembly::clearC() {
    _assemblyOf.clear();
}

void libCardAssembly::clearV() {
    _assemblyView.clear();
}
