//
//  Camera.cpp
//  Ardapp
//
//  Created by xinchen on 2018/9/28.
//  Copyright © 2018 xinchen. All rights reserved.
//

#include "Camera.hpp"
Camera::Camera(){
    this->position = new Vector4f(0.0, 0.0, 0.0, 1.0);
    this->target = new Vector4f(0.0, 0.0, 1.0, 1.0);
    this->frustum = new Frustum();
    this->U = new Vector4f(1.0, 0.0, 0.0, 1.0);
    this->V = new Vector4f(0.0, 1.0, 0.0, 1.0);
    this->N = new Vector4f(0.0, 0.0, 1.0, 1.0);
    this->MatrixPosition = new Matrix4f();
    *(this->MatrixPosition) << 1.0, 0.0, 0.0, -(*(this->position))(0),
                            0.0, 1.0, 0.0, -(*(this->position))(1),
                            0.0, 0.0, 1.0, -(*(this->position))(2),
                            0.0, 0.0, 0.0, 1.0;
    this->MatrixUVN = new Matrix4f();
    *(this->MatrixUVN) << 1.0, 0.0, 0.0, 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            0.0, 0.0, 1.0, 0.0,
                            0.0, 0.0, 0.0, 1.0;
    this->MatrixCamere = new Matrix4f();
    *(this->MatrixCamere) << 1.0, 0.0, 0.0, -(*(this->position))(0),
                            0.0, 1.0, 0.0, -(*(this->position))(1),
                            0.0, 0.0, 1.0, -(*(this->position))(2),
                            0.0, 0.0, 0.0, 1.0;
    this->MatrixPerspective = new Matrix4f();
    *(this->MatrixPerspective) << 1.0, 0.0, 0.0, 0.0,
                                0.0, 1.0, 0.0, 0.0,
                                0.0, 0.0, 1.0, 0.0,
                                0.0, 0.0, 1.0, 0.0;
}
Camera::~Camera(){
    delete this->position;
    delete this->target;
    delete this->frustum;
    delete this->U;
    delete this->V;
    delete this->N;
    delete this->MatrixPosition;
    delete this->MatrixUVN;
    delete this->MatrixCamere;
    delete this->MatrixPerspective;
}
void Camera::SetPosition(Vector4f _position){
    *(this->position) = _position;
    this->ResetMatrixCamera();
}
void Camera::SetTarget(Vector4f _target){
    *(this->target) = _target;
    this->ResetMatrixCamera();
}
void Camera::ResetMatrixCamera(){
    *(this->MatrixPosition) << 1.0, 0.0, 0.0, -(*(this->position))(0),
    0.0, 1.0, 0.0, -(*(this->position))(1),
    0.0, 0.0, 1.0, -(*(this->position))(2),
    0.0, 0.0, 0.0, 1.0;
    *(this->MatrixUVN) << (*(this->U))(0), (*(this->U))(1), (*(this->U))(2), 0.0,
    (*(this->V))(0), (*(this->V))(1), (*(this->V))(2), 0.0,
    (*(this->N))(0), (*(this->N))(1), (*(this->N))(2), 0.0,
    0.0, 0.0, 0.0, 1.0;
    *(this->MatrixCamere) = (*(this->MatrixUVN)) * (*(this->MatrixPosition));
}

void Camera::Translate(Vector4f shift){
    *(this->position) = Transform::TranslateMat(shift) * (*(this->position));
    *(this->target) = Transform::TranslateMat(shift) * (*(this->position));
    this->ResetMatrixCamera();
}
void Camera::RotateEuler(Vector4f angle){
    *(this->U) = Transform::RotateEulerMat(angle) * (*(this->U));
    *(this->V) = Transform::RotateEulerMat(angle) * (*(this->V));
    *(this->N) = Transform::RotateEulerMat(angle) * (*(this->N));
    this->ResetMatrixCamera();
}
