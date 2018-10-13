//
//  Frustum.cpp
//  Ardapp
//
//  Created by xinchen on 2018/10/10.
//  Copyright © 2018 xinchen. All rights reserved.
//

#include "Frustum.hpp"
Frustum::Frustum(float _clip_z_near, float _clip_z_far, float _visual_angel_horizontal, float _visual_angel_vertical){
    this->clip_z_near = _clip_z_near;
    this->clip_z_far = _clip_z_far;
    this->visual_angel_horizontal = _visual_angel_horizontal;
    this->visual_angel_vertical = _visual_angel_vertical;
}
