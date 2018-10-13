//
//  Camera.hpp
//  Ardapp
//
//  Created by xinchen on 2018/9/28.
//  Copyright © 2018 xinchen. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <cstdio>
#include <Eigen/Dense>
#include "geometry/Transform.hpp"
#include "Frustum.hpp"
using Eigen::Vector4f;
using Eigen::Matrix4f;
class Camera{
public:
    Vector4f* position;
    Vector4f* target;
    Frustum* frustum;
    Vector4f* U;
    Vector4f* V;
    Vector4f* N;
    //MatrixCamere = MatrixUVN * MatrixPosition;
    Matrix4f* MatrixPosition;
    Matrix4f* MatrixUVN;
    Matrix4f* MatrixCamere;
    Matrix4f* MatrixPerspective;
    Camera();
    ~Camera();
    void ResetMatrixCamera();
    void SetPosition(Vector4f _position);
    void SetTarget(Vector4f _target);
    void Translate(Vector4f shift);
    void RotateEuler(Vector4f angle);
    void Rotate();//四元数旋转
};

#endif /* Camera_hpp */
