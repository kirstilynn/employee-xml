//
//  Employee.cpp
//  xml
//
//  Created by Kirsti Norton on 2/25/14.
//  Copyright (c) 2014 Kirsti Norton. All rights reserved.
//

#include "Employee.h"

using namespace std;

Parse Employee::p = Parse();

void Employee::write(std::ostream& os) const {
    emprec outbuf;
    outbuf.id = id;
    strncpy(outbuf.name, name.c_str(), 30)[30] = '\0';
    strncpy(outbuf.address, address.c_str(), 25)[25] = '\0';
    strncpy(outbuf.city, city.c_str(), 20)[20] = '\0';
    strncpy(outbuf.state, state.c_str(), 20)[20] = '\0';
    strncpy(outbuf.country, country.c_str(), 20)[20] = '\0';
    strncpy(outbuf.phone, phone.c_str(), 20)[20] = '\0';
    outbuf.salary = salary;
    os.write(reinterpret_cast<const char*>(&outbuf), sizeof outbuf);
}

Employee* Employee::read(std::istream& is) {
    emprec inbuf;
    is.read(reinterpret_cast<char*>(&inbuf), sizeof inbuf);
    Employee* emp = new Employee;
    if (is) {
        emp->id = inbuf.id;
        emp->name = inbuf.name;
        emp->address = inbuf.address;
        emp->city = inbuf.city;
        emp->state = inbuf.state;
        emp->country = inbuf.country;
        emp->phone = inbuf.phone;
        emp->salary = inbuf.salary;
    }
    return emp;
}

void Employee::store(std::iostream& is) const {
    Employee* e = retrieve(is, id); //set the file to the end of the employee you want to overwrite
    if(e == nullptr){ //record not in file, store at the end
        write(is);
    }
    else {
        is.seekg(-(Employee::recordSize()), ios::cur);
        write(is);
    }
    
}

Employee* Employee::retrieve(std::istream& is, int id) {
    Employee* e = new Employee;
    
    is.clear();
    is.seekg(0, is.beg); //start from begining
    
    e = Employee::read(is);
    while (e->isValid()) {
        if(e->id == id)
            return e;
        else
            e = Employee::read(is);
    }
    is.clear();
    return nullptr;
}

void Employee::display(ostream& os) const {
    //output Employee id
    os << endl << "id: ";
    if(id)
        os << id;
    
    //output Employee name
    os << endl << "name: ";
    if(name.compare(""))
        os << name;
    
    //output Employee address
    os << endl << "address: ";
    if(address.compare(""))
        os << address;
    
    //output Employee city
    os << endl << "city: ";
    if(city.compare(""))
        os << city;
    
    //output Employee state
    os << endl << "state: ";
    if(state.compare(""))
        os << state;
    
    //output Employee country
    os << endl << "country: ";
    if(state.compare(""))
        os << country;

    //output Employee phone
    os << endl << "phone: ";
    if(phone.compare(""))
        os << phone;

    //output Employee salary
    os << endl << "salary: ";
    if(salary)
        os << salary << endl;
}

void Employee::toXML(ostream& os) const {
    
    os << endl << "<Employee>";
    
    //output Employee name
    if(name.compare(""))
        os << endl << "\t<Name>" << name << "</Name>";
    
    //output Employee id
    if(id)
        os << endl << "\t<ID>" << id << "</ID>";
    
    //output Employee address
    if(address.compare(""))
        os << endl << "\t<Address>" << address << "</Address>";
    
    //output Employee city
    if(city.compare(""))
        os << endl << "\t<City>" << city << "</City>";
    
    //output Employee state
    if(state.compare(""))
        os << endl << "\t<State>" << state << "</State>";
    
    //output Employee country
    if(country.compare(""))
        os << endl << "\t<Country>" << country << "<Country>";
    
    //output Employee phone
    if(phone.compare(""))
        os << endl << "\t<Phone>" << phone << "</Phone>";
    
    //output Employee salary
    if(salary)
        os << endl << "\t<Salary>" << salary << "</Salary>" ;
    
    os << endl << "</Employee>" << endl;
    
}

Employee* Employee::fromXML(istream& is) {
    Employee* e = new Employee;
    string etag, ftag, ltag, value;
    int result;
    
    if ( (result = strcasecmp((etag = p.getNextTag(is)).c_str(), string ("employee").c_str())) == 0 ) {
    
        while(strcasecmp((ftag = p.getNextTag(is)).c_str(), string ("/employee").c_str()) != 0) {
    
            value = p.getNextValue(is);
            ltag = p.getNextTag(is);
            
            if(strcasecmp(ftag.c_str(), ltag.substr(1,ltag.length()).c_str()) == 0) {
                if("id" == ftag) {
                    if(e->id == 0)
                        e->id = stoi(value);
                    else //has already been set
                        throw std::runtime_error("Multiple <"+ftag+"> tags");
                }
                
                else if("salary" == ftag) {
                    if(e->salary == 0)
                        e->salary = stof(value);
                    else //has already been set
                        throw std::runtime_error("Multiple <"+ftag+"> tags");
                }
                
                else if("name" == ftag) {
                    if(e->name == "")
                        e->name = value;
                    else //has already been set
                        throw std::runtime_error("Multiple <"+ftag+"> tags");
                }
                
                else if("address" == ftag) {
                    if(e->address == "")
                        e->address = value;
                    else //has already been set
                        throw std::runtime_error("Multiple <"+ftag+"> tags");
                }
                
                else if("city" == ftag) {
                    if(e->city == "")
                        e->city = value;
                    else //has already been set
                        throw std::runtime_error("Multiple <"+ftag+"> tags");
                }
                
                else if("state" == ftag) {
                    if(e->state == "")
                        e->state = value;
                    else //has already been set
                        throw std::runtime_error("Multiple <"+ftag+"> tags");
                }
                
                else if("country" == ftag) {
                    if(e->country == "")
                        e->country = value;
                    else //has already been set
                        throw std::runtime_error("Multiple <"+ftag+"> tags");
                }
                
                else if("phone" == ftag) {
                    if(e->phone == "")
                        e->phone = value;
                    else //has already been set
                        throw std::runtime_error("Multiple <"+ftag+"> tags");
                }
                
                else
                    throw std::runtime_error("Invalid Tag: <" + ftag + ">");
            }
            else if(strcasecmp(ftag.c_str(), string ("employee").c_str()) == 0) {
                throw std::runtime_error("Invalid Tag: <Employee>");
            }
            else {
                throw std::runtime_error("Missing </" + ftag + "> tag");
            }
        }
    }
    else if(etag.find_first_not_of("\r\n ") != string::npos)
        throw std::runtime_error("Missing <Employee> tag");
    else{
        return nullptr;
    }

    
    if(!e->id)
        throw std::runtime_error("Missing <ID> tag");

    if(!e->name.compare(""))
       throw std::runtime_error("Missing <Name> tag");
    
    return e;
}