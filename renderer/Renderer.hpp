//
//  Renderer.hpp
//  Ardapp
//
//  Created by xinchen on 2018/10/2.
//  Copyright © 2018 xinchen. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <cstdio>
#include "Renderer2D.hpp"
#include "Renderer3D.hpp"
class Renderer{
public:
    Renderer2D* renderer2D;
    Renderer3D* renderer3D;
    list<Triangle3f*> render_triangle_list;
    ~Renderer();
};
#endif /* Renderer_hpp */
