//
//  Mesh.cpp
//  Ardapp
//
//  Created by xinchen on 2018/10/9.
//  Copyright © 2018 xinchen. All rights reserved.
//

#include "Mesh.hpp"
Mesh::Mesh(){
    this->origin = new Vector4f(0.0, 0.0, 0.0, 1.0);
}
Mesh::~Mesh(){
    delete this->origin;
    for(list<Triangle3f*>::iterator it = this->triangle_list.begin();it != this->triangle_list.end();it ++){
        delete *it;
    }
    for(list<Vertex3f*>::iterator it = this->vertex_list.begin();it != this->vertex_list.end();it ++){
        delete *it;
    }
}
void Mesh::createObject(Object* obj, float ratio){
    obj->max_radius = this->max_radius * ratio;
    //遍历mesh顶点列表，复制并插入初始化对象的顶点列表，并建立顶点指针映射
    for(list<Vertex3f*>::iterator it = this->vertex_list.begin();it != this->vertex_list.end();it ++){
        Vertex3f* v = new Vertex3f(**it);
        (*(v->position))(0) = (*(v->position))(0) * ratio;
        (*(v->position))(1) = (*(v->position))(1) * ratio;
        (*(v->position))(2) = (*(v->position))(2) * ratio;
        (this->vertex_map).insert(pair<Vertex3f*, Vertex3f*>(*it, v));
        (obj->vertex_list).push_back(v);
    }
    //遍历mesh多边形列表，复制并插入初始化对象多边形列表，使用map查找顶点指针
    for(list<Triangle3f*>::iterator it = this->triangle_list.begin();it != this->triangle_list.end();it ++){
        Vertex3f* v[3];
        map<Vertex3f*, Vertex3f*>::iterator it_map;
        for(int i = 0;i < 3;i ++){
            it_map = (this->vertex_map).find(((*it)->verteces)[i]);
            v[i] = it_map->second;
        }
        Triangle3f* t = new Triangle3f(v[0], v[1], v[2], false);
        (obj->triangle_list).push_back(t);
    }
    (this->vertex_map).clear();
}
//计算顶点法线
void Mesh::calcVertecesNormal(list<Triangle3f*>* pTriangleList, list<Vertex3f*>* pVertexList){
    //vertex_normal_map为顶点到存放向量计算结果的映射表
    map<Vertex3f*, Vector3f*> vertex_normal_map;
    map<Vertex3f*, Vector3f*>::iterator it_map;
    //v_n为指向存放法线运算结果的指针，n_w为加权后的三角形法向量
    Vector3f* v_n;
    Vector3f n_w;
    //建立映射表
    for(list<Vertex3f*>::iterator it_v = pVertexList->begin();it_v != pVertexList->end();it_v ++){
        v_n = new Vector3f(0.0, 0.0, 0.0);
        vertex_normal_map.insert(pair<Vertex3f*, Vector3f*>(*it_v, v_n));
    }
    //对多边形每一个顶点，从映射表找到存放法线运算结果的三维向量，以面积为权值叠加多边形法线
    for(list<Triangle3f*>::iterator it_t = pTriangleList->begin();it_t != pTriangleList->end();it_t ++){
        n_w = Operation::vec4f2vec3f(*((*it_t)->N)) * (*it_t)->vertex_w;
        for(int i = 0;i < 3;i ++){
            it_map = vertex_normal_map.find(((*it_t)->verteces)[i]);
            v_n = it_map->second;
            *v_n = *v_n + n_w;
        }
    }
    //对列表每一个顶点，单位化法线结果，存入顶点法线
    //释放映射表中存放法线结果的内存
    for(list<Vertex3f*>::iterator it_v = pVertexList->begin();it_v != pVertexList->end();it_v ++){
        it_map = vertex_normal_map.find(*it_v);
        v_n = it_map->second;
        *((*it_v)->N) = Operation::vec3f2vec4f(v_n->normalized());
        delete v_n;
    }
    vertex_normal_map.clear();
}
