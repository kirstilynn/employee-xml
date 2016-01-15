//
//  parse.h
//  xml
//
//  Created by Kirsti Norton on 2/27/14.
//  Copyright (c) 2014 Kirsti Norton. All rights reserved.
//

#ifndef xml_parse_h
#define xml_parse_h

#include <string>
#include <iostream>

class Parse {
public:
    std::string getNextTag(std::istream& is);
    std::string getNextValue(std::istream& is);
};

#endif
