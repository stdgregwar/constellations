#ifndef MAT4_H
#define MAT4_H

#include <SFML/System/Vector3.hpp>
#include <cstdlib>

/**
 * @brief Represents 3D transformation
 */
class Mat4
{
public:
    Mat4();
    Mat4(const Mat4& other);
    Mat4(Mat4&& other);
    Mat4 operator*(const Mat4& other);
    Mat4& operator=(const Mat4& other);
    Mat4& operator=(const Mat4&& other);
    float* operator[](std::size_t i);
    Mat4& operator*=(const Mat4& other);
    Mat4& translate(const sf::Vector3f d);
    Mat4& translate(float x, float y, float z);
    Mat4& rotate(float rx, float ry, float rz);
    Mat4& rotate(const sf::Vector3f& axis, float angle);
    Mat4& scale(const sf::Vector3f& scale);
    Mat4& scale(float x, float y, float z);
    static Mat4 perpective(float ratio, float angle, float near, float far);
    static Mat4 orthographic(const sf::Vector3f& first, const sf::Vector3f& second);
    ~Mat4();
private:
    float* mElements;
};

#endif // MAT4_H
