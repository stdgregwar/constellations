#include "../include/Mat4.h"

Mat4::Mat4()
{
    mElements = new float[16];
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

Mat4 Mat4::operator*(const Mat4& b)
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
