#ifndef TABLE_H_
#define TABLE_H_

#include <vector>
#include "Customer.h"
#include "Dish.h"

typedef std::pair<int, Dish> OrderPair;

class Table{
public:
    Table(int t_capacity);
    int getCapacity() const;
    void addCustomer(Customer* customer);
    void removeCustomer(int id);
    Customer* getCustomer(int id);
    std::vector<Customer*>& getCustomers();
    std::vector<OrderPair>& getOrders();
    void order(const std::vector<Dish> &menu);
    void openTable();
    void closeTable();
    int getBill();
    bool isOpen();
    bool isfull();//returns true if full, false if not
   // int getId() const;



    //copy constructor
    Table(const  Table &other);
    //destructor
    ~Table();

    //move constructor
    Table(Table&& other);

    //move assignment
    Table &operator=(Table&& other);


    //copy assignment
    Table &operator=(const Table &other);

    //copy function
    Table* copy() const ;

    //add a list of customers
    bool addclist(std::vector<Customer*>customerslist);



private:
    int capacity;
    bool open;//true when the table is open, false when it's close
    //int tid=-1;//not sure if its ok that i set it to -1
    std::vector<Customer*> customersList;
    std::vector<OrderPair> orderList; //A list of pairs for each order in a table - (customer_id, Dish)
};


#endif