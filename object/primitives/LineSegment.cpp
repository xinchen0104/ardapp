//
//  LineSegment.cpp
//  Ardapp
//
//  Created by xinchen on 2018/9/20.
//  Copyright © 2018 xinchen. All rights reserved.
//

#include "LineSegment.hpp"
LineSegment3f::LineSegment3f(Vertex3f* v0, Vertex3f* v1){
    this->verteces[0] = new Vertex3f(*v0);
    this->verteces[1] = new Vertex3f(*v1);
    this->visible = true;
}
LineSegment3f::~LineSegment3f(){
    delete verteces[0];
    delete verteces[1];
}

