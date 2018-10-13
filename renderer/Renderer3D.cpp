//
//  Renderer3D.cpp
//  Ardapp
//
//  Created by xinchen on 2018/10/2.
//  Copyright © 2018 xinchen. All rights reserved.
//

#include "Renderer3D.hpp"

//3D渲染，结果输出至result_triangle_list
void Renderer3D::render(list<Triangle3f*>* pOutputList){
    Camera* pCamera = this->camera;
    Scene* pScene = this->scene;
    list<Object*>* pObjectList = &(pScene->object_list);
    //释放列表中Triangle内存，清空列表
    for(list<Triangle3f*>::iterator it_tri = pOutputList->begin();it_tri !=  pOutputList->end();it_tri++){
        delete *it_tri;
    }
    pOutputList->clear();
    //todo，物体剔除
    this->cullObject(pObjectList, pCamera);
    
    //遍历场景模型，局部坐标转化为世界坐标，将自包含多边形插入渲染列表
    for(list<Object*>::iterator it_ob = pObjectList->begin();it_ob !=  pObjectList->end();it_ob ++){
        if((*it_ob)->culled)continue;
        list<Triangle3f*>* pTriangle = &((*it_ob)->triangle_list);
        for(list<Triangle3f*>::iterator it_tri = pTriangle->begin();it_tri != pTriangle->end();it_tri ++){
            Triangle3f* tri_vertex_binded = (*it_tri)->clone();
            tri_vertex_binded->transform(*((*it_ob)->MatrixWorld), Triangle3f::TRANSFORM_VERTECES_ONLY);
            pOutputList->push_back(tri_vertex_binded);
        }
    }
    //相机变换
    for(list<Triangle3f*>::iterator it_tri = pOutputList->begin();it_tri !=  pOutputList->end();it_tri++){
        (*it_tri)->transform(*(pCamera->MatrixPosition), Triangle3f::TRANSFORM_VERTECES_ONLY);
        (*it_tri)->transform(*(pCamera->MatrixUVN));
    }
    //背面消隐
    this->cullBackface(pOutputList);
    //透视变换
    for(list<Triangle3f*>::iterator it_tri = pOutputList->begin();it_tri !=  pOutputList->end();it_tri++){
        if((*it_tri)->state & (Triangle3f::TRIANGLE_STATE_CLIPPED | Triangle3f::TRIANGLE_STATE_BACKFACE))continue;
        (*it_tri)->transform(*(pCamera->MatrixPerspective), Triangle3f::TRANSFORM_VERTECES_ONLY);
    }
}
//注意这里剔除直接使用了镜头张角计算，所以只有当张角设置适应屏幕宽高比时，剔除结果才会与显示效果完全一致
//否则可能会出现物体未被剔除，但屏幕上却未显示的情况，但这种误差属于可接受误差
void Renderer3D::cullObject(list<Object*>* pObjectList, Camera* pCamera){
    float clip_z_near = pCamera->frustum->clip_z_near,
    clip_z_far = pCamera->frustum->clip_z_far,
    visual_angel_horizontal = pCamera->frustum->visual_angel_horizontal,
    visual_angel_vertical = pCamera->frustum->visual_angel_vertical;
    Matrix4f m_c = *(pCamera->MatrixCamere);
    for(list<Object*>::iterator it_ob = pObjectList->begin();it_ob !=  pObjectList->end();it_ob ++){
        Vector4f center_trans = m_c * (*((*it_ob)->position));
        if(center_trans(2) + (*it_ob)->max_radius < clip_z_near || center_trans(2) - (*it_ob)->max_radius> clip_z_far){
            (*it_ob)->culled = true;
            continue;
        }
        //(|x| - z * tan) * cos > max_radius
        if((fabs(center_trans(0)) - center_trans(2) * tan(visual_angel_horizontal)) * cos(visual_angel_horizontal) > (*it_ob)->max_radius || (fabs(center_trans(1)) - center_trans(2) * tan(visual_angel_vertical)) * cos(visual_angel_vertical) > (*it_ob)->max_radius){
            (*it_ob)->culled = true;
            continue;
        }
        (*it_ob)->culled = false;
    }
}
//这里约定：
//1.法向量指向外表面
//2.法向量为(p1-p0)x(p2-p0)
//3.左手系
void Renderer3D::cullBackface(list<Triangle3f*>* pOutputList){
    for(list<Triangle3f*>::iterator it_tri = pOutputList->begin();it_tri !=  pOutputList->end();it_tri++){
        if((*it_tri)->attr & Triangle3f::TRIANGLE_ATTR_2SIDE)continue;
        Vector3f v1 = Operation::vec4f2vec3f(*(((*it_tri)->verteces)[0]->position));
        Vector3f v2 = Operation::vec4f2vec3f(*((*it_tri)->N));
        if(v1.dot(v2) > 0){
            (*it_tri)->state |= Triangle3f::TRIANGLE_STATE_BACKFACE;
        }
        
    }
}
