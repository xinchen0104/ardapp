//
//  Color.hpp
//  Ardapp
//
//  Created by xinchen on 2018/9/20.
//  Copyright © 2018 xinchen. All rights reserved.
//

#ifndef Color_hpp
#define Color_hpp

#include <cstdio>
#include <algorithm>
#include <Eigen/Dense>

using Eigen::Vector4i;
using std::ostream;
using std::endl;
using std::max;
using std::min;
class Color{
public:
    //主意这里的alpha值只是与硬件设置RGBA格式保持一致，暂时恒定为255，在光照计算中不使用
    Vector4i*   value;
    uint32_t    value_dword;
    friend  ostream& operator<<(ostream& stream, const Color& color);
    Color& operator=(const Color& _c);
    const Color operator+(const Color& _c);
    const Color operator*(const Color& _c);
    friend const Color operator*(float alpha, Color& _c);
    Color();
    Color(Vector4i _value);
    Color(const Color& _c);
    ~Color();
    inline void _updateValueDword();
};
#endif /* Color_hpp */
