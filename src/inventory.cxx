#include "inventory.hpp"

using namespace fur;
void Inventory::openinventorywindow(){
    if (Inventory::offscreenConsole==NULL){
       offscreenConsole = new TCODConsole(25,50);
    }

}
void Inventory::closeinventorywindow(){

}
