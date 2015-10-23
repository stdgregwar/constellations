#include "../include/Mat4.h"
#include <cstring>
#include <cmath>

using namespace std;

Mat4::Mat4()
{
    mElements = new float[16];
    for(int i = 0; i < 4; i++)
        for(int j = 0; i < 4; i++)
            (*this)[i][j] = 0;
}

Mat4::Mat4(const Mat4& other) : Mat4()
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
}

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

float* Mat4::operator[](std::size_t i) const
{
    return &mElements[i*4];
}

Mat4& Mat4::operator*=(const Mat4& other)
{
    Mat4 r = other*(*this);
    (*this) = r;
    return *this;
}

Mat4::~Mat4()
{
    if(mElements)
        delete mElements;
}

Mat4 perpective(float ratio, float angle, float near, float far)
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
    Mat4 m;
    switch(axe)
    {
        case X_AXIS:
            break;
    };
}
