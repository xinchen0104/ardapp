//
//  Operation.hpp
//  Ardapp
//
//  Created by xinchen on 2018/10/9.
//  Copyright © 2018 xinchen. All rights reserved.
//

#ifndef Operation_hpp
#define Operation_hpp

#include <cstdio>
#include <cmath>
#include "Point.hpp"

class Operation{
public:
    static float distance(Point4f p1, Point4f p2);
    static float length(Vector4f v);
    static Vector4f unitNormal(Point4f p0, Point4f p1, Point4f p2);
    static Vector3f vec4f2vec3f(Vector4f v);
    static Vector4f vec3f2vec4f(Vector3f v);
    static float triangleArea(Point4f p0, Point4f p1, Point4f p2);
};

#endif /* Operation_hpp */
