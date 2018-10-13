//
//  Object.cpp
//  Ardapp
//
//  Created by xinchen on 2018/10/2.
//  Copyright © 2018 xinchen. All rights reserved.
//

#include "Object.hpp"
Object::Object(){
    this->position = new Vector4f(0.0, 0.0, 0.0, 1.0);
    this->ux = new Vector4f(1.0, 0.0, 0.0, 1.0);
    this->uy = new Vector4f(0.0, 1.0, 0.0, 1.0);
    this->uz = new Vector4f(0.0, 0.0, 1.0, 1.0);
    this->MatrixWorld = new Matrix4f();
    *(this->MatrixWorld) << 1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0;
    this->culled = false;
}
Object::Object(Mesh* mesh, float ratio){
    mesh->createObject(this, ratio);
    this->position = new Vector4f(0.0, 0.0, 0.0, 1.0);
    this->ux = new Vector4f(1.0, 0.0, 0.0, 1.0);
    this->uy = new Vector4f(0.0, 1.0, 0.0, 1.0);
    this->uz = new Vector4f(0.0, 0.0, 1.0, 1.0);
    this->MatrixWorld = new Matrix4f();
    *(this->MatrixWorld) << 1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0;
    this->culled = false;
}
Object::~Object(){
    delete this->position;
    delete this->MatrixWorld;
    delete this->ux;
    delete this->uy;
    delete this->uz;
    for(list<Vertex3f*>::iterator it = this->vertex_list.begin();it != this->vertex_list.end();it ++){
        delete *it;
    }
    for(list<Triangle3f*>::iterator it = this->triangle_list.begin();it != this->triangle_list.end();it ++){
        delete *it;
    }
}
//该函数直接对顶点进行矩阵变换，但没有考虑对局部坐标系，半径等的影响，一般不能直接使用
Object& Object::transform(Matrix4f mat){
    for(list<Vertex3f*>::iterator it = this->vertex_list.begin();it != this->vertex_list.end();it ++){
        (*it)->transform(mat);
    }
    return *this;
}
void Object::setPosition(Vector4f _p){
    *(this->position) = _p;
    *(this->MatrixWorld) << 1.0, 0.0, 0.0, _p(0),
    0.0, 1.0, 0.0, _p(1),
    0.0, 0.0, 1.0, _p(2),
    0.0, 0.0, 0.0, 1.0;
}
//平移对象，直接移动position
Object& Object::translate(Vector4f shift){
    Matrix4f m_t = Transform::TranslateMat(shift);
    *(this->position) = m_t * (*(this->position));
    return *this;
}
//欧拉旋转操作，对顶点列表进行旋转，同时模型朝向向量需要旋转
//虽然ux，uy，uz跟踪了模型的朝向变化，但不能认为物体坐标系发生了变化
//因为欧拉角旋转方法总是假定动态坐标系和静态坐标系一开始是重合的，在这个前提下，xyz外旋和zyx内旋才是等价的
//用方程很容易证明，对三个坐标轴依次进行欧拉旋转操作，得到的是该顺序的外旋。同样的，多次平凡欧拉旋转得到的是广义的“外旋”结果
//所以多步使用欧拉角旋转时需注意，如果旋转前模型朝向已经发生了变化，uz向量并不是zyx内旋第一次旋转的旋转轴，旋转轴仍为z轴
//此时若想以uz为轴，应该使用四元数方法
Object& Object::rotateEuler(Vector4f angle){
    for(list<Vertex3f*>::iterator it = this->vertex_list.begin();it != this->vertex_list.end();it ++){
        (*it)->rotateEuler(angle);
    }
    Matrix4f m_r = Transform::RotateEulerMat(angle);
    *(this->ux) = m_r * (*(this->ux));
    *(this->uy) = m_r * (*(this->uy));
    *(this->uz) = m_r * (*(this->uz));
    return *this;
}
//缩放对象，需要重新计算半径
//重算法线，todo
Object& Object::scale(Vector4f ratio){
    for(list<Vertex3f*>::iterator it = this->vertex_list.begin();it != this->vertex_list.end();it ++){
        (*it)->scale(ratio);
    }
    caculateMaxRadius();
    return *this;
}
Object& Object::scale(float ratio){
    for(list<Vertex3f*>::iterator it = this->vertex_list.begin();it != this->vertex_list.end();it ++){
        (*it)->scale(ratio);
    }
    this->max_radius = this->max_radius * ratio;
    return *this;
}
void Object::caculateMaxRadius(){
    float max_radius = 0.0, i_radius = 0.0;
    for(list<Vertex3f*>::iterator it = this->vertex_list.begin();it != this->vertex_list.end();it ++){
        i_radius = Operation::length(*((*it)->position));
        if(i_radius > max_radius)max_radius = i_radius;
    }
    this->max_radius = max_radius;
}

