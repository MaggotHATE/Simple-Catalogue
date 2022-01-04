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
    _assemblyView.clearV();

    _assemblyOf = assemblyOf_I;
    //_assemblyView = assemblyView_I;
    _assemblyView = (assemblyOf_I);


    std::cout << __FUNCTION__ << ": " << _assemblyView.Name(0) << "\n";
}

libUI& libCardAssembly::getUI() {
    return _assemblyView;
}

int libCardAssembly::getCardIdx(int idx) {
    return _assemblyView.ID(idx);
}

std::vector<libCard>& libCardAssembly::getCards() {
    return _assemblyOf;
}

libCard libCardAssembly::getACard(int idx) {
    return _assemblyOf[idx];
}

libCard libCardAssembly::getACardByUi(int idx) {
    return _assemblyOf[getCardIdx(idx)];
}

bool libCardAssembly::setACard(libCard aCard, int idx) {
    _assemblyOf[idx] = aCard;
}



///////////////////////////////////// SET CARD DATA

bool libCardAssembly::setCname(char* name, int idx) {
    int ID = _assemblyView.getAUI(idx).ID;
    _assemblyOf[ID].setName(name);

    return true;
}

bool libCardAssembly::setCtags(char* tags, int idx) {
    int ID = _assemblyView.getAUI(idx).ID;
    _assemblyOf[ID].setTags(tags);

    return true;
}

bool libCardAssembly::setCpath(char* path, int idx) {
    int ID = _assemblyView.getAUI(idx).ID;
    _assemblyOf[ID].setPath(path);

    return true;
}

bool libCardAssembly::setCinfo(std::map<char*, char*> info, int idx) {
    int ID = _assemblyView.getAUI(idx).ID;
    _assemblyOf[ID].setInfo(info);

    //std::cout << __FUNCTION__ << " BEGIN" << "\n";
    //std::cout << funcAssembleFromMap(_assemblyOf[ID].getInfo()) << "\n";
    //std::cout << __FUNCTION__ << " end" << "\n";
}

//////////////////////////////////// SET UIs 

///////////////////////////////////// UNIFIED SET

bool libCardAssembly::setData(int idx, char* name, char* tags, char* path, std::map<char*, char*> inform) {
    if (name != "--") {
        setCname(name, idx);
        _assemblyView.setName(name, idx);
    }

    if (tags != "--") {
        setCtags(tags, idx);
        _assemblyView.setTags(tags, idx);
    }

    if (path != "--") {
        setCpath(path, idx);
        _assemblyView.setPath(path, idx);
    }

    if (inform.find("NULL") == inform.end() ) {
        setCinfo(inform, idx);
        _assemblyView.setInfo(inform, idx);
    }

    return true;
}

///////////////////////////////////// UNIFIED GET

char* libCardAssembly::getCardElem(cardItem flag, int idx) {
    return getACardByUi(idx).getItem(flag, idx);
}

////////////////////////////// CLEARS

void libCardAssembly::clearC() {
    _assemblyOf.clear();
}
