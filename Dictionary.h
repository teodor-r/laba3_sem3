//
// Created by kuzin on 12.12.2021.
//

#ifndef HASH_TABLE_DICTIONARY_H
#define HASH_TABLE_DICTIONARY_H

#include <list>
#include "Item.h"
#include "IDictionary.h"
#include <string>
#include<bits/stdc++.h>

template <class  TElement>
class Dictionary: public IDictionary< std::string, TElement>
{
private:
    unsigned static const defaultCapacity=17;
    unsigned capacity;
    int count;
    unsigned static const p = 2; //
    unsigned static const q = 2; // коэффицент сжатия

public:
    std::vector< std::list< std::pair<std::string, TElement* > > > table;
    std::list< std::string> keys;
    Dictionary();
    Dictionary(unsigned divisor);
    ~Dictionary();
    int GetHash(std::string key);
    TElement* Get (std::string key) ;
    int GetCount ();
    int GetCapacity();
    bool ContainsKey(std::string key);
    void Remove(std::string key);
    void Add (std::string& key, TElement* element);
    void Resize (size_t);
    void Print ();
    const TElement& operator[](int key);
    void PushBack(std::string key, TElement* element,int hash);
    void CopyTable(std::vector< std::list< std::pair<std::string, TElement* > > > &copy);
    std::list< std::string> &GetListKeys();
};


#endif //HASH_TABLE_DICTIONARY_H
