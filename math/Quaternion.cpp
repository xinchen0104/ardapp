//
//  Quaternion.cpp
//  Ardapp
//
//  Created by xinchen on 2018/9/20.
//  Copyright © 2018 xinchen. All rights reserved.
//

#include "Quaternion.hpp"
Quaternion::Quaternion(Vector4f _components){
    this->components = new Vector4f();
    *(this->components) = _components;
}
Quaternion::~Quaternion(){
}
