//
//  Vertex.hpp
//  Ardapp
//
//  Created by xinchen on 2018/9/20.
//  Copyright © 2018 xinchen. All rights reserved.
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include <cstdio>
#include <Eigen/Dense>
#include "core/Color.hpp"
#include "geometry/Transform.hpp"


using Eigen::Vector4f;
using Eigen::Vector4i;
using Eigen::Matrix4f;


class Vertex3f{
public:
    static const int TRANSFORM_POSITION_ONLY = 0x0001;
    Vector4f*       position;
    Color*          color;
    Vector4f*       N;
    Vertex3f(Vector4f _position, Color* _color);
    Vertex3f(Vector4f _position);
    Vertex3f(const Vertex3f& _v);
    Vertex3f();
    ~Vertex3f();
    friend ostream& operator<<(ostream& stream, const Vertex3f& vertex);
    Vertex3f& operator=(const Vertex3f& _v);
    Vertex3f& translate(Vector4f shift);
    Vertex3f& rotateEuler(Vector4f angle);
    Vertex3f& scale(Vector4f ratio);
    Vertex3f& scale(float ratio);
    Vertex3f& transform(Matrix4f mat, int flag = 0);
};

#endif /* Vertex_hpp */
