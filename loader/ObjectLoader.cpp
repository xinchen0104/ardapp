//
//  ObjectLoader.cpp
//  Ardapp
//
//  Created by xinchen on 2018/10/8.
//  Copyright © 2018 xinchen. All rights reserved.
//

#include "ObjectLoader.hpp"
inline string& ObjectLoader::ltrim(string &str) {
    string::iterator p = find_if(str.begin(), str.end(), not1(ptr_fun<int, int>(isspace)));
    str.erase(str.begin(), p);
    return str;
}

inline string& ObjectLoader::rtrim(string &str) {
    string::reverse_iterator p = find_if(str.rbegin(), str.rend(), not1(ptr_fun<int , int>(isspace)));
    str.erase(p.base(), str.end());
    return str;
}

inline string& ObjectLoader::trim(string &str) {
    this->ltrim(this->rtrim(str));
    return str;
}
bool ObjectLoader::isValidLine(string &str){
    this->trim(str);
    if(str.length() == 0 || str.at(0) == '#')return false;
    else return true;
}
int ObjectLoader::load(string path, Mesh* mesh, bool reverse_z){
    return loadPLX(path, mesh, reverse_z);
}
//《3D大师》提供的模型似乎是右手系建模，加载时反转z坐标
int ObjectLoader::loadPLX(string path, Mesh* mesh, bool reverse_z){
    #define PLX_SHADE_MODE_MASK   0x60000000
    #define PLX_2SIDED_MASK       0x10000000
    #define PLX_COLOR_MASK        0x00ffffff

    #define PLX_2SIDED_FLAG              0x10000000
    #define PLX_1SIDED_FLAG              0x00000000

    #define PLX_SHADE_MODE_PURE_FLAG      0x00000000
    #define PLX_SHADE_MODE_CONSTANT_FLAG  0x00000000
    #define PLX_SHADE_MODE_FLAT_FLAG      0x20000000
    #define PLX_SHADE_MODE_GOURAUD_FLAG   0x40000000
    #define PLX_SHADE_MODE_PHONG_FLAG     0x60000000
    #define PLX_SHADE_MODE_FASTPHONG_FLAG 0x60000000
    ifstream fp;
    string buf;
    stringstream bufstream;
    int num_v = 0, num_t = 0;
    //顶点坐标
    float px = 0.0, py = 0.0, pz = 0.0;
    //中心坐标
    float cx = 0.0, cy = 0.0, cz = 0.0;
    //多边形属性，多边形顶点数，暂时不用
    int tri_flag = 0, tri_vertex_num = 3;
    int v0_index = 0, v1_index = 0, v2_index =0;
    float max_radius = 0.0, i_radius = 0.0;
    vector<Vertex3f*> vector_vertex;
    
    fp.open(path);
    if(!fp){
        std::cout << "failed to open file: " << path << std::endl;
        return -1;
    }
    //头信息行
    while(getline(fp, buf)){
        if(this->isValidLine(buf)){
            bufstream << buf;
            bufstream >> mesh->name >> mesh->vertex_num >> mesh->triangle_num;
            num_v = mesh->vertex_num;
            num_t = mesh->triangle_num;
            bufstream.clear();
            break;
        }
    }
    //中心坐标
    while(getline(fp, buf)){
        if(this->isValidLine(buf)){
            bufstream << buf;
            bufstream >> cx >> cy >> cz;
            if(reverse_z)cz = -cz;
            bufstream.clear();
            break;
        }
    }
    //顶点
    while(num_v > 0){
        while(getline(fp, buf)){
            if(this->isValidLine(buf)){
                bufstream << buf;
                bufstream >> px >> py >> pz;
                if(reverse_z)pz = -pz;
                Vertex3f* v = new Vertex3f(Vector4f(px-cx, py-cy, pz-cz, 1.0));
                i_radius = Operation::length(*(v->position));
                if(i_radius > max_radius)max_radius = i_radius;
                vector_vertex.push_back(v);
                (mesh->vertex_list).push_back(v);
                num_v --;
                bufstream.clear();
                break;
            }
        }
    }
    mesh->max_radius = max_radius;
    //多边形
    while(num_t > 0){
        while(getline(fp, buf)){
            if(this->isValidLine(buf)){
                bufstream << buf;
                bufstream >> std::hex >> tri_flag >> std::dec >> tri_vertex_num >> v0_index >> v1_index >> v2_index;
                
                Triangle3f* t = new Triangle3f(vector_vertex.at(v0_index), vector_vertex.at(v1_index), vector_vertex.at(v2_index), false);
                (mesh->triangle_list).push_back(t);
                num_t --;
                bufstream.clear();
                break;
            }
        }
    }
    Mesh::calcVertecesNormal(&(mesh->triangle_list), &(mesh->vertex_list));
    return 0;
}
