//
//  Renderer2D.cpp
//  Ardapp
//
//  Created by xinchen on 2018/9/21.
//  Copyright © 2018 xinchen. All rights reserved.
//

#include "Renderer2D.hpp"
Renderer2D::Renderer2D(uint32_t _canvas_size_x, uint32_t _canvas_size_y){
    this->canvas_size_x = _canvas_size_x;
    this->canvas_size_y = _canvas_size_y;
    this->buffer = NULL;
    this->lpitch_byte = 0;
    this->MatrixScreen = new Matrix4f();
    *(this->MatrixScreen) << this->canvas_size_x/2, 0.0, 0.0, this->canvas_size_x/2,
                            0.0, -(int)(this->canvas_size_y)/2, 0.0, this->canvas_size_y/2,
                            0.0, 0.0, 1.0, 0.0,
                            0.0, 0.0, 0.0, 1.0;
}
Renderer2D::~Renderer2D(){
    delete this->MatrixScreen;
}
//简单粗暴的画线法
void Renderer2D::DrawLineSegment(LineSegment3f* lineSegment){
    if(lineSegment->visible == false)return;
    uint32_t lpitch = this->lpitch_byte >> 2;
    float x0 = (*(lineSegment->verteces[0]->position))(0);
    float y0 = (*(lineSegment->verteces[0]->position))(1);
    float x1 = (*(lineSegment->verteces[1]->position))(0);
    float y1 = (*(lineSegment->verteces[1]->position))(1);
    int lx, ly;
    int begin_x, end_x, begin_y, end_y;
    int ix, iy, ibuf;
    float k;
    lx = (x0 - x1 > 0) ? x0 - x1 : x1 - x0;
    ly = (y0 - y1 > 0) ? y0 - y1 : y1 - y0;
    if(lx > ly){
        if(x0 < x1){
            begin_x = x0 + 0.5;
            end_x = x1 + 0.5;
            begin_y = y0 + 0.5;
            end_y = y1 + 0.5;
        }
        else{
            begin_x = x1 + 0.5;
            end_x = x0 + 0.5;
            begin_y = y1 + 0.5;
            end_y = y0 + 0.5;
        }
        k = (float)(end_y - begin_y)/(end_x - begin_x);
        
        for(ix = begin_x, iy = begin_y; ix <= end_x;){
            ibuf = iy * lpitch + ix;
            (this->buffer)[ibuf] = 0xffffff00;
            ix ++;
            iy = (float)begin_y + (ix - begin_x) * k + 0.5;
        }
    }else{
        if(y0 < y1){
            begin_y = y0 + 0.5;
            end_y = y1 + 0.5;
            begin_x = x0 + 0.5;
            end_x = x1 + 0.5;
        }
        else{
            begin_y = y1 + 0.5;
            end_y = y0 + 0.5;
            begin_x = x1 + 0.5;
            end_x = x0 + 0.5;
        }
        k = (float)(end_x - begin_x)/(end_y - begin_y);
        for(iy = begin_y, ix = begin_x; iy <= end_y;){
            ibuf = iy * lpitch + ix;
            (this->buffer)[ibuf] = 0xffffff00;
            iy ++;
            ix = (float)begin_x + (iy - begin_y) * k + 0.5;
        }
    }

}
//传入裁剪前线段，返回裁剪后线段，会修改传入对象
//Cohen-Sutherland算法
LineSegment3f* Renderer2D::ClipLineSegment(LineSegment3f* lineSegment){
    //将平面分为九宫格，初始化标志位
    #define CLIP_CODE_C  0x0000
    #define CLIP_CODE_U  0x0008
    #define CLIP_CODE_D  0x0004
    #define CLIP_CODE_R  0x0002
    #define CLIP_CODE_L  0x0001
    
    #define CLIP_CODE_UR 0x000a
    #define CLIP_CODE_DR 0x0006
    #define CLIP_CODE_UL 0x0009
    #define CLIP_CODE_DL 0x0005
    int v0_code = 0, v1_code = 0;
    float x0_c = 0, y0_c = 0, x1_c = 0, y1_c = 0;
    int min_x = 0, min_y = 0, max_x = this->canvas_size_x - 1, max_y = this->canvas_size_y - 1;
    //提取坐标
    float x0 = (*(lineSegment->verteces[0]->position))(0);
    float y0 = (*(lineSegment->verteces[0]->position))(1);
    float x1 = (*(lineSegment->verteces[1]->position))(0);
    float y1 = (*(lineSegment->verteces[1]->position))(1);
    //判定两点区域
    if(x0 > max_x)v0_code |= CLIP_CODE_R;
    else if(x0 < min_x)v0_code |= CLIP_CODE_L;
    if(y0 > max_y)v0_code |= CLIP_CODE_D;
    else if(y0 < min_y)v0_code |= CLIP_CODE_U;
    if(x1 > max_x)v1_code |= CLIP_CODE_R;
    else if(x1 < min_x)v1_code |= CLIP_CODE_L;
    if(y1 > max_y)v1_code |= CLIP_CODE_D;
    else if(y1 < min_y)v1_code |= CLIP_CODE_U;

    //如果都在窗口内，则不必裁剪
    if(v0_code == 0 && v1_code == 0)
        return lineSegment;
    
    //如果在窗口外同一区域，则全部裁剪
    if(v0_code & v1_code){
        lineSegment->visible = false;
        return lineSegment;
    }

    //除了两种特殊情况
    switch (v0_code) {
        case CLIP_CODE_C:
            x0_c = x0;
            y0_c = y0;
            break;
        case CLIP_CODE_U:
            y0_c = min_y;
            x0_c = x0 + (min_y - y0)*(x1 - x0)/(y1 - y0);
            break;
        case CLIP_CODE_D:
            y0_c = max_y;
            x0_c = x0 + (max_y - y0)*(x1 - x0)/(y1 - y0);
            break;
        case CLIP_CODE_L:
            x0_c = min_x;
            y0_c = y0 + (min_x - x0)*(y1 - y0)/(x1 - x0);
            break;
        case CLIP_CODE_R:
            x0_c = max_x;
            y0_c = y0 + (max_x - x0)*(y1 - y0)/(x1 - x0);
            break;
        case CLIP_CODE_UL:
            y0_c = min_y;
            x0_c = x0 + (min_y - y0)*(x1 - x0)/(y1 - y0);
            if(x0_c < min_x || x0_c > max_x){
                x0_c = min_x;
                y0_c = y0 + (min_x - x0)*(y1 - y0)/(x1 - x0);
            }
            break;
        case CLIP_CODE_UR:
            y0_c = min_y;
            x0_c = x0 + (min_y - y0)*(x1 - x0)/(y1 - y0);
            if(x0_c < min_x || x0_c > max_x){
                x0_c = max_x;
                y0_c = y0 + (max_x - x0)*(y1 - y0)/(x1 - x0);
            }
            break;
        case CLIP_CODE_DL:
            y0_c = max_y;
            x0_c = x0 + (max_y - y0)*(x1 - x0)/(y1 - y0);
            if(x0_c < min_x || x0_c > max_x){
                x0_c = min_x;
                y0_c = y0 + (min_x - x0)*(y1 - y0)/(x1 - x0);
            }
            break;
        case CLIP_CODE_DR:
            y0_c = max_y;
            x0_c = x0 + (max_y - y0)*(x1 - x0)/(y1 - y0);
            if(x0_c < min_x || x0_c > max_x){
                x0_c = max_x;
                y0_c = y0 + (max_x - x0)*(y1 - y0)/(x1 - x0);
            }
            break;
        default:
            break;
    }
    switch (v1_code) {
        case CLIP_CODE_C:
            x1_c = x1;
            y1_c = y1;
            break;
        case CLIP_CODE_U:
            y1_c = min_y;
            x1_c = x1 + (min_y - y1)*(x0 - x1)/(y0 - y1);
            break;
        case CLIP_CODE_D:
            y1_c = max_y;
            x1_c = x1 + (max_y - y1)*(x0 - x1)/(y0 - y1);
            break;
        case CLIP_CODE_L:
            x1_c = min_x;
            y1_c = y1 + (min_x - x1)*(y0 - y1)/(x0 - x1);
            break;
        case CLIP_CODE_R:
            x1_c = max_x;
            y1_c = y1 + (max_x - x1)*(y0 - y1)/(x0 - x1);
            break;
        case CLIP_CODE_UL:
            y1_c = min_y;
            x1_c = x1 + (min_y - y1)*(x0 - x1)/(y0 - y1);
            if(x1_c < min_x || x1_c > max_x){
                x1_c = min_x;
                y1_c = y1 + (min_x - x1)*(y0 - y1)/(x0 - x1);
            }
            break;
        case CLIP_CODE_UR:
            y1_c = min_y;
            x1_c = x1 + (min_y - y1)*(x0 - x1)/(y0 - y1);
            if(x1_c < min_x || x1_c > max_x){
                x1_c = max_x;
                y1_c = y1 + (max_x - x1)*(y0 - y1)/(x0 - x1);
            }
            break;
        case CLIP_CODE_DL:
            y1_c = max_y;
            x1_c = x1 + (max_y - y1)*(x0 - x1)/(y0 - y1);
            if(x1_c < min_x || x1_c > max_x){
                x1_c = min_x;
                y1_c = y1 + (min_x - x1)*(y0 - y1)/(x0 - x1);
            }
            break;
        case CLIP_CODE_DR:
            y1_c = max_y;
            x1_c = x1 + (max_y - y1)*(x0 - x1)/(y0 - y1);
            if(x1_c < min_x || x1_c > max_x){
                x1_c = max_x;
                y1_c = y1 + (max_x - x1)*(y0 - y1)/(x0 - x1);
            }
            break;
        default:
            break;
    }

    if(x0_c < min_x || x0_c > max_x ||
       x1_c < min_x || x1_c > max_x ||
       y0_c < min_y || y0_c > max_y ||
       y1_c < min_y || y1_c > max_y){
        lineSegment->visible = false;
        return lineSegment;
    }

    (*(lineSegment->verteces[0]->position))(0) = x0_c;
    (*(lineSegment->verteces[0]->position))(1) = y0_c;
    (*(lineSegment->verteces[1]->position))(0) = x1_c;
    (*(lineSegment->verteces[1]->position))(1) = y1_c;
    return lineSegment;
}
void Renderer2D::render(list<Triangle3f*>* pOutputList){
    memset((void*)this->buffer, 0 , this->canvas_size_y * this->lpitch_byte);
    for(list<Triangle3f*>::iterator it = pOutputList->begin();it != pOutputList->end();it ++){
        if((*it)->state & Triangle3f::TRIANGLE_STATE_CLIPPED)continue;
        for(int i = 0;i < 3;i ++){
            this->HomogeneousNormalize(((*it)->verteces)[i]);
            this->RatioAdapt(((*it)->verteces)[i]);
        }
        (*it)->transform(*(this->MatrixScreen));
    }
    for(list<Triangle3f*>::iterator it = pOutputList->begin();it != pOutputList->end();it ++){
        if((*it)->state & (Triangle3f::TRIANGLE_STATE_CLIPPED | Triangle3f::TRIANGLE_STATE_BACKFACE))continue;
        this->DrawTriangle(*it);
    }
}
void Renderer2D::DrawTriangle(Triangle3f* triangle){
    std::cout << *triangle << std::endl;
    LineSegment3f l[3] = {
        LineSegment3f(triangle->verteces[0],triangle->verteces[1]),
        LineSegment3f(triangle->verteces[0],triangle->verteces[2]),
        LineSegment3f(triangle->verteces[1],triangle->verteces[2])
    };
    for(int i=0;i<3;i++){
        this->ClipLineSegment(&(l[i]));
        this->DrawLineSegment(&(l[i]));
    }
}
void Renderer2D::FillTriangle(Triangle3f* triangle, int shading_mode){
    
}
void Renderer2D::HomogeneousNormalize(Vertex3f* vertex){
    (*(vertex->position))(0) /= (*(vertex->position))(3);
    (*(vertex->position))(1) /= (*(vertex->position))(3);
    (*(vertex->position))(3) = 1.0;
}
void Renderer2D::RatioAdapt(Vertex3f* vertex){
    (*(vertex->position))(1) = (*(vertex->position))(1) * this->canvas_size_x / this->canvas_size_y;
}
void Renderer2D::clear(){
    memset((void*)this->buffer, 0 , this->canvas_size_y * this->lpitch_byte);
}
