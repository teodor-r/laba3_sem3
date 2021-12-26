//
// Created by kuzin on 16.12.2021.
//

#include "Dictionary.h"
#include "memory"
template <class  TElement>
Dictionary<TElement>::Dictionary()
{
    count=0;
    capacity=defaultCapacity;
    //////////////////////////////////////////////////////////////////////////
    table.resize(defaultCapacity);
}
template <class  TElement>
Dictionary<TElement>::Dictionary(unsigned divisor){
    count=0;
    capacity=divisor;
    //////////////////////////////////////////////////////////////////////////
    table.resize(capacity);

}
template<class TElement>
Dictionary<TElement>::~Dictionary<TElement>()
{
    table.clear();
}



template <class  TElement>
int Dictionary<TElement>::GetHash(std::string key)
{
    std::hash<std::string> hash_string;
    int hash_value = hash_string(key) % capacity ;
    //std::cout << "\nthe hashed value is: " << hash_value << std::endl;
    return hash_value;
}

template <class  TElement>
void Dictionary<TElement>::PushBack(std::string key, TElement* element, int hash)
{
    std::pair<std::string, TElement*> newpair;
    newpair.first = key;
    newpair.second = element;
    table[hash].push_back(newpair);
}

template <class  TElement>
TElement* Dictionary<TElement>::Get(std::string key)
{

    int  hash = GetHash(key);
    if(!table[hash].empty())
    {
        for (auto it = table[hash].begin(); it != table[hash].end(); ++it)
        {
            if (it->first == key)
            {
                return it->second;
            }
        }
    }

    return nullptr;
}

template <class  TElement>
void Dictionary<TElement>::Add(std::string& key, TElement *element)
{
    int  hash = GetHash(key);
    int  alpha = 0;// коэффицент заполнения конкретного листа
    if(!table[hash].empty())
    {
       for (auto it = table[hash].begin(); it != table[hash].end(); ++it)
            {   alpha++;
                if ((it)->first == key)
                {
                    TElement *collison = (TElement*)malloc(sizeof((it)->second));
                    memcpy(&collison,&((it)->second),sizeof(&((it)->second)));
                    (it)->second = element;
                    delete collison;
                    return;
                }
            }
       PushBack(key, element, hash);
       keys.push_back(key);
    }
    else {
        PushBack(key, element, hash);
        keys.push_back(key);
    }
    count++;

    if((alpha>=count/2 +1)|| count == capacity)
    {   std::cout << "Resize";
        Resize(capacity*p);
    }

}

template <class  TElement>
void Dictionary<TElement>::Remove(std::string key)
{

  TElement *removed = Get(key);
    if (removed!= nullptr )
    {
        int hash = GetHash(key);
        std::pair<std::string, TElement*> pair(key,removed );
        table[hash].remove(pair);
        keys.remove(key);
        count--;
        if(count< capacity/p)
        {
            Resize(capacity/p + 1);
        }
    }

}

template <class  TElement>
bool Dictionary<TElement>::ContainsKey(std::string key)
{
    TElement* res = Get(key);
    if (res!= nullptr)
        return true;
    return false;
}


template <class  TElement>
int Dictionary<TElement>::GetCapacity()
{
    return capacity;
}

template <class  TElement>
int Dictionary<TElement>::GetCount()
{
    return count;
}

template <class  TElement>
void Dictionary<TElement>::Print()
{

}
template <class  TElement>
void Dictionary<TElement>::Resize(size_t t)
{

    std::vector< std::list< std::pair<std::string,  TElement* > > >copy;
    unsigned old_capacity = capacity;
    CopyTable(copy);

    table.clear();
    keys.clear();
    capacity = t;
    table.resize(t);


    for(int i =0;i< old_capacity;i++)
    {
        for (auto it = copy[i].begin(); it != copy[i].end(); ++it)
        {
            int hash = GetHash(it->first);
            TElement *cop = (TElement*)malloc(sizeof((it)->second));
            memcpy(&cop,&((it)->second),sizeof(&((it)->second)));
            std::pair<std::string, TElement*> newpair;
            newpair.first = it->first;
            newpair.second = cop;
            table[hash].push_back(newpair);
            keys.push_back(it->first);
        }
    }
    copy.clear();
}

template<class TElement>
void Dictionary<TElement>::CopyTable(std::vector<std::list<std::pair<std::string, TElement *>>> &copy) {
    copy.clear();
    copy.resize(capacity);
    for(int i =0;i< capacity;i++)
    {
        for (auto it = table[i].begin(); it != table[i].end(); ++it)
        {
            TElement *cop = (TElement*)malloc(sizeof((it)->second));
            memcpy(&cop,&((it)->second),sizeof(&((it)->second)));

            std::pair<std::string, TElement*> newpair;
            newpair.first = it->first;
            newpair.second = cop;
            copy[i].push_back(newpair);
        }
    }
}

template <>
void Dictionary<Item>::Print()
{
    for (int i =0;i<capacity;i++)
    {
        if(!table[i].empty())
        {   std::list<std::pair<std::string, Item*>>::iterator it;
            for (it = table[i].begin(); it != table[i].end(); ++it)
            {
                it->second->Print();
            }
        }
    }
    for (auto it = keys.begin(); it!= keys.end();it++)
    {
        std::cout <<  *it << " "  << std::endl;
    }
}
template<class TElement>
std::list< std::string> &Dictionary<TElement>::GetListKeys()
{
    return keys;
}





