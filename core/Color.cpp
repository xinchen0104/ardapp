//
//  Color.cpp
//  Ardapp
//
//  Created by xinchen on 2018/9/20.
//  Copyright © 2018 xinchen. All rights reserved.
//

#include "Color.hpp"
ostream& operator<<(ostream& stream, const Color& color){
    stream << "value:" << std::dec << *(color.value) << endl;
    stream << "value_dword:" << std::hex <<color.value_dword << endl;
    return stream;
}
Color& Color::operator=(const Color& _c){
    if(this == &_c)return *this;
    *(this->value) = *(_c.value);
    this->value_dword = _c.value_dword;
    return *this;
}
Color::Color(Vector4i _value){
    this->value = new Vector4i();
    *(this->value) = _value;
    this->value_dword = (uint32_t)(_value(0)<<24) + (uint32_t)(_value(1)<<16) + (uint32_t)(_value(2)<<8) + (uint32_t)_value(3);
}
Color::Color(const Color& _c){
    this->value = new Vector4i();
    *(this->value) = *(_c.value);
    this->value_dword = _c.value_dword;
}
Color::Color(){
    this->value = new Vector4i();
    this->value_dword = 0;
}
Color::~Color(){
    delete this->value;
}

inline void Color::_updateValueDword(){
    this->value_dword = (uint32_t)((*(this->value))(0)<<24) + (uint32_t)((*(this->value))(1)<<16) + (uint32_t)((*(this->value))(2)<<8) + (uint32_t)(*(this->value))(3);
}

const Color Color::operator+(const Color& _c){
    int r = min(255, (*(this->value))(0) + (*(_c.value))(0));
    int g = min(255, (*(this->value))(1) + (*(_c.value))(1));
    int b = min(255, (*(this->value))(2) + (*(_c.value))(2));
    Vector4i c_value = Vector4i(r, g, b, 255);
    return Color(c_value);
}
const Color Color::operator*(const Color& _c){
    int r = (*(this->value))(0) * (*(_c.value))(0) / 255;
    int g = (*(this->value))(1) * (*(_c.value))(1) / 255;
    int b = (*(this->value))(2) * (*(_c.value))(2) / 255;
    Vector4i c_value = Vector4i(r, g, b, 255);
    return Color(c_value);
}
const Color operator*(float alpha, Color& _c){
    int r = alpha * (*(_c.value))(0);
    int g = alpha * (*(_c.value))(1);
    int b = alpha * (*(_c.value))(2);
    Vector4i c_value = Vector4i(r, g, b, 255);
    return Color(c_value);
}
