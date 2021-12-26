//
// Created by kuzin on 20.12.2021.
//

#ifndef HASH_TABLE_MENU_H
#define HASH_TABLE_MENU_H
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <fstream>

int variable_choice();

int VAR = variable_choice();

const char *MSGS[] = {"0. Exit", "1. Pass data", "2. Change variable type"};

const size_t MSGS_SIZE = (sizeof(MSGS) / sizeof(MSGS[0]));

int stoi (const char *);

int choice_();

int dialog ();

#endif //HASH_TABLE_MENU_H
