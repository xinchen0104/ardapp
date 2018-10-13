//
//  Transform.cpp
//  Ardapp
//
//  Created by xinchen on 2018/10/5.
//  Copyright © 2018 xinchen. All rights reserved.
//

#include "Transform.hpp"
//传入平移向量，返回平移矩阵
Matrix4f Transform::TranslateMat(Vector4f shift){
    Matrix4f mat = Matrix4f();
    mat << 1.0, 0.0, 0.0, shift(0),
    0.0, 1.0, 0.0, shift(1),
    0.0, 0.0, 1.0, shift(2),
    0.0, 0.0, 0.0, 1.0;
    return mat;
}
//传入欧拉角，返回旋转矩阵，旋转顺序为内旋zyx
Matrix4f Transform::RotateEulerMat(Vector4f angle){
    Matrix4f mat = Matrix4f();
    mat << 1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0;
    if(angle(2) > 1e-6 || angle(2) < -(1e-6)){
        Matrix4f matz = Matrix4f();
        matz << cos(angle(2)), -sin(angle(2)), 0.0, 0.0,
        sin(angle(2)), cos(angle(2)), 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0;
        mat *= matz;
    }
    if(angle(1) > 1e-6 || angle(1) < -(1e-6)){
        Matrix4f maty = Matrix4f();
        maty << cos(angle(1)), 0.0, sin(angle(1)),0.0,
        0.0, 1.0, 0.0, 0.0,
        -sin(angle(1)), 0.0, cos(angle(1)), 0.0,
        0.0, 0.0, 0.0, 1.0;
        mat *= maty;
    }
    if(angle(0) > 1e-6 || angle(0) < -(1e-6)){
        Matrix4f matx = Matrix4f();
        matx <<1.0, 0.0, 0.0, 0.0,
        0.0, cos(angle(0)), -sin(angle(0)), 0.0,
        0.0, sin(angle(0)), cos(angle(0)), 0.0,
        0.0, 0.0, 0.0, 1.0;
        mat *= matx;
    }
    return mat;
}
//传入缩放系数，返回缩放矩阵
Matrix4f Transform::ScaleMat(Vector4f ratio){
    Matrix4f mat = Matrix4f();
    mat << ratio(0), 0.0, 0.0, 0.0,
    0.0, ratio(1), 0.0, 0.0,
    0.0, 0.0, ratio(2), 0.0,
    0.0, 0.0, 0.0, 1.0;
    return mat;
}
Matrix4f Transform::ScaleMat(float ratio){
    Matrix4f mat = Matrix4f();
    mat << ratio, 0.0, 0.0, 0.0,
    0.0, ratio, 0.0, 0.0,
    0.0, 0.0, ratio, 0.0,
    0.0, 0.0, 0.0, 1.0;
    return mat;
}
