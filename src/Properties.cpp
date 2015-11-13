#include "Properties.h"
#include <iostream>
using namespace std;

Properties::Properties()
{
}
//Properties(std::initializer_list<std::pair<std::string,Property>> l);
Properties::Properties(const Properties& other)
{
    mProperties = other.mProperties;
}

Properties::Properties(const Properties&& other)
{
    mProperties = std::move(other.mProperties);
} //Move contructor

Properties::Properties(std::initializer_list<PropertyMapElement> l) : mProperties(l)
{
}

Properties& Properties::operator=(const Properties& other)
{
    mProperties = other.mProperties;
    return *this;
}

Properties& Properties::operator=(const Properties&& other)
{
    mProperties = std::move(other.mProperties);
    return *this;
}

//Move assign
bool Properties::hasKey(const std::string& key) const
{
    return (mProperties.find(key) != mProperties.end());
}

Property& Properties::operator[](const std::string& key)
{
    return mProperties[key];
}

PropertyMap::iterator Properties::begin()
{
    return mProperties.begin();
}

Properties& Properties::add(const Properties& other)
{
    for(const PropertyMapElement p : other)
    {
        add(p.first,p.second);
    }
    return *this;
}

Properties& Properties::add(string name, const Property& prop)
{
    mProperties[name] = prop;
    return *this;
}

PropertyMap::iterator Properties::end()
{
    return mProperties.end();
}

PropertyMap::const_iterator Properties::begin() const
{
    return mProperties.begin();
}

PropertyMap::const_iterator Properties::end() const
{
    return mProperties.end();
}

std::ostream& operator<<(std::ostream& stream, const Properties& props)
{
    stream << props.mProperties.size() << " Properties \n{" << endl;
    for(const PropertyMapElement& p : props.mProperties)
    {
        stream << "    {\"" << p.first << "\", " << p.second << "}" << endl;
    }
    stream << "}" << endl;
    return stream;
}
