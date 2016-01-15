//
//  parse.cpp
//  xml
//
//  Created by Kirsti Norton on 2/27/14.
//  Copyright (c) 2014 Kirsti Norton. All rights reserved.
//

#include "parse.h"

using namespace std;

string Parse::getNextTag(std::istream& is) {
    string s;
    size_t openpos;
    getline(is, s, '>');
    
    openpos = s.find_first_of('<');
    s.erase(s.begin(), s.begin()+openpos+1);
    
    return s;
}

string Parse::getNextValue(std::istream& is) {
    string value;
    getline(is, value, '<');
    is.unget();
    
    return value;
}