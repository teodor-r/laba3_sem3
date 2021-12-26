//
// Created by kuzin on 20.12.2021.
//

#include "Menu.h"
#include "Item.h"
#include <time.h>
#include "Dictionary.h"
#include "Tree.h"
#include "Dijkstra.h"
#include <fstream>

int stoi (const char *str)
{
    int ans = 0, i = 0;
    int sign = (str[0] == '-') ? -1: (((str[0] >= '0') && (str[0] <= '9')) ? 1: 0);
    if (sign == 0)
        return -1;
    while (str[i] != '\0')
    {
        if ((str[i] <= '9') && (str[i] >= '0'))
            ans = 10 * ans + str[i] - '0';
        else
            return -1;
        i++;
    }
    return sign * ans;
}

int *generate_seq (size_t size)
{
    int *data = (int *) calloc (size, sizeof(int));
    for (size_t i = 0; i < size; i++)
    {
        int t = rand() % 100000 - 20000;
        *(data + i) = t;
    }
    return data;
}


int variable_choice()
{
    while (1)
    {
        std::cout << "What type of data do u use?" << std::endl << "1. Integer" << std::endl;
        char *c = new char (100);
        std::cin >> c;
        int ans = stoi (c);
        delete c;
        if ((ans > 0) && (ans < 5))
            return ans;
        else
            std::cout << "Wrong number, plaese, try again!" << std::endl;
    }
}

int choice_()
{
    while (true) {
        char *ch = new char (100);
        std::cout << "What do you wanna do?" << std::endl;
        for (auto & i : MSGS)
            std::cout << i << std::endl;
        std::cin >> ch;
        int choice = stoi(ch);
        delete ch;
        if ((choice >= 0) && (choice < MSGS_SIZE))
            return choice;
        else
            std::cout << "You entered a wrong number, plaese, try again!" << std::endl;
    }
}



int dialog()
{
    int choice = choice_();
    while (true)
        switch (choice)
        {
            case(0):
            {
                std::cout << "Good Bye!" << std::endl;
                return 0;
            }
            case(1):// вводим данные
            {
                int num_elem;
                std::cout << "Pass number of items"  << std::endl;
                std::cin >> num_elem;
                std::cout << "Pass data in a next way: name,  weight, value, volume "  << std::endl;
                Dictionary<Item> d(num_elem+1);
                for ( int i =0 ; i< num_elem ;i++)
                {
                    std::string name;
                    int weight, value, volume;
                    std::cin >> name >> weight >> value >> volume;
                    Item *t = new Item(name,weight,value,volume);
                    d.Add(t->name, t);
                }
                d.Print();
                Tree<Item> tree(d.GetListKeys(),d);
                std::cout << "Pass backpack weight and volume "  << std::endl;
                std::cin >> tree.bckpck_weight >>  tree.bckpck_volume;

                bool (*ptrSingleKTaskW)(Item *t, int bckpck_weight, int bckpck_volume,int cur_weight, int cur_volume);

                ptrSingleKTaskW = Tree<Item>::SingleKTaskW;

                tree.GenerateTree(ptrSingleKTaskW);
                tree.PrintAnswer(ptrSingleKTaskW);
                Dijkstra(tree.GR, tree.total_nodes, 0);
                float *distance=Dijkstra(tree.GR, tree.total_nodes, 0);

                int m=1;
                cout << "Cost ways:\n";
                for (int i=0; i<tree.total_nodes; i++)
                    if (distance[i]!=INT_MAX)
                        cout << m << " > " << i+1 << " = " << distance[i] << endl;
                    else cout << m << " > " << i+1 << " = " << "Way is denied" << endl;


                int max_index = 0;
                int max =0;
                for (int i=0; i<tree.total_nodes; i++)
                {
                    if(distance[i] >=max){
                        max_index = i;
                        max = distance[i];
                    }
                }

                cout << "The Single-Criteria task is computed  using Dijkstra alghoritm " << endl;
                Node<Item> *current = tree.GetByIndex(max_index, tree.root);
                cout << "Max total value: "<<  current->curr_value <<endl;
                cout << "Items:" <<endl;
                while(current->parent!= nullptr)
                {
                    current->element.second->Print();
                    current = current->parent;
                }
                cout << "////////////////////////////////////////"  <<   endl;
                cout << "The Single-Criteria task using usual method "  <<   endl;
                tree.PrintAnswer(ptrSingleKTaskW);
                choice = choice_();

                break;
            }
            case (2):
            {
                VAR = variable_choice();
                return 1;
            }
        }
}