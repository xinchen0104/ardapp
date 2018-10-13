//
//  Frustum.hpp
//  Ardapp
//
//  Created by xinchen on 2018/10/10.
//  Copyright © 2018 xinchen. All rights reserved.
//

#ifndef Frustum_hpp
#define Frustum_hpp

#include <cstdio>
#include <cmath>
class Frustum{
public:
    float clip_z_near;
    float clip_z_far;
    float visual_angel_horizontal;
    float visual_angel_vertical;
    Frustum(float _clip_z_near = 1.0, float _clip_z_far = 15.0, float _visual_angel_horizontal = M_PI_4, float _visual_angel_vertical = M_PI_4);
};

#endif /* Frustum_hpp */
