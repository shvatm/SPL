#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <vector>
#include <string>
#include "Dish.h"

class Customer{
public:
    Customer(std::string c_name, int c_id);
    virtual std::vector<int> order(const std::vector<Dish> &menu)=0;
    virtual std::string toString() const = 0;
    std::string getName() const;
    int getId() const;




    //copy function
	virtual Customer* copy() const =0;

	//destructor
	~Customer();

	//move constructor
	//Customer(Customer&& other);

private:
    const std::string name;
    const int id;
};


class VegetarianCustomer : public Customer {
public:
	VegetarianCustomer(std::string name, int id);
	Customer* copy() const ;// copy function- coppying this
	std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
    int vegsmallestid(const std::vector<Dish> &menu);//returns the id of the vegetarian smallest id
    int mostexpensiveb(const std::vector<Dish> &menu);//returns the most expensive beverage

private:
};


class CheapCustomer : public Customer {
public:
	CheapCustomer(std::string name, int id);
	Customer* copy() const; //copy function
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
    int mostcheap(const std::vector<Dish> &menu);//returns the id of the cheapest dish
private:
    int numberoforders;
};


class SpicyCustomer : public Customer {
public:
	SpicyCustomer(std::string name, int id);
	Customer* copy() const ;// copy function
    std::vector<int> order(const std::vector<Dish> &menu);
    std::vector<Dish> nonalcoholic(const std::vector<Dish> &menu);//returns all the non alcoholic beverages
    std::vector<Dish>allspicy(const std::vector<Dish> &menu);//returns all the spicy dishes
    int mostexp(const std::vector<Dish> &menu);
    int cheapest(const std::vector<Dish> &menu);
    std::string toString() const;
private:
    int numoforders;
};


class AlchoholicCustomer : public Customer {
public:
	AlchoholicCustomer(std::string name, int id);
	Customer* copy() const ;
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
    std::vector<Dish> getalc(const std::vector<Dish> &menu);//returns all the alc drinks
    int mostexpensive(std::vector<int> alcmenu);//returns the most cheap dish
    void alcbyorder(std::vector<int> alcmenu);//return the menu by order from cheapest to most expensive
    int getorderid(std::vector<Dish>&menu,int price);//recieve a price and menu and return the id of the dish
private:
    std::vector<int>alcprice;
};


#endif

