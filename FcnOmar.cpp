#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <algorithm>
#include <ctime>
#include <iomanip>
using namespace std;

//prototypes for functions in this file
void readFile(string);
void clear_screen();
int exit_program();
void show_menu(int, string);
vector<int>* process_order(int, vector<int>*);
string time_now(string text = ""); //default parameter for text = ""

//initialize menu globally, so every function can access it without
//it being passed through function arguments
const int menu_size = 5;
const string name[] = {"burger", "nuggets", "wrap", "fries", "wings"}; 
const double price[] = {4.50, 7.20, 3.50, 3.20, 2.80};
const int cal[] = {550, 510, 310, 320, 590};
string rest_name;


void printWelcome(){
	string filename = "textfiles/1welcome.txt";
	readFile(filename);
	
	return;
}


void readFile(string filename){
	//function to read all the contents of a given file
	
	ifstream textfile(filename);
	string line;
	cout << endl;
	if(textfile.is_open())
	{
		while(getline(textfile, line))
		{
			cout << line << endl;
		}
		textfile.close();
	}
	else{ cout << "Cannot open file: " << filename << endl;}
	cout << endl;
	
	return;
}


int choose_restaurant(){
	int choice;
	string filename = "textfiles/2restaurants.txt";
	readFile(filename);
	
	//this while loop prevents the input of anything which isn't an integer
	while(cout << "Pick the number of the restaurant where you want to order: " && !(cin >> choice)){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input type, please try again!\n\n";
	}
	
	return choice;	
}


void navigate_options(int restaurant)
{
	//switch case to determine at which restaurant
	//an order will be placed
	switch(restaurant){
		case -1:
			if(!(exit_program())){ //if you don't want to exit the program
				//restart the restaurant option navigation
				restaurant = choose_restaurant();
				navigate_options(restaurant);
			}
			break;
		case 1:
			//welcome to mcdonalds + menu
			rest_name = "McDonalds";
			show_menu(restaurant, rest_name); //show the menu of this restaurant
			break;
		case 2:
			//welcome to kfc + menu
			rest_name = "KFC";
			show_menu(restaurant, rest_name);
			break;
		case 3:
			//welcome to burger king + menu
			rest_name = "Burger King";
			show_menu(restaurant, rest_name);
			break;
		case 4:
			//welcome to popeyes + menu
			rest_name = "Popeyes";
			show_menu(restaurant, rest_name);		
			break;
		default:
			//executes if none of the options above was chosen
			clear_screen();
			cout << "This option is not (yet) available.\n\n";
			cout << "Please choose a different restaurant below:\n";
			
			//restart the restaurant option navigation
			restaurant = choose_restaurant();
			navigate_options(restaurant);
	}
	
	return;
}


void show_menu(int restaurant, string rest_name){
	clear_screen();
	
	//prints the menu options to the command prompt
	cout << "Welcome to " << rest_name << '!' << endl << endl;
	
	//column names formatting of menu
	cout << "#\tItem\t\tPrice\t\tCalories\n"; 
	for(int i = 0; i < menu_size; i++)
	{
		//prints the menu row by row based on the global menu variables
		cout << '\n' << i+1 << '\t';
		cout << name[i] << "\t\t" << price[i] << "\t\t" << cal[i];
		
	}
	cout << "\n\n";
	
	return;
}


vector<int>* process_order(int ordered_item, vector<int>* order){
	/*
	A pointer to an int vector is chosen to add exit flexibility in the program.
	Without the pointer, when the user 'accidently' goes to the exit order/program
	prompt, but doesn't fully exit the program, the previous order would be overwritten
	and therefore lost. When passing the address of the location of the vector,
	the program can continue with the previously added items in the order.
	A vector is basically a dynamic array which can change size during runtime,
	and is chosen based on its flexibility and native c++ features.
	*/
	cout << "(-3 to restart order, -2 to finish order, -1 to exit program)\n";
	ordered_item = 0;
	string confirm;
	
	do{
		//input protection for ordered_item int type;
		while(cout << "What would you like to order, please enter the Item #: " && !(cin >> ordered_item)){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input type, please try again!\n\n";
		}
		
		//defined actions for picking a menu item, or choosing an exit option
		if(ordered_item <= 5 && ordered_item >= -3 && ordered_item != 0){ // menu items
			if(ordered_item == -2){
				
				//input protection for confirm string type				
				while(cout << "\nAre you done with ordering (y/n)?: " && !(cin >> confirm)){
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input type, please try again!\n\n";
				}

				cout << endl;
				if(confirm == "y" || confirm == "Y"){
					ordered_item = -2;
				}
				else if(confirm == "n" || confirm == "N"){
					ordered_item = 0;
				}
				else{
					cout << "Invalid option. Try command -2 again.\n";
					ordered_item = 0;
				}
				//clear screen
				//print receipt
			}
			else if(ordered_item == -1){
				if(!(exit_program())){
					//return where the order left off
					process_order(0, order);
					break;
				}
			}
			else if(ordered_item == -3){
				order->clear(); //clear every item stored in the order vector
				
				//check if the value clearing was succesful
				if(order->size() == 0){
					cout << "\nOrder is succesfully restarted!\n\n";
				}
				else{
					cout << "\nAn error occured while restarting the order!\
					 Please try again or exit the program.\n";
				}
			}
			
			else{
				order->push_back(ordered_item); //add item to order vector
				cout << "Great choice, it's added to your order!\r";
			}
			this_thread::sleep_for(chrono::milliseconds(1000)); //wait 1 second
			//sleep or delay functions were OS specific, this works cross platform
		}
		else{
			cout << "\nSorry, this item is not on the menu!\r";
			this_thread::sleep_for(chrono::milliseconds(2500)); //wait 2.5 seconds
			//sleep or delay functions were OS specific, this works cross platform
		}

	} while(ordered_item != -2);
	
	return order;
}


void print_receipt(vector<int>* order){
	clear_screen();
	
	//initialise the occurance of items to 0 to avoid
	//random values in the memory which will be evaluated
	int item_occurance[menu_size] = {0, 0, 0, 0, 0};
	
	//sort the vector from smallest to largest
	sort(order->begin(), order->end());
	
	auto i = order->begin();
    while (i != order->end())
    {
    	//get the distance between first occurance and last occurance of the
    	//menu item, aka: how many times has this product been ordered?
        auto ub = upper_bound(order->begin(), order->end(), *i);
        item_occurance[*i-1] = distance(i, ub);
        i = ub;
    }
	
	//initialise an unique filename for the receipt
    string filename = "order_receipts/receipt_" + rest_name + "_" + time_now() + ".txt";
	ofstream textfile(filename);
	double total_price = 0;
	
	if(textfile.is_open())
	{
		//formatting and printing of the receipt
		textfile << rest_name + " order on " << time_now("format") << endl << endl;
		textfile << "Qty\tItem\t\tPrice\t\tCalories\n";
		for(int x = 0; x < menu_size; x++)
		{
			if(item_occurance[x] != 0){ //if an item has been ordered more than 0 times:
				//print it on the receipt
				textfile << fixed << item_occurance[x] << "x\t" << name[x] << "\t\t" <<\
				setprecision(2)<< item_occurance[x]*price[x] << " euro\t" << item_occurance[x]*cal[x] << endl;
				
				//calculate the total price of the order thus far
				total_price += item_occurance[x]*price[x];
			}
		}
		textfile << fixed << setprecision(2) << "\nTotal price: " << total_price << " euro";
		textfile << "\n\nHave a nice day!";
		cout << "Receipt stored in: ~/" << filename << endl;
		cout << "\n\nHave a nice day!";
	}
	else{
		cout << "Can't write to " + filename;
	}
	
	textfile.close();
		
	return;
}


string time_now(string text){
	//retrieve the local time
	time_t now = time(0);
	tm *ltm = localtime(&now);
	string time_now;
	
	
	//formatting for digital clock
	//(for example) 7 am raw output is 7:0 and is changed to 07:00:
	string add_sec = "";
	string add_min = "";
	string add_hour = ""; 
	
	if(ltm->tm_sec < 10)
	{
		add_sec = "0";
	}
	if(ltm->tm_min < 10)
	{
		add_min = "0";
	}
	if(ltm->tm_hour < 10)
	{
		add_min = "0";
	}
	
	//information about tm struct: https://www.cplusplus.com/reference/ctime/tm/
	
	//output in pretty format, for on the receipt etc.
	if(text == "format"){
		time_now = to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon)\
		+ "-" + to_string(ltm->tm_mday) + " " + add_hour + to_string(ltm->tm_hour) +\
		':' + add_min + to_string(ltm->tm_min);
	}
	
	//output in filename suitable format
	else{
		time_now = to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon)\
		+ "-" + to_string(ltm->tm_mday) + "_" + add_hour + to_string(ltm->tm_hour) +\
		add_min + to_string(ltm->tm_min) + add_sec + to_string(ltm->tm_sec);
	}
	
	return time_now;
}


void clear_screen(){
	//clear screen of cmd prompt
	system("CLS"); 
	
	return;
}


int exit_program(){
	int end = 1;
	string answer;
	do{
	//input protection for answer string type	
	while(cout << "\nAre you sure you want to exit (y/n)?: " && !(cin >> answer)){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input type, please try again!\n\n";
		}

		if(answer == "y" || answer == "Y"){
			clear_screen();
			cout << "See you, have a nice day!";
			//exit program
			exit(EXIT_SUCCESS);
		}
		else if(answer == "n" || answer == "N")
		{
			clear_screen();
			//stay in program
			end = 0;
		}
		else{
			cout << "Invalid input. Try again!\n";
			end = 2;
		}
	} while(end == 2);
	
	return end;
}

