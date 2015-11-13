#include "Property.h"
#include <regex>
#include <new>

using namespace std;

Property::Property(Type t)
{
    mType = t;
}

Property::Property(const char *c,bool autodetect) : Property(string(c),autodetect)
{
}

Property::Property(const string& s, bool autodetect)
{
    if(!autodetect)
    {
        mType = STRING;
        allocateString();
        mString = s;
    }
    else
    {
        mType = determineType(s);
        switch(mType)
        {
            case EMPTY: break;
            case FLOAT: mFloat = atof(s.c_str()); break;
            case INT: mInt = atoi(s.c_str()); break;
            case BOOL: mBool = (s == "True") ? true : false; break;
            case STRING:
            {
                allocateString();
                mString = s;
                break;
            }
            case VEC2: loadVec2(s); break;
            case RECT: loadRect(s); break;
            default: break;
        }
    }
}

Property::Property(const double &d)
{
    mType = FLOAT;
    mFloat = d;
}

Property::Property(const float &f)
{
    mType = FLOAT;
    mFloat = f;
}

Property::Property(const int& i)
{
    mType = INT;
    mInt = i;
}

Property::Property(const bool& b)
{
    mType = BOOL;
    mBool = b;
}

Property::Property(const sf::Vector2f& vec2)
{
    mType  = VEC2;
    mVec2 = vec2;
}

Property::Property(const sf::FloatRect& rect)
{
    mType = RECT;
    mFloatRect = rect;
}

Property::Property(const Property& other)
{
    mType = other.type();
    switch(mType)
    {
        case EMPTY: break;
        case FLOAT: mFloat = other.mFloat; break;
        case INT: mInt = other.mInt; break;
        case BOOL: mBool = other.mBool; break;
        case STRING:
        {
            allocateString();
            mString = other.mString;
            break;
        }
        case VEC2: mVec2 = other.mVec2; break;
        case RECT: mFloatRect = other.mFloatRect; break;
        default: break;
    }
}

Property::Property(const Property&& other)
{
    mType = other.type();
    switch(mType)
    {
        case EMPTY: break;
        case FLOAT: mFloat = other.mFloat; break;
        case INT: mInt = other.mInt; break;
        case BOOL: mBool = other.mBool; break;
        case STRING:
        {
            allocateString();
            mString = std::move(other.mString);
            break;
        }
        case VEC2: mVec2 = other.mVec2; break;
        case RECT: mFloatRect = other.mFloatRect; break;
        default: break;
    }
}

Property& Property::operator=(const Property&& other)
{
    mType = other.type();
    switch(other.type())
    {
        case EMPTY: break;
        case FLOAT: mFloat = other.mFloat; break;
        case INT: mInt = other.mInt; break;
        case BOOL: mBool = other.mBool; break;
        case STRING: mString = std::move(other.mString); break;
        case VEC2: mVec2 = other.mVec2; break;
        case RECT: mFloatRect = other.mFloatRect; break;
        default: break;
    }
    return *this;
}

Property& Property::operator=(const Property& other)
{
    bool needAlloc = !(mType == STRING);
    mType = other.type();
    switch(other.type())
    {
        case EMPTY: break;
        case FLOAT: mFloat = other.mFloat; break;
        case INT: mInt = other.mInt; break;
        case BOOL: mBool = other.mBool; break;
        case STRING:
            if(needAlloc)
                allocateString();
            mString = other.mString; break;
        case VEC2: mVec2 = other.mVec2; break;
        case RECT: mFloatRect = other.mFloatRect; break;
        default: break;
    }
    return *this;
}

Property& Property::operator=(const float & f)
{
    if(mType == FLOAT)
        mFloat = f;
    else if(mType == INT)
        mInt = f;
    else
        throw std::runtime_error("Property type is not float");
    return *this;
}


Property& Property::operator=(const double & d)
{
    if(mType == FLOAT)
        mFloat = d;
    else if(mType == INT)
        mInt = d;
    else
        throw std::runtime_error("Property type is not float");
    return *this;
}

Property& Property::operator=(const int& i)
{
    if(mType == FLOAT)
        mFloat = i;
    else if(mType == INT)
        mInt = i;
    else
        throw std::runtime_error("Property type is not int");
    return *this;
}

Property& Property::operator=(const bool& b)
{
    if(mType == BOOL)
        mBool = b;
    else
        throw std::runtime_error("Property type is not bool");
    return *this;
}

Property& Property::operator=(const std::string& s)
{
    if(mType == STRING)
        mString = s;
    else
        throw std::runtime_error("Property type is not string");
    return *this;
}

Property& Property::operator =(const sf::Vector2f& vec2)
{
    if(mType == VEC2)
        mVec2 = vec2;
    else
        throw std::runtime_error("Property type is not vec2");
    return *this;
}

Property& Property::operator=(const sf::FloatRect& rect)
{
    if(mType == RECT)
        mFloatRect = rect;
    else
        throw std::runtime_error("Property type is not rect");
    return *this;
}

Property& Property::operator=(const sf::IntRect& rect)
{
    if(mType == RECT)
    {
        mFloatRect.top = rect.top;
        mFloatRect.left = rect.left;
        mFloatRect.height = rect.height;
        mFloatRect.width = rect.width;
    }
    else
        throw std::runtime_error("Property type is not rect");
    return *this;
}

float Property::toFloat() const
{
    if(mType == FLOAT)
        return mFloat;
    else if(mType == INT)
        return mInt;
    else
        throw std::runtime_error("Type is not numeric");
}

int Property::toInt() const
{
    if(mType == FLOAT)
        return mFloat;
    else if(mType == INT)
        return mInt;
    else
        throw std::runtime_error("Type is not numeric");
}

const bool& Property::toBool() const
{
    if(mType == BOOL)
        return mBool;
    else
        throw std::runtime_error("Type is not boolean");
}

const sf::Vector2f &Property::toVec2() const
{
    if(mType == VEC2)
        return mVec2;
    else
        throw std::runtime_error("Type is not vec2");
}

const sf::FloatRect& Property::toFRect() const
{
    if(mType == RECT)
        return mFloatRect;
    else
        throw std::runtime_error("Type is not rect");
}

sf::IntRect Property::toIRect() const
{
    if(mType == RECT)
        return sf::IntRect(mFloatRect.left,mFloatRect.top,mFloatRect.width,mFloatRect.height);
    else
        throw std::runtime_error("Type is not rect");
}

const string Property::toString() const
{
    string str;
    switch(mType)
    {
        case FLOAT: return to_string(mFloat);
        case INT: return to_string(mInt);
        case BOOL: str = toString(mBool); break;
        case STRING: return mString;
        case VEC2: str = toString(mVec2); break;
        case RECT: str = toString(mFloatRect); break;
        default: return "";
    }
    return str;
}

const std::string Property::toString(const sf::FloatRect& rect) const
{
    return to_string(rect.left) + ";" + to_string(rect.top) + ";" + to_string(rect.width) + ";" + to_string(rect.height);
}

const std::string Property::toString(const sf::Vector2f& vec2) const
{
    return to_string(vec2.x) + ";" + to_string(vec2.y);
}

void Property::loadRect(const std::string& str)
{
    std::stringstream ss(str);
    std::string item;
    std::getline(ss,item,';');
    mFloatRect.left = atof(item.c_str());
    std::getline(ss,item,';');
    mFloatRect.top = atof(item.c_str());
    std::getline(ss,item,';');
    mFloatRect.width = atof(item.c_str());
    std::getline(ss,item,';');
    mFloatRect.height = atof(item.c_str());
}

void Property::loadVec2(const std::string& str)
{
    std::stringstream ss(str);
    std::string item;
    std::getline(ss,item,';');
    mVec2.x = atof(item.c_str());
    std::getline(ss,item,';');
    mVec2.y = atof(item.c_str());
}

string Property::toString(bool b) const
{
    if(b)
        return "True";
    else
        return "False";
}

Property::~Property()
{
    if(mType == STRING)
        deleteString();
}

const Property::Type& Property::type() const
{
    return mType;
}

Property::Type Property::determineType(const string &value) const
{
    //bool check
    if(value == "True" || value == "False")
        return BOOL;

    const string it("(\\+|-)?[[:digit:]]+");
    const string fl("(("+it+")(\\.(([[:digit:]]+)?))?)");
    const string rect(fl+";"+fl+";"+fl+";"+fl);
    const string v(fl+";"+fl);
    regex floating(fl);
    regex integer(it);
    regex vec2(v);
    regex floatrect(rect);

    if(regex_match(value,floatrect))
        return RECT;
    if(regex_match(value,vec2))
        return VEC2;
    if(regex_match(value,integer))
        return INT;
    if(regex_match(value,floating))
        return FLOAT;

    return STRING; //If nothing is detected. Then it's a string!
}

void Property::allocateString()
{
    new(&mString)(string);
}

void Property::deleteString()
{
    mString.~string();
}

std::ostream& operator<<(std::ostream& os, const Property& prop)
{
    prop.type() == Property::STRING ? os << '"' << prop.toString() << '"' : os << prop.toString();
    return os;
}
