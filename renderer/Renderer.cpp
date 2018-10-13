//
//  Renderer.cpp
//  Ardapp
//
//  Created by xinchen on 2018/10/2.
//  Copyright © 2018 xinchen. All rights reserved.
//

#include "Renderer.hpp"
Renderer::~Renderer(){
    for(list<Triangle3f*>::iterator it = this->render_triangle_list.begin();it != this->render_triangle_list.end();it ++){
        delete *it;
    }
}
