#ifndef RESTAURANT_H_
#define RESTAURANT_H_

#include <vector>
#include <string>
#include "Dish.h"
#include "Table.h"
#include "Action.h"


class Restaurant{		
public:
	Restaurant();

    explicit Restaurant(const std::string &configFilePath);
    void start();
    int getNumOfTables() const;
    Table* getTable(int ind);
    std::vector<Table*> gettables();
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Dish>& getMenu();

	//copy constructor
	Restaurant(const Restaurant &other);


	//destructor
	~Restaurant();

	//move constractor
	Restaurant(Restaurant&& other);

	//move assignment
	Restaurant &operator=(Restaurant&& other);

	//copy assignment
	Restaurant &operator=(const Restaurant &other);


    //casting string into DishType
    DishType stringtodishtype(std::string s);

    void closerest();

    std::vector<std::string> split(std::string str, char c);

private:
    bool open;
    std::vector<Table*> tables;
    std::vector<Dish> menu;
    std::vector<BaseAction*> actionsLog;
    int numoftables;
    int cid; //customer id
    int did; //dish id
};

#endif