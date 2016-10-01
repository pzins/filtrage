#ifndef MANAGER_H
#define MANAGER_H
#include <iostream>

class Manager
{
public:
    static Manager& getInstance(){
        if(!instance){
            instance = new Manager();
            return *instance;
        }
        return *instance;
    }
    void print(){std::cout << "Hello I'm the manager" << std::endl;}
private:
    Manager();
    static Manager* instance;
};

#endif // MANAGER_H
