//
//  Transform.hpp
//  Ardapp
//
//  Created by xinchen on 2018/10/5.
//  Copyright © 2018 xinchen. All rights reserved.
//

#ifndef Transform_hpp
#define Transform_hpp

#include <cstdio>
#include <cmath>
#include <Eigen/Dense>
using Eigen::Vector4f;
using Eigen::Matrix4f;

class Transform{
public:
    //传入平移向量，返回平移矩阵
    static Matrix4f TranslateMat(Vector4f shift);
    //传入欧拉角，返回旋转矩阵，旋转顺序为内旋zyx
    static Matrix4f RotateEulerMat(Vector4f angle);
    //传入缩放系数，返回缩放矩阵
    static Matrix4f ScaleMat(Vector4f ratio);
    static Matrix4f ScaleMat(float ratio);
};

#endif /* Transform_hpp */
