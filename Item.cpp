//
// Created by kuzin on 12.12.2021.
//

#include "Item.h"


Item::Item(const std::string name, int weight, int value, int volume){
    Item::name = name;
    Item::weight = weight;
    Item::value = value;
    Item::volume = volume;
}

Item::Item(){

}
void Item::Print()
{   std::cout<< name << " ";
    std::printf("weight: %d , volume: %d, value: %d\n", weight,volume, value);
}
Item::~Item(){

}