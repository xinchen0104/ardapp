//
//  Triangle.cpp
//  Ardapp
//
//  Created by xinchen on 2018/9/20.
//  Copyright © 2018 xinchen. All rights reserved.
//

#include "Triangle.hpp"
Triangle3f::Triangle3f(Vertex3f* v0, Vertex3f* v1, Vertex3f* v2, int _attr){
    this->verteces[0] = v0;
    this->verteces[1] = v1;
    this->verteces[2] = v2;
    this->attr = _attr;
    this->state = Triangle3f::TRIANGLE_STATE_ACTIVE;
    this->N = new Vector4f();
    *(this->N) = Operation::unitNormal(*(v0->position), *(v1->position), *(v2->position));
    this->vertex_w = Operation::triangleArea(*(v0->position), *(v1->position), *(v2->position));
}
Triangle3f::Triangle3f(const Triangle3f& _t){
    this->attr = _t.attr;
    this->state = _t.state;
    if(_t.attr & Triangle3f::TRIANGLE_ATTR_VERTEXBINDED){
        this->verteces[0] = new Vertex3f(*(_t.verteces[0]));
        this->verteces[1] = new Vertex3f(*(_t.verteces[1]));
        this->verteces[2] = new Vertex3f(*(_t.verteces[2]));
    }else{
        this->verteces[0] = _t.verteces[0];
        this->verteces[1] = _t.verteces[1];
        this->verteces[2] = _t.verteces[2];
    }
    this->N = new Vector4f();
    *(this->N) = *(_t.N);
    this->vertex_w = _t.vertex_w;
}

Triangle3f::~Triangle3f(){
    delete this->N;
    if(this->attr & Triangle3f::TRIANGLE_ATTR_VERTEXBINDED){
        delete this->verteces[0];
        delete this->verteces[1];
        delete this->verteces[2];
    }
}

Triangle3f* Triangle3f::clone(int attr){
    attr = this->attr | attr;
    if(attr & Triangle3f::TRIANGLE_ATTR_VERTEXBINDED){
        Vertex3f* v0 = new Vertex3f(*this->verteces[0]);
        Vertex3f* v1 = new Vertex3f(*this->verteces[1]);
        Vertex3f* v2 = new Vertex3f(*this->verteces[2]);
        Triangle3f* t = new Triangle3f(v0, v1, v2, attr);
        return t;
    }else{
        Triangle3f* t = new Triangle3f(this->verteces[0], this->verteces[1], this->verteces[2], attr);
        return t;
    }
}
ostream& operator<<(ostream& stream, const Triangle3f& triangle){
    stream << "vertex[0]:" << *(triangle.verteces[0])<< endl;
    stream << "vertex[1]:" << *(triangle.verteces[1])<< endl;
    stream << "vertex[2]:" << *(triangle.verteces[2])<< endl;
    return stream;
}
Triangle3f& Triangle3f::transform(Matrix4f mat, int flag){
    int flag_v = 0;
    if(flag & Triangle3f::TRANSFORM_VERTECES_ONLY){
        flag_v |= Vertex3f::TRANSFORM_POSITION_ONLY;
    }else{
        *(this->N) = mat * (*(this->N));
    }
    this->verteces[0]->transform(mat, flag_v);
    this->verteces[1]->transform(mat, flag_v);
    this->verteces[2]->transform(mat, flag_v);
    return *this;
}







