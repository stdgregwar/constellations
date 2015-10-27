#include "../include/Mat4.h"
#include <cstring>
#include <cmath>

using namespace std;

Mat4::Mat4()
{
    mElements.resize(16,0);
}

/*Mat4::Mat4(const Mat4& other) : Mat4()
{
    memcpy(mElements,other.mElements,16*sizeof(float));
}

Mat4::Mat4(Mat4&& other)
{
    mElements = other.mElements;
    other.mElements = nullptr;
}

Mat4& Mat4::operator=(const Mat4& other)
{
    memcpy(mElements,other.mElements,16*sizeof(float));
}

Mat4& Mat4::operator=(Mat4&& other)
{
    if(mElements)
        delete mElements;
    mElements = other.mElements;
    other.mElements = nullptr;
    return *this;
}*/

Mat4 Mat4::operator*(const Mat4& b) const
{
    const Mat4& a(*this);
    Mat4 r;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            r[i][j] = a[i][0]*b[0][j]+a[i][1]*b[1][j]+a[i][2]*b[2][j]+a[i][3]*b[3][j];

    return r;
}

float* Mat4::operator[](std::size_t i)
{
    return &mElements[i*4];
}

const float* Mat4::operator[](std::size_t i) const
{
    return &mElements[i*4];
}

Mat4& Mat4::operator*=(const Mat4& other)
{
    (*this) = other*(*this);
    return *this;
}

sf::Vector3f Mat4::operator*(const sf::Vector3f& vec) const
{
    const Mat4& m(*this);
    return {
        vec.x * m[0][0] + vec.y * m[0][1] + vec.z * m[0][2] + m[0][3],
        vec.x * m[1][0] + vec.y * m[1][1] + vec.z * m[1][2] + m[1][3],
        vec.x * m[2][0] + vec.y * m[2][1] + vec.z * m[2][2] + m[2][3],
    };
}

Mat4& Mat4::translate(const sf::Vector3f d)
{
    return (*this)*=translation(d);
}

Mat4& Mat4::translate(float x, float y, float z)
{
    return (*this)*=translation(sf::Vector3f(x,y,z));
}

Mat4& Mat4::rotate(float rx, float ry, float rz)
{
    rotate(X_AXIS,rx);
    rotate(Y_AXIS,ry);
    return rotate(Z_AXIS,rz);
}

Mat4& Mat4::rotate(Axes axe, float angle)
{
    return (*this)*=rotation(axe,angle);
}

Mat4& Mat4::scale(const sf::Vector3f& scale)
{
    return (*this)*=scaling(scale);
}

Mat4& Mat4::scale(float x, float y, float z)
{
    return (*this)*=scaling(sf::Vector3f(x,y,z));
}

Mat4::~Mat4()
{
    mElements.clear();
}

Mat4 Mat4::perspective(float ratio, float angle, float near, float far)
{
    constexpr float TO_RADIANS = 3.1415 / 180;
    float zz = far-near;
    Mat4 mat;
    mat[0][0] = 1/tan(angle*TO_RADIANS);
    mat[1][1] = ratio/tan(angle*TO_RADIANS);
    mat[2][2] = (near+far)/zz;
    mat[2][3] = -2*near*far/zz;
    mat[3][2] = 1;
    return mat;
}

Mat4 orthographic(const sf::Vector3f& first, const sf::Vector3f& second)
{
    //TEMP
    return Mat4();
}

Mat4 Mat4::identity()
{
    Mat4 m;
    for(int i = 0; i < 4; i++)
    {
        m[i][i] = i;
    }
    return m;
}

Mat4 Mat4::translation(const sf::Vector3f& r)
{
    Mat4 m;
    m[0][3] = r.x;
    m[1][3] = r.y;
    m[2][3] = r.z;
    return m;
}

Mat4 Mat4::scaling(const sf::Vector3f &s)
{
    Mat4 m;
    m[0][0] = s.x;
    m[1][1] = s.y;
    m[2][2] = s.z;
    m[3][3] = 1;
    return m;
}


Mat4 Mat4::rotation(Axes axe,float angle)
{
    float angleRad = angle * 3.1415 / 180;
    Mat4 m;
    m[3][3] = 1;
    switch(axe)
    {
        case X_AXIS:
            m[0][0] = 1;
            m[1][1] = cos(angleRad);
            m[1][2] = -sin(angleRad);
            m[2][1] = sin(angleRad);
            m[2][2] = cos(angleRad);
            break;
        case Y_AXIS:
            m[0][0] = cos(angleRad);
            m[0][2] = sin(angleRad);
            m[1][1] = 1;
            m[2][0] = -sin(angleRad);
            m[2][2] = cos(angleRad);
            break;
        case Z_AXIS:
            m[0][0] = cos(angleRad);
            m[0][1] = -sin(angleRad);
            m[1][0] = sin(angleRad);
            m[1][1] = cos(angleRad);
            m[2][2] = 1;
            break;
    };
    return m;
}
