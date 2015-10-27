#ifndef MAT4_H
#define MAT4_H

#include <SFML/System/Vector3.hpp>
#include <cstdlib>
#include <vector>

/**
 * @brief Represents 3D transformation
 */
class Mat4
{
public:
    enum Axes
    {
        X_AXIS,
        Y_AXIS,
        Z_AXIS
    };
    Mat4();
    /*Mat4(const Mat4& other);
    Mat4(Mat4&& other);
    Mat4& operator=(const Mat4& other);
    Mat4& operator=(Mat4&& other);*/
    float* operator[](std::size_t i);
    const float* operator[](std::size_t i) const;
    Mat4 operator*(const Mat4& other) const;
    Mat4& operator*=(const Mat4& other);
    sf::Vector3f operator*(const sf::Vector3f& vec) const;
    Mat4& translate(const sf::Vector3f d);
    Mat4& translate(float x, float y, float z);
    Mat4& rotate(float rx, float ry, float rz);
    Mat4& rotate(Axes axe, float angle);
    Mat4& scale(const sf::Vector3f& scale);
    Mat4& scale(float x, float y, float z);
    static Mat4 perspective(float ratio, float angle, float near, float far);
    static Mat4 orthographic(float x1, float x2, float y1, float y2, float z1, float z2);
    static Mat4 translation(const sf::Vector3f& r);
    static Mat4 scaling(const sf::Vector3f &scale);
    static Mat4 rotation(Axes axe,float angle);
    static Mat4 identity();
    ~Mat4();
private:
    std::vector<float> mElements;
};

#endif // MAT4_H
