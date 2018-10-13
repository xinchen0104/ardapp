//
//  LineSegment.hpp
//  Ardapp
//
//  Created by xinchen on 2018/9/20.
//  Copyright © 2018 xinchen. All rights reserved.
//

#ifndef LineSegment_hpp
#define LineSegment_hpp

#include <cstdio>
#include "object/Vertex.hpp"

class LineSegment3f{
public:
    Vertex3f*   verteces[2];
    bool        visible;
    LineSegment3f(Vertex3f* v0, Vertex3f* v1);
    ~LineSegment3f();
};
#endif /* LineSegment_hpp */
