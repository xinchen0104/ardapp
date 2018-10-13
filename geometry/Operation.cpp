//
//  Operation.cpp
//  Ardapp
//
//  Created by xinchen on 2018/10/9.
//  Copyright © 2018 xinchen. All rights reserved.
//

#include "Operation.hpp"
float Operation::distance(Point4f p1, Point4f p2){
    return length(p1 - p2);
}
float Operation::length(Vector4f v){
    return sqrt(v(0) * v(0) + v(1) * v(1) + v(2) * v(2));
}
Vector4f Operation::unitNormal(Point4f p0, Point4f p1, Point4f p2){
    Point3f q0(p0(0), p0(1), p0(2)) , q1(p1(0), p1(1), p1(2)), q2(p2(0), p2(1), p2(2));
    Vector3f qn;
    qn = (q1 - q0).cross(q2 - q0).normalized();
    return Vector4f(qn(0), qn(1), qn(2), 1.0);
}
float Operation::triangleArea(Point4f p0, Point4f p1, Point4f p2){
    Vector3f e0 = vec4f2vec3f(p1) - vec4f2vec3f(p0);
    Vector3f e1 = vec4f2vec3f(p2) - vec4f2vec3f(p0);
    return e0.cross(e1).norm() / 2;
}
Vector3f Operation::vec4f2vec3f(Vector4f v){
    return Vector3f(v(0), v(1), v(2));
}
Vector4f Operation::vec3f2vec4f(Vector3f v){
    return Vector4f(v(0), v(1), v(2), 1.0);
}
