#ifndef FCNOMAR_H
#define FCNOMAR_H

#include <vector>
using namespace std;

void printWelcome();
void readFile();
int choose_restaurant();
void navigate_options(int);
void clear_screen();
vector<int>* process_order(int, vector<int>*);
void print_receipt(vector<int>*);

#endif
