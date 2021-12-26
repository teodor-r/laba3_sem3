//
// Created by kuzin on 17.12.2021
//

#include "Tree.h"

template <class TElement>
Node<TElement>::Node(list<std::string> all_elements)
{
    isTerminal = false;
    not_parents = all_elements;
    parent = nullptr;
    curr_value = 0;
    curr_weight = 0;
    curr_volume = 0;
    destiny_of_val = 0;
    index = 0;

}
template <class TElement>
Node<TElement>::Node(string& key, TElement* el,list<std::string> not_par,int curr_value, int curr_weight,int curr_volume, Node<TElement> *p,int index)
{
    parent = p;
    element.first = key;
    element.second = el;
    not_parents = not_par;
    this->curr_value = curr_value;
    this->curr_weight = curr_weight;
    this->curr_volume = curr_volume;
    destiny_of_val = this->curr_value / this->curr_weight;
    this->index = index;
}

template <class TElement>
Node<TElement>::~Node()
{

}

template<class TElement>
Tree<TElement>::Tree()
{
    root = nullptr;
    mxv_terminal = nullptr;
    mxvdestiny_terminal = nullptr;
    total_nodes = 0;
}

template<class TElement>
Tree<TElement>::Tree(list<std::string> all_elements, Dictionary<TElement> &dict)
{
    root = new Node<TElement>(all_elements);
    mxv_terminal = root;
    mxvdestiny_terminal = root;
    this->dict = dict;
    total_nodes = 0;
    int count  =  dict.GetCount();
    int size = count * 100;
    GR = new float * [size];
    for (int i=0; i<size; i++) GR[i] = new float [size];
    for (int i=0; i<size; i++) {
        for (int j = 0; j < size; j++){
            GR[i][j] = 0;
        }

    }


}
template<class TElement>
Tree<TElement>::~Tree(){

}

template<typename TElement>
bool Tree<TElement>::SingleKTaskW(TElement *t, int bckpck_weight, int bckpck_volume, int cur_weight, int cur_volume)
{
    return 0;
}
template<typename TElement>
bool Tree<TElement>::SingleKTaskV(TElement *t, int bckpck_weight, int bckpck_volume, int cur_weight, int cur_volume)
{
    return 0;
}
template<typename TElement>
bool Tree<TElement>::MultiKTask(TElement *t, int bckpck_weight, int bckpck_volume, int cur_weight, int cur_volume)
{
    return 0;
}
template<class TElement>
void Tree<TElement>::GenerateTree(bool (*metrika)(TElement*,int,int,int,int))
{

}
template<class TElement>
void Tree<TElement>::PrintAnswer(bool (*metrika)(TElement*,int,int,int,int)){

}

template<class TElement>
Node<TElement>* Tree<TElement>::GetByIndex(int id, Node<TElement>* node) {

}
template<class TElement>
void Tree<TElement>::DeleteTree()
{
    DeleteNode(root);
    mxv_terminal = root;
    mxvdestiny_terminal = root;
}

template<class TElement>
void Tree<TElement>::NextNode(Node<TElement> *node, bool (*metrika)(TElement*,int bckpck_weight, int bckpck_volume,int cur_weight, int cur_volume))
{

}
template<class TElement>
void Tree<TElement>::DeleteNode(Node<TElement> *node)
{
    if (node->childs.size() > 0)
    {
        for (auto it = node->childs.begin(); it != node->childs.end(); it++) {
            //node->childs.remove(*it);
            DeleteNode(*it);
        }
        node->childs.clear();
    }
    else {
        if(node!= root)
            delete node;
    }
}


template<>
bool Tree<Item>::SingleKTaskW(Item *t, int bckpck_weight, int bckpck_volume,int cur_weight, int cur_volume)
{
    if(bckpck_weight >=cur_weight + t->weight)
        return true;
    else
        return false;
}

template<>
bool Tree<Item>::SingleKTaskV(Item *t, int bckpck_weight, int bckpck_volume,int cur_weight, int cur_volume)
{
    if(bckpck_volume >=cur_volume + t->volume)
        return true;
    else
        return false;
}

template<>
bool Tree<Item>::MultiKTask(Item *t, int bckpck_weight, int bckpck_volume, int cur_weight, int cur_volume)
{
    if(bckpck_volume >=cur_volume + t->volume && bckpck_weight >=cur_weight + t->weight)
        return true;
    else
        return false;
}



template<>
void Tree<Item>::NextNode(Node<Item> *node, bool (*metrika)(Item*,int bckpck_weight, int bckpck_volume,int cur_weight, int cur_volume))
{   int counter = 0;
    for ( auto it = node->not_parents.begin(); it != node->not_parents.end(); ++it)
    {   Item* t = dict.Get(*it);
        if(t!= nullptr && node->element.first != t->name && metrika(t,bckpck_weight, bckpck_volume, node->curr_weight ,  node->curr_value))
        {   counter++;
            list<string> not_parents_next_node(node->not_parents);
            not_parents_next_node.remove(node->element.first);
            int ncv = node->curr_value + t->value;
            int ncw = node->curr_weight + t->weight;
            int ncvol = node->curr_volume + t->volume;
            total_nodes++;
            Node<Item> *next_node = new Node<Item>(*it, t, not_parents_next_node, ncv, ncw, ncvol, node, total_nodes);
            GR[node->index][total_nodes] = float(t->value) / float(t->weight);
            node->childs.push_back(next_node);
            NextNode(next_node,metrika);
        }
    }
    if(counter==0 || node->not_parents.size() ==0)
    {
        node->isTerminal = true;
        //cout << "Terminal list: "  <<node->curr_value << endl;
        if(node->curr_value >= mxv_terminal->curr_value)
        {
            mxv_terminal = node;
        }
        if(node->destiny_of_val  >= mxvdestiny_terminal->destiny_of_val)
        {
            mxvdestiny_terminal = node;
        }

    }
}



template<>
void Tree<Item>::GenerateTree(bool (*metrika)(Item*,int,int,int,int))
{
    NextNode(root, metrika);
    for (int i = 0; i<total_nodes; i++)
    {
        for (int j = 0; j<total_nodes; j++)
            printf("%.2f ", GR[i][j]);
        printf("\n");
    }
}

template<>
void  Tree<Item>::PrintAnswer(bool (*metrika)(Item*,int,int,int,int)){
    if( metrika!= nullptr)
    {
        Node<Item> *current = mxv_terminal;
        cout << "Max total value: "<<  current->curr_value <<endl;
        cout << "Items:" <<endl;
        while(current->parent!= nullptr)
        {
            current->element.second->Print();
            current = current->parent;
        }
    }
    else
    {
        Node<Item> *current = mxvdestiny_terminal;
        cout << "Total value: "<<  current->curr_value <<endl;
        cout << "Total weight: "<<  current->curr_weight <<endl;
        cout << "Items:" <<endl;
        while(current->parent!= nullptr)
        {
            current->element.second->Print();
            current = current->parent;
        }
    }
}

template<>
Node<Item>* Tree<Item>::GetByIndex(int id, Node<Item>* node) {
    if (node->index != id) {
        for ( auto it = node->childs.begin(); it != node->childs.end();++it)
        {
            if ((**it).index==id)
            {
                (*it)->element.second->Print();
                return *it;
            }
        }
        for ( auto it = node->childs.begin(); it != node->childs.end();++it)
        {
            Node<Item> *nod = GetByIndex(id, *it);
            if (nod != nullptr)
                return nod;
        }

    } else {
        return node;
    }
    return nullptr;
}

template<>
int *Tree<Item>::GetAdjacencyMatrix()
{


    return nullptr;
}
