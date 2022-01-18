/*
Programming for FE - Final delivery
Drive through food ordering
Omar El Nahhas
23-12-2020
*/

#include "FcnOmar.h"

int main()
{
	int restaurant, ordered_item;
	vector<int>* order = new vector<int>;
	
	printWelcome();
	restaurant = choose_restaurant();
	navigate_options(restaurant);
	order = process_order(ordered_item, order);
	print_receipt(order);

	delete order;
	
	return 0;
}

