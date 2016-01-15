//
//  Employee.h
//  xml
//
//  Created by Kirsti Norton on 2/25/14.
//  Copyright (c) 2014 Kirsti Norton. All rights reserved.
//

#include "parse.h"

#include <string>
#include <iostream>
#include <vector>

#ifndef __xml__Employee__
#define __xml__Employee__

class Employee {
    std::string name = "";
    int id = 0;
    std::string address = "";
    std::string city = "";
    std::string state = "";
    std::string country = "";
    std::string phone = "";
    double salary = 0.0;
    static Parse p;
    
    struct emprec {     // Used for file transfer
        int id;
        char name[31];
        char address[26];
        char city[21];
        char state[21];
        char country[21];
        char phone[21];
        int salary;
    };
    
public:
    Employee() {}
    Employee(int id, std::string name, std::string address = NULL, std::string city = NULL,
             std::string state = NULL, std::string country = NULL, std::string phone = NULL, double salary = NULL)
    : id(id), name(name), address(address), city(city), state(state), country(country), phone(phone), salary(salary) {}
    void display(std::ostream&) const;
    void write(std::ostream&) const;
    void store(std::iostream&) const;
    void toXML(std::ostream&) const;
    void setSalary(const double s) { salary = s; }
    const double getSalary() { return salary; }
    bool isValid() const { return (id != 0) && name.compare(""); }
    static Employee* read(std::istream&);
    static Employee* retrieve(std::istream&,int);
    static Employee* fromXML(std::istream&);
    static size_t recordSize() { return sizeof(emprec); }
};


#endif /* defined(__xml__Employee__) */
