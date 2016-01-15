//
//  main.cpp
//  xml
//
//  Created by Kirsti Norton on 2/25/14.
//  Copyright (c) 2014 Kirsti Norton. All rights reserved.
//

#include "Employee.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include<vector>

using namespace std;

string tgetNextTag(std::istream& is) {
    string s;
    size_t openpos;
    getline(is, s, '>');
 
    openpos = s.find_first_of('<');
    s.erase(s.begin()+openpos);
    
    return s;
}

string tgetNextValue(std::istream& is) {
    string value;
    getline(is, value, '<');
    is.unget();
    
    return value;
}

int main(int argc, const char * argv[])
{
    try {
        Employee* e;
        vector<unique_ptr<Employee>> Employees;
        string filename = argv[1];
        ifstream myfile (filename);
        if (myfile.is_open())
        {
            while ((e = move(Employee::fromXML(myfile))) != nullptr) {
                Employees.push_back(unique_ptr<Employee>(e));
            }
           
            fstream eData("employee.bin", ios::in | ios::out | ios::binary | ios::trunc);
            
            for (auto & i : Employees) {
                i->display(cout);
            }
            for (auto & i : Employees) {
                i->write(eData);
            }
            
            eData.clear();
            eData.seekg(0, eData.beg);
            Employees.clear();
            e = Employee::read(eData);
            while (e->isValid()) {
                Employees.push_back(unique_ptr<Employee>(e));
                e = Employee::read(eData);
            }
            
            for (auto & i : Employees) {
                i->toXML(cout);
            }
            
            e = Employee::retrieve(eData, 12345);
            cout << "\nFound:";
            e->display(cout);
            
            e->setSalary(150000.0);
            e->store(eData);
            
            e = Employee::retrieve(eData, 12345);
            cout << e->getSalary() << endl;
            
            Employee newEmp(333, "Kirsti Norton", "33 Triumph Ln.", "Victory", "California", "US", "242-224-2342", 200000.0);
            
            newEmp.store(eData);
            
            cout << "\nFound:";
            Employee::retrieve(eData, 333)->display(cout);
            
            
        }
        else cout << "Unable to open file";
    }
    catch (exception& e) {
        cout << e.what() << endl;
    }
    
}

