//
//  LightSource.hpp
//  Ardapp
//
//  Created by xinchen on 2018/10/11.
//  Copyright © 2018 xinchen. All rights reserved.
//

#ifndef LightSource_hpp
#define LightSource_hpp

#include <stdio.h>
#include <string>
#include <list>
#include "core/Color.hpp"
#include "object/primitives/Triangle.hpp"
using std::string;
using std::list;

class LightSource{
public:
    //光源id
    string id;
    //光源状态
    int stat;
    //光强
    Color* c_ambient;
    Color* c_diffuse;
    Color* c_specular;
    virtual void light(list<Triangle3f*>* pOutputList, int shading_mode) = 0;
};

#endif /* LightSource_hpp */
