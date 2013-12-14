#ifndef FLUX_UTILS_H
#define FLUX_UTILS_H

#define PI      3.14159265f
#define TWO_PI  6.28318530f
#define HALF_PI 1.57079633f
#define DECRADRATIO PI / 180.0f
#define RADDECRATIO 180.0f / P

#define MAXLIGHTS 2

#define STR_VALUE(arg)      #arg
#define STR_TMP(A) STR_VALUE(A)

#define MAXLIGHTS_STR STR_TMP(MAXLIGHTS)

#define CLAMP(A, X, Y) (A < X ? X : (A > Y ? Y : A))
#define HEXTODEC(A) CLAMP((float)(A) / 0xFF, 0x0, 0xFf)
#define DECTORAD(A) A * DECRADRATIO
#define RADTODEC(A) A * RADDECRATIO

typedef unsigned char uchar;

#endif

