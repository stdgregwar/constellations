#ifndef CONSTELLATIONS_MATHUTILS_H
#define CONSTELLATIONS_MATHUTILS_H

#include <cmath>

constexpr float TO_DEGREES = 180/3.1415;

inline float frac(float x) {
    return modf(x,nullptr);
}

inline float triangleWave(float x) {
    return std::abs( frac( x + 0.5 ) * 2.0 - 1.0 );
}

inline float smoothCurve(float x) {
    return x * x *( 3.0 - 2.0 * x );
}

inline float smoothTriangleWave(float x) {
    return smoothCurve(triangleWave(x));
}

#endif //CONSTELLATIONS_MATHUTILS_H
