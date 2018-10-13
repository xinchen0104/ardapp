#//
//  AmbientLightSource.hpp
//  Ardapp
//
//  Created by xinchen on 2018/10/12.
//  Copyright © 2018 xinchen. All rights reserved.
//

#ifndef AmbientLightSource_hpp
#define AmbientLightSource_hpp

#include <cstdio>
#include "object/primitives/Triangle.hpp"
#include "LightSource.hpp"
class AmbientLightSource : public LightSource{
public:
    void light(list<Triangle3f*>* pOutputList, int shading_mode);
};

#endif /* AmbientLightSource_hpp */
