//
//  Scene.hpp
//  Ardapp
//
//  Created by xinchen on 2018/10/2.
//  Copyright © 2018 xinchen. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <cstdio>
#include <list>
using std::list;
#include "object/Object.hpp"
class Scene{
public:
    list<Object*> object_list;
    Scene();
    ~Scene();
};
#endif /* Scene_hpp */
