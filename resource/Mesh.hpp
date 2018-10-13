//
//  Mesh.hpp
//  Ardapp
//
//  Created by xinchen on 2018/10/9.
//  Copyright © 2018 xinchen. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <cstdio>
#include <list>
#include <string>
#include <map>
#include "object/Object.hpp"
using std::list;
using std::string;
using std::map;
using std::pair;
class Object;

class Mesh{
public:
    string name;
    int vertex_num;
    int triangle_num;
    //中心/原点坐标，模型文件可以指定物体视觉中心，加载模型后，会将该中心作为物体局部坐标原点，重新调整各顶点坐标
    //中心位置会影响旋转结果，如果模型文件格式不支持指定中心，建模结束后可将物体平移，使视觉中心位于原点，加载函数会默认中心为（0，0，0）
    //物体剔除操作也会使用视觉中心作为包围球球心
    //加载过程中已处理，所以该变量无实际意义
    Vector4f* origin;
    //最大半径
    float max_radius;
    //模型顶点列表，三角形列表
    list<Vertex3f*> vertex_list;
    list<Triangle3f*> triangle_list;
    //创建新物体时使用的临时映射表
    map<Vertex3f*, Vertex3f*> vertex_map;
    Mesh();
    ~Mesh();
    void createObject(Object* obj, float ratio);
    static void calcVertecesNormal(list<Triangle3f*>* pTriangleList, list<Vertex3f*>* pVertexList);
    //void caculateMaxRadius();
};
#endif /* Mesh_hpp */
