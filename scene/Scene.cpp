//
//  Scene.cpp
//  Ardapp
//
//  Created by xinchen on 2018/10/2.
//  Copyright © 2018 xinchen. All rights reserved.
//

#include "Scene.hpp"
Scene::Scene(){
    
}
Scene::~Scene(){
    for(list<Object*>::iterator it = this->object_list.begin();it != this->object_list.end();it ++){
        delete *it;
    }
}
