//
//  ObjectLoader.hpp
//  Ardapp
//
//  Created by xinchen on 2018/10/8.
//  Copyright © 2018 xinchen. All rights reserved.
//

#ifndef ObjectLoader_hpp
#define ObjectLoader_hpp

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include "object/Object.hpp"
#include "resource/Mesh.hpp"
#include "geometry/Operation.hpp"
using std::string;
using std::ifstream;
using std::stringstream;
using std::ptr_fun;
using std::find_if;
using std::vector;

class ObjectLoader{
public:
    int load(string path, Mesh* mesh, bool reverse_z = false);//考虑换为二进制码
    int loadPLX(string path, Mesh* mesh, bool reverse_z = false);
    bool isValidLine(string &str);
    inline string& ltrim(string &str);
    inline string& rtrim(string &str);
    inline string& trim(string &str);
};
#endif /* ObjectLoader_hpp */



