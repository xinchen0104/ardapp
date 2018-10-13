//
//  Renderer3D.hpp
//  Ardapp
//
//  Created by xinchen on 2018/10/2.
//  Copyright © 2018 xinchen. All rights reserved.
//

#ifndef Renderer3D_hpp
#define Renderer3D_hpp

#include <cstdio>
#include <list>
#include <iostream>
#include "camera/Camera.hpp"
#include "scene/Scene.hpp"
using std::list;

class Renderer3D{
public:
    Scene* scene;
    Camera* camera;
    void render(list<Triangle3f*>* pOutputList);
    void cullObject(list<Object*>* pObjectList, Camera* pCamera);
    void cullBackface(list<Triangle3f*>* pOutputList);
};

#endif /* Renderer3D_hpp */
