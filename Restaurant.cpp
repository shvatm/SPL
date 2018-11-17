#include <iostream>
#include <sstream>
#include "Restaurant.h"
#include "fstream"
#include "iostream"

using namespace std;
/*bool open;                        //writing for me the variables
std::vector<Table*> tables;
std::vector<Dish> menu;
std::vector<BaseAction*> actionsLog;
 int numoftables;
*/
/*---------------constructors---------------*/


//constructor
Restaurant::Restaurant(const std::string &configFilePath)
{
    cid=-1;
    did=-1;
    std:string s1;
    string commandline;
    std::vector<std::string> v;
    std::ifstream f1(configFilePath);
    while (std::getline(f1,s1))
    {
        if(s1[0]=='#')
        {
            commandline=s1;
        }
        else
        {
            if(commandline=="#number of tables")
                numoftables=s1[0];

            if(commandline=="#tables description")
            {

            v=split(s1,',');//capacities array
                for (int j = 0; j < v.size(); ++j)
                {
                    Table* t=new Table(stoi(v[j]));//creating new table
                    tables.push_back(t);

                }

            }

            if(commandline=="#menu")
            { std::vector <string>s2=split(s1,',');
            string name=s2[0];
            DishType type=stringtodishtype(s2[1]);//the type
            int price=stoi(s2[2]);//the price
            did++;
            Dish* d=new Dish(did,name,price,type);



            }



        }
        cout<<s1<<endl;

    }
    //tables=vector<Table*>();
   // menu=vector<Dish>();
    //actionsLog=vector<BaseAction*>();
}

Restaurant::Restaurant() { //the vectors will be constracted from the default
    open= false;
}


//copy constructor
Restaurant::Restaurant(const Restaurant &other):open(other.open)
{
    for (int i = 0; i <other.menu.size() ; ++i) { //coppying the menu
        menu.push_back(other.menu[i]);

    }

    for(int j=0;j<other.tables.size();j=j++)//coppying the tables list
    {
        Table* tmp=other.tables[j]->copy();
        tables.push_back(tmp);
    }


    for (int k = 0; k < other.actionsLog.size(); ++k) {
        BaseAction* tmp=other.actionsLog[k]->copy();
        actionsLog.push_back(tmp);

    }



}


//destructor
Restaurant::~Restaurant() {
    open=false;
    std::vector<Dish>().swap(menu);
    for(int i=0;i<actionsLog.size();i++)
    {
        delete actionsLog[i];//deleting the actions
        actionsLog[i]= nullptr;//deleting the pointer
    }
    for (int j = 0; j<tables.size(); j++) {
        delete tables[j];
        tables[j]=nullptr;

    }


}

/*bool open;                        //writing for me the variables, dont forget to delete
std::vector<Table*> tables;
std::vector<Dish> menu;
std::vector<BaseAction*> actionsLog;
*/

//move constractor
Restaurant::Restaurant(Restaurant &&other) {
    this->tables=move(other.tables);
    this->actionsLog=move(other.actionsLog);
    this->menu=move(other.menu);
    this->open=other.open;
}


//move assignment
Restaurant &Restaurant::operator=(Restaurant &&other) {

    this->tables=move(other.tables);
    this->actionsLog=move(other.actionsLog);
    this->menu=move(other.menu);
    this->open=other.open;
}


//copy assignment
Restaurant& Restaurant::operator=(const Restaurant &other) {// make sure that this is ok

    open=other.open;

    for (int i = 0; i <other.menu.size() ; ++i) { //coppying the menu
        menu.push_back(other.menu[i]);

    }

    for(int j=0;j<other.tables.size();j=j++)//coppying the tables list
    {
        Table* tmp=other.tables[j]->copy();
        tables.push_back(tmp);
    }


    for (int k = 0; k < other.actionsLog.size(); ++k) {
        BaseAction* tmp=other.actionsLog[k]->copy();
        actionsLog.push_back(tmp);

    }
    return *this;
}




/*---------------function---------------*/


const std::vector<BaseAction*>& Restaurant::getActionsLog() const {
    return actionsLog;
}

std::vector<Dish>& Restaurant::getMenu() {
    return menu;
}

int Restaurant::getNumOfTables() const {
    return static_cast<int>(tables.size());
}

void Restaurant::start() {
    std::string act;
    std:: cout<<"Restaurant is now open!"<<+"\n";
    std::getline(std::cin,act);
    std::vector<string> input=split(act,' ');//split the line by spaces into array of words
    if (input[0]=="closeall") {
        CloseAll* cla=new CloseAll();
        cla->act(*this);
    }
    else
    {

        if (input[0] == "open") {
            int id = stoi(input[1]);
            std::vector<Customer *> customers;
            for (int i = 2; i < input.size(); ++i) {
                std::vector<string> c = split(input[i],',');
                std::string name = c[0];
                std::string type = c[1];
                cid = cid + 1;//giving the customer id
                if (type == "chp") {
                    CheapCustomer *chp = new CheapCustomer(name, cid);
                    customers.push_back(chp);
                }
                if (type == "alc") {
                    AlchoholicCustomer *alc = new AlchoholicCustomer(name, cid);
                    customers.push_back(alc);
                }
                if (type == "spc") {
                    CheapCustomer *spc = new CheapCustomer(name, cid);
                    customers.push_back(spc);
                }
                if (type == "veg") {
                    VegetarianCustomer *veg = new VegetarianCustomer(name, cid);
                    customers.push_back(veg);

                }


            }
            OpenTable *ot = new OpenTable(id, customers);
            ot->act(*this);

        }

        if (input[0] == "order") {
            int tid = stoi(input[1]);
            Order *orr = new Order(tid);
            orr->act(*this);
        }
        if (input[0] == "move") {
            MoveCustomer *mc = new MoveCustomer(stoi(input[1]), stoi(input[2]), stoi(input[3]));
            mc->act(*this);

        }
        if (input[0] == "status") {
            int id2 = stoi(input[1]);
            PrintTableStatus *ts = new PrintTableStatus(id2);
            ts->act(*this);
        }

        if (input[0] == "log") {
            PrintActionsLog *lg = new PrintActionsLog();
            lg->act(*this);
        }

        if (input[0] == "backup") {

            BackupRestaurant *br = new BackupRestaurant();
            br->act(*this);
        }

        if (input[0] == "restore") {

            RestoreResturant *rr = new RestoreResturant();
            rr->act(*this);
        }
        if (input[0] == "menu") {
            PrintMenu *pm = new PrintMenu();
            pm->act(*this);
        }

        if (input[0] == "close") {
            Close *cl = new Close(stoi(input[1]));
            cl->act(*this);

        }

    }
}


std::vector<std::string> Restaurant::split(std::string str, char c) {
    std::stringstream s(str);
    std::string s2;
    std::vector<std::string> spiltstring;
    while (std::getline(s, s2, c)) {
        spiltstring.push_back(s2);

    }
    return spiltstring;
}

Table* Restaurant::getTable(int ind) {
    Table* ans= nullptr;
    for (int i = 0; i < tables.size(); ++i) {
        if(tables[i]->getId()==ind)
            ans=tables[i];

    }
    return ans;
}



DishType Restaurant::stringtodishtype(std::string s) {
    //DishType ALC,VEG,BVG,SPC;
    if(s=="ALC")
        return ALC;
    if(s=="VEG")
        return VEG;
    if(s=="BVG")
        return BVG;
    if(s=="SPC")
        return SPC;
}

std::vector<Table *> Restaurant::gettables() {
    return tables;
}

void Restaurant::closerest() {
    open= false;
    CloseAll* b=new CloseAll;
    b->act(*this);
}







