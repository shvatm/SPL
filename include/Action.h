#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <iostream>
#include "Customer.h"
#include "Table.h"

enum ActionStatus{
    PENDING, COMPLETED, ERROR
};

//Forward declaration
class Restaurant;

class BaseAction{
public:
    BaseAction();
    ActionStatus getStatus() const;

    virtual void act(Restaurant& restaurant)=0;
    virtual std::string toString() const=0;
    std::string statustostring(ActionStatus s);
 //lynn's functions
    void setParams(std::string params) { this->params = params; };
    std::string getStatusString() const;
    std::string getParams() { return params; };
//end of lynn's functions
	//copy constructor
//BaseAction(const BaseAction &other);

//copy constructor
   // BaseAction* copyme(const BaseAction &other);

    //copy function
    virtual BaseAction* copy() const =0;

	//destructor
	~BaseAction();

	//move constructor
	//BaseAction(BaseAction&& other);

	//move assignment

//	BaseAction &&operator= (BaseAction &&other);


	//copy assignment
	//BaseAction &operator=(const BaseAction& other);

    std::string geterrorMsg();


protected:
    void complete();
    void error(std::string errorMsg);
    std::string getErrorMsg() const;
    std::string params;

    void copyStatusToMe(const BaseAction& other);
private:
    std::string errorMsg;
    ActionStatus status;
};


class OpenTable : public BaseAction {
public:
    OpenTable(int id, std::vector<Customer *> &customersList);
    //copy constructor
    OpenTable(const OpenTable& other);
    //destructor
    ~OpenTable();
    //move constractor
    OpenTable(OpenTable&& other);
    //move assignment
    OpenTable& operator=(OpenTable&& other);
    //copy assignment
    OpenTable&operator=(const OpenTable& other);

    void act(Restaurant &restaurant);
    std::string toString() const;
    BaseAction* copy() const ;// copy function- coppying this
private:
	const int tableId;
	 std::vector<Customer *> customers;
	std::string s="";
};


class Order : public BaseAction {
public:
    Order(int id);
    void act(Restaurant &restaurant);
    std::string toString() const;
    BaseAction* copy() const ;//copy function
    //void GetTheOrders(Table* t);//gets a table and returns a string of all the orders &customers
   // std::string Getcorder(Customer* c,std::vector<OrderPair&>order);//gets the orders of a specific cusotmer and returns a string of them
private:
    const int tableId;
};


class MoveCustomer : public BaseAction {
public:
    MoveCustomer(int src, int dst, int customerId);
    void act(Restaurant &restaurant);
    std::string toString() const;
    BaseAction* copy() const ;//copy function
    int GetC(int id,std::vector<Customer*>clist);
    std::vector<OrderPair> orderswittoutc(int cid, std::vector<OrderPair> OrderList);


private:
    const int srcTable;
    const int dstTable;
    const int id;

};


class Close : public BaseAction {
public:
    Close(int id);
    void act(Restaurant &restaurant);
    std::string toString() const;
    BaseAction* copy() const ;//copy function
private:
    const int tableId;
    std::string ans;
};


class CloseAll : public BaseAction {
public:
    CloseAll();
    void act(Restaurant &restaurant);
    std::string toString() const;
    BaseAction* copy() const ;//copy function
    std::vector<Table*> sortbyid(std::vector<Table*> tables);
	int findmin(std::vector<Table*> tables);
private:
	std::string stg="";
};


class PrintMenu : public BaseAction {
public:
    PrintMenu();
    void act(Restaurant &restaurant);
    std::string toString() const;
    BaseAction* copy() const ;//copy function
private:
	std::string stg="";
};


class PrintTableStatus : public BaseAction {
public:
    PrintTableStatus(int id);
    void act(Restaurant &restaurant);
    std::string toString() const;
    BaseAction* copy() const ;//copy function
    std::string booltostring(bool t);
private:
    const int tableId;
    std::string outpt="";
};


class PrintActionsLog : public BaseAction {
public:
    PrintActionsLog();
    void act(Restaurant &restaurant);
    std::string toString() const;
    BaseAction* copy() const ;//copy function
private:
};


class BackupRestaurant : public BaseAction {
public:
    BackupRestaurant();
    void act(Restaurant &restaurant);
    std::string toString() const;
    BaseAction* copy() const ;//copy function

private:
};


class RestoreResturant : public BaseAction {
public:
    RestoreResturant();
    void act(Restaurant &restaurant);
    std::string toString() const;
    BaseAction* copy() const ;//copy function

};


#endif