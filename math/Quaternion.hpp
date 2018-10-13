//
//  Quaternion.hpp
//  Ardapp
//
//  Created by xinchen on 2018/9/20.
//  Copyright © 2018 xinchen. All rights reserved.
//

#ifndef Quaternion_hpp
#define Quaternion_hpp

#include <cstdio>
#include <Eigen/Dense>

using Eigen::Vector3f;
using Eigen::Vector4f;
using Eigen::Vector3i;
using Eigen::Vector4i;
class Quaternion{
public:
    Vector4f*    components;
    Quaternion(Vector4f _components);
    ~Quaternion();
};
#endif /* Quaternion_hpp */
