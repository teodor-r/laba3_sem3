//
// Created by kuzin on 12.12.2021.
//

#ifndef HASH_TABLE_ITEM_H
#define HASH_TABLE_ITEM_H
#include "string"
#include <iostream>

class Item
{
public:
    std::string name;
    int weight;
    int value;
    int volume;

    Item(const std::string name, int weight, int value, int volume);
    Item();
    ~Item();
    void Print();
};

#endif //HASH_TABLE_ITEM_H
