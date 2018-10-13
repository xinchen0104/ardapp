//
//  Object.hpp
//  Ardapp
//
//  Created by xinchen on 2018/10/2.
//  Copyright © 2018 xinchen. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include <cstdio>
#include <list>
#include <string>
#include "geometry/Transform.hpp"
#include "primitives/Triangle.hpp"
#include "resource/Mesh.hpp"
#include "geometry/Operation.hpp"
using std::list;
using std::string;
class Mesh;

class Object{
public:
    //世界坐标
    Vector4f* position;
    //最大半径
    float max_radius;
    bool culled;
    //模型朝向向量，ux，uy，uz变量名可能会产生误解，这里的含义更类似于相机的uvn向量，详见rotateEuler()的注释
    Vector4f* ux;
    Vector4f* uy;
    Vector4f* uz;
    //局部坐标->世界坐标变换矩阵
    Matrix4f* MatrixWorld;
    //变换后的模型顶点列表，三角形列表
    list<Vertex3f*> vertex_list;
    list<Triangle3f*> triangle_list;
    Object(Mesh* mesh, float ratio = 1.0);
    Object();
    ~Object();
    //对vertex_list进行矩阵操作
    Object& transform(Matrix4f mat);
    Object& translate(Vector4f shift);
    Object& rotateEuler(Vector4f angle);
    Object& scale(Vector4f ratio);
    Object& scale(float ratio);
    void caculateMaxRadius();
    
    //设置世界坐标
    void setPosition(Vector4f _p);
};

#endif /* Object_hpp */
