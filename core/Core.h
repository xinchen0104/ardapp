//
//  Core.h
//  Ardapp
//
//  Created by xinchen on 2018/9/20.
//  Copyright © 2018 xinchen. All rights reserved.
//

#ifndef     Core_h
#define     Core_h
#define     DEFAULT_SCREEN_BPP          32
#define     _RGBA32(r,g,b,a)            (uint32_t)((a) + ((b) << 8) + ((g) << 16) + ((r) << 24))
#define     R(color)                    (uint8_t)((color) >> 24)
#define     G(color)                    (uint8_t)((color) >> 16)
#define     B(color)                    (uint8_t)((color) >> 8)
#define     A(color)                    (uint8_t)(color)
#define     SET_BIT(word,bit_flag)      ((word)=((word) | (bit_flag)))
#define     RESET_BIT(word,bit_flag)    ((word)=((word) & (~bit_flag)))
#define     uint32_t                    COLOR;


#endif /* Core_h */
