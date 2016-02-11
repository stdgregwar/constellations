#ifndef CONSTELLATIONS_MATHUTILS_H
#define CONSTELLATIONS_MATHUTILS_H

#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265359
#endif

constexpr float TO_DEGREES = 180/3.1415;

/**
 * @brief frac part of the given double
 * @param x
 * @return double frac part
 */
inline float frac(float x) {
    double shit;
    return modf(x,&shit);
}

/**
 * @brief generate a triangle wave whit given x as time
 * @param x
 * @return
 */
inline float triangleWave(float x) {
    return std::abs( frac( x + 0.5 ) * 2.0 - 1.0 );
}

/**
 * @brief smooth waves given as argument (if period is 1)
 * @param x
 * @return
 */
inline float smoothCurve(float x) {
    return x * x *( 3.0 - 2.0 * x );
}

/**
 * @brief smoothTriangleWave
 * @param x
 * @return
 */
inline float stw(float x) {
    return smoothCurve(triangleWave(x))-0.5f;
}



#endif //CONSTELLATIONS_MATHUTILS_H
