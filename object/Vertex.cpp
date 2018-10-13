//
//  Vertex.cpp
//  Ardapp
//
//  Created by xinchen on 2018/9/20.
//  Copyright © 2018 xinchen. All rights reserved.
//

#include "Vertex.hpp"
Vertex3f::Vertex3f(Vector4f _position, Color* _color){
    this->position = new Vector4f();
    *(this->position) = _position;
    this->N = new Vector4f();
    this->color = _color;
}
Vertex3f::Vertex3f(Vector4f _position){
    this->position = new Vector4f();
    *(this->position) = _position;
    this->N = new Vector4f();
    this->color = new Color();
}
Vertex3f::Vertex3f(const Vertex3f& _v){
    this->position = new Vector4f();
    *(this->position) = *(_v.position);
    this->N = new Vector4f();
    *(this->N) = *(_v.N);
    this->color = new Color(*(_v.color));
}
Vertex3f::Vertex3f(){
    this->position = new Vector4f();
    this->color = new Color();
    this->N = new Vector4f();
}
Vertex3f::~Vertex3f(){
    delete this->position;
    delete this->color;
    delete this->N;
}
ostream& operator<<(ostream& stream, const Vertex3f& vertex){
    stream << "position:" << *(vertex.position)<< endl;
    stream << "color:" << *(vertex.color)<< endl;
    return stream;
}
Vertex3f& Vertex3f::operator=(const Vertex3f& _v){
    if(this == &_v)return *this;
    *(this->position) = *(_v.position);
    *(this->color) = *(_v.color);
    *(this->N) = *(_v.N);
    return *this;
}
Vertex3f& Vertex3f::transform(Matrix4f mat, int flag){
    *(this->position) = mat * (*(this->position));
    if(flag & Vertex3f::TRANSFORM_POSITION_ONLY){
        //do nothing
    }else{
        *(this->N) = mat * (*(this->N));
    }
    return *this;
}

Vertex3f& Vertex3f::translate(Vector4f shift){
    *(this->position) = Transform::TranslateMat(shift) * (*(this->position));
    return *this;
}
Vertex3f& Vertex3f::rotateEuler(Vector4f angle){
    *(this->position) = Transform::RotateEulerMat(angle) * (*(this->position));
    *(this->N) = Transform::RotateEulerMat(angle) * (*(this->N));
    return *this;
}
Vertex3f& Vertex3f::scale(Vector4f ratio){
    *(this->position) = Transform::ScaleMat(ratio) * (*(this->position));
    return *this;
}
Vertex3f& Vertex3f::scale(float ratio){
    *(this->position) = Transform::ScaleMat(ratio) * (*(this->position));
    return *this;
}

