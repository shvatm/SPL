#include <iostream>
#include <sstream>
#include "../include/Restaurant.h"
#include "../include/Table.h"
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


    std::ifstream fileToRead(configFilePath);
    std::string line;
    std::vector<string> relevantLines;


    while (getline(fileToRead,line)) {

        // TAKING ONLY RELEVANTS CONFIG LINES. DELETING COMMENTS END EMPTY LINES PUT EVERYTHING IN A STRING VECTOR
        if (line.at(0) != '#' && line.at(0) != '\r') {
            relevantLines.push_back(line);
            line.erase(line.find_last_not_of(" \r\n\t") + 1);
        }
    }


    // INITIALIZING NUMBER OF TABLES
    numoftables = stoi(relevantLines.at(0));

    // INITIALIZING TABLES CAPACITIES
    std::vector<int> TablesCapacitiesInt;
    string s = relevantLines.at(1);
    string delimiter;
    delimiter = ',';
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        TablesCapacitiesInt.push_back(stoi(token));
        s.erase(0, pos + delimiter.length());
    }
    TablesCapacitiesInt.push_back(stoi(token));
// ADDING TABLES WITH CAPACITIES FROM INT VECTOR
    Table *toAdd;
    for (size_t i = 0; i < TablesCapacitiesInt.size(); i++) {
         toAdd = new Table(TablesCapacitiesInt.at(i));
        tables.push_back(toAdd);
    }

    //ADDING DISHES
    int DishCounter = 0;
    for (size_t i=2;i<relevantLines.size();i++) {
        string currentLine = relevantLines.at(i);
        DishType type;
        int price;
        string name;

        //getting dish name
        name = currentLine.substr(0,currentLine.find(','));

        //getting dish type
        string typeInString = currentLine.substr(name.length()+1,line.find(',')-1);
        if (typeInString.at(0) == 'B')
            type = BVG;

        else if (typeInString.at(0) == 'A')
            type = ALC;

        else if (typeInString.at(0) == 'V')
            type = VEG;

        else if (typeInString.at(0) == 'S')
            type = SPC;

        //getting dish price
        string PriceInString = currentLine.substr(name.length()+5);
        price = stoi(PriceInString);

        Dish toAdd(DishCounter, name, price, type);
        menu.push_back(toAdd);
        DishCounter++;
    }

/*
    cid=-1;
    did=-1;
    std:string s1;
    string commandline;
    std::vector<std::string> v;
    std::ifstream f1;
    f1.open(configFilePath.c_str());
    if (f1.is_open()){std::cout << "open\n";}
    else {std::cout <<"not open\n" << configFilePath << "\n";}
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

    this->start();
*/
}

Restaurant::Restaurant() { //the vectors will be constracted from the default
    open= false;
}


//copy constructor
Restaurant::Restaurant(const Restaurant &other):open(other.open)
{
    for (size_t i = 0; i <other.menu.size() ; ++i) { //coppying the menu
        menu.push_back(other.menu[i]);

    }

    for(size_t j=0;j<other.tables.size();j++)//coppying the tables list
    {
        Table* tmp=other.tables[j]->copy();
        tables.push_back(tmp);
    }


    for (size_t k = 0; k < other.actionsLog.size(); ++k) {
        BaseAction* tmp=other.actionsLog[k]->copy();
        actionsLog.push_back(tmp);

    }



}


//destructor
Restaurant::~Restaurant() {
    open=false;
    menu.clear();
    for(size_t i=0;i<actionsLog.size();i++)
    {
        delete actionsLog[i];//deleting the actions
        actionsLog[i]= nullptr;//deleting the pointer
    }
    actionsLog.clear();
    for (size_t j = 0; j<tables.size(); j++) {
        delete tables[j];
        tables[j]=nullptr;

    }
    tables.clear();

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

    return *this;
}


//copy assignment
Restaurant& Restaurant::operator=(const Restaurant &other) {// make sure that this is ok

    open=other.open;

    for (size_t i = 0; i <other.menu.size() ; ++i) { //coppying the menu
        menu.push_back(other.menu[i]);

    }

    for(size_t j=0;j<other.tables.size();j++)//coppying the tables list
    {
        Table* tmp=other.tables[j]->copy();
        tables.push_back(tmp);
    }


    for (size_t k = 0; k < other.actionsLog.size(); ++k) {
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

    this->open= true;
    std::string act;
    std:: cout<<"Restaurant is now open!"<<+"\n";
    cid=0;
    did=0;

    while(act!="closeall")
    {
        std::getline(std::cin,act);
        std::vector<string> input=split(act,' ');//split the line by spaces into array of words
        BaseAction* nextAct;
        if (input[0] == "open") {
            int id = stoi(input[1]);
            std::vector<Customer *> customers;
            for (size_t i = 2; i < input.size(); ++i) {
                std::vector<string> c = split(input[i],',');
                std::string name = c[0];
                std::string type = c[1];
                //cid = cid + 1;//giving the customer id
                if (type == "chp") {
                    CheapCustomer*chp = new CheapCustomer(name, cid++);
                    customers.push_back(chp);
                }
                if (type == "alc") {
                    AlchoholicCustomer *alc = new AlchoholicCustomer(name, cid++);
                    customers.push_back(alc);
                }
                if (type == "spc") {
                    SpicyCustomer *spc = new SpicyCustomer(name, cid++);
                    customers.push_back(spc);
                }
                if (type == "veg") {
                    VegetarianCustomer *veg = new VegetarianCustomer(name,cid++);
                    customers.push_back(veg);

                }


            }
            nextAct = new OpenTable(id, customers);

        }

        if (input[0] == "order") {
            int tid = stoi(input[1]);
            nextAct = new Order(tid);

        }
        if (input[0] == "move") {
            nextAct = new MoveCustomer(stoi(input[1]), stoi(input[2]), stoi(input[3]));


        }
        if (input[0] == "status") {
            int id2 = stoi(input[1]);
            nextAct = new PrintTableStatus(id2);

        }

        if (input[0] == "log") {
            nextAct = new PrintActionsLog();

        }

        if (input[0] == "backup") {

            nextAct = new BackupRestaurant();

        }

        if (input[0] == "restore") {

            nextAct = new RestoreResturant();

        }
        if (input[0] == "menu") {
            nextAct = new PrintMenu();

        }

        if (input[0] == "close") {
            nextAct = new Close(stoi(input[1]));


        }
        if (input[0]=="closeall") {
            nextAct = new CloseAll();

        }

        nextAct->act(*this);
        this->actionsLog.push_back(nextAct);
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
    if (ind<(signed)tables.size()){
    return tables.at(ind);}
    else{return nullptr;}
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

    return BVG;
}

std::vector<Table *> Restaurant::gettables() {
    return tables;
}

void Restaurant::closerest() {
    open= false;
    //CloseAll* b=new CloseAll;
    //b->act(*this);
}







