//
//  Triangle.hpp
//  Ardapp
//
//  Created by xinchen on 2018/9/20.
//  Copyright © 2018 xinchen. All rights reserved.
//

#ifndef Triangle_hpp
#define Triangle_hpp

#include <cstdio>
#include "object/Vertex.hpp"
#include "geometry/Operation.hpp"
class Triangle3f{
public:
    //是否只对顶点坐标进行变换，主要针对法线
    //若设置为TRANSFORM_VERTECES_ONLY，将不会变换多边形及顶点的法线
    static const int TRANSFORM_VERTECES_ONLY = 0x0001;
    //多边形状态
    static const int TRIANGLE_STATE_NULL = 0x0000;
    static const int TRIANGLE_STATE_ACTIVE = 0x0001;
    static const int TRIANGLE_STATE_CLIPPED = 0x0002;
    static const int TRIANGLE_STATE_BACKFACE = 0x0004;
    static const int TRIANGLE_STATE_LIT = 0x0008;
    //多边形属性
    static const int TRIANGLE_ATTR_NULL = 0x0000;
    static const int TRIANGLE_ATTR_2SIDE = 0x0001;
    static const int TRIANGLE_ATTR_TRANSPARENT = 0x0002;
    static const int TRIANGLE_ATTR_VERTEXBINDED = 0x0004;
    Vertex3f*   verteces[3];
    Vector4f*   N;
    int         state;
    int         attr;
    //占顶点的权重，实际为三角形面积，但面积可能会变，为防止歧义，使用权重表述
    float       vertex_w;
    Triangle3f(Vertex3f* v0, Vertex3f* v1, Vertex3f* v2, int _attr = Triangle3f::TRIANGLE_ATTR_NULL);
    Triangle3f(const Triangle3f& _t);
    Triangle3f* clone(int attr = Triangle3f::TRIANGLE_ATTR_VERTEXBINDED);
    ~Triangle3f();
    friend ostream& operator<<(ostream& stream, const Triangle3f& triangle);
 /* 多边形操作，暂时没用
    Triangle3f& translation(Vector4f shift);
    Triangle3f& rotateEuler(Vector4f angle);
    Triangle3f& scale(Vector4f ratio);
  */
    Triangle3f& transform(Matrix4f mat, int flag = 0);
    
};


#endif /* Triangle_hpp */
