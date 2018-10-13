//
//  Renderer2D.hpp
//  Ardapp
//
//  Created by xinchen on 2018/9/21.
//  Copyright © 2018 xinchen. All rights reserved.
//

#ifndef Renderer2D_hpp
#define Renderer2D_hpp

#include <cstdio>
#include <iostream>
#include <cstdint>
#include <list>
#include <Eigen/Dense>
#include "object/primitives/LineSegment.hpp"
#include "object/primitives/Triangle.hpp"
#include "conf/Conf.hpp"
using Eigen::Vector4f;
using Eigen::Matrix4f;
using std::list;
class Renderer2D{
public:
    uint32_t    canvas_size_x;
    uint32_t    canvas_size_y;
    int         lpitch_byte;
    uint32_t*   buffer;
    Matrix4f*   MatrixScreen;
    Renderer2D(uint32_t _canvas_size_x, uint32_t _canvas_size_y);
    ~Renderer2D();
    //齐次坐标归一化
    void HomogeneousNormalize(Vertex3f* vertex);
    //二维绘制前根据画布长宽比调整归一化坐标
    void RatioAdapt(Vertex3f* vertex);
    //线段绘制
    void DrawLineSegment(LineSegment3f* lineSegment);
    //线段裁剪
    LineSegment3f* ClipLineSegment(LineSegment3f* lineSegment);
    //线框绘制三角形
    void DrawTriangle(Triangle3f* triangle);
    void FillTriangle(Triangle3f* triangle, int shading_mode);
    void render(list<Triangle3f*>* pOutputList);
    void clear();
};
#endif /* Renderer2D_hpp */
