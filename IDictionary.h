//
// Created by kuzin on 12.12.2021.
//

#ifndef HASH_TABLE_IDICTIONARY_H
#define HASH_TABLE_IDICTIONARY_H

#include <stdlib.h>
#include <string>

template <class Tkey, class TElement>
class IDictionary
{
public:

    virtual TElement* Get (Tkey key) = 0;
    virtual int GetHash(Tkey key) = 0;
    virtual int GetCount () = 0;
    virtual int GetCapacity()=0;
    virtual bool ContainsKey(Tkey key)=0;
    virtual void Remove(Tkey key)=0;
    virtual void Add (Tkey& key, TElement* element) = 0;
    virtual void Resize (size_t) = 0;
    virtual void Print () = 0;
};

#endif //HASH_TABLE_IDICTIONARY_H
