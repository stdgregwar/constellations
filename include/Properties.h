#ifndef PROPERTIES_H
#define PROPERTIES_H

#include "Property.h"
#include <ostream>

typedef std::pair<const std::string,Property> PropertyMapElement;
typedef std::map<std::string,Property> PropertyMap;

class Properties
{
public:
    Properties();
    Properties(std::initializer_list<PropertyMapElement> l);
    Properties(const Properties& other);
    Properties(const Properties&& other); //Move contructor
    Properties& operator=(const Properties& other);
    Properties& operator=(const Properties&& other); //Move assign
    bool hasKey(const std::string& key) const;
    Properties& add(const Properties& other);
    Properties& add(std::string name,const Property& prop);
    Property& operator[](const std::string& key);
    PropertyMap::iterator begin();
    PropertyMap::iterator end();
    PropertyMap::const_iterator begin() const;
    PropertyMap::const_iterator end() const;
    friend std::ostream& operator<<(std::ostream& os, const Properties& dt);
private:
    std::map<std::string,Property> mProperties;
};

std::ostream& operator<<(std::ostream& os, const Properties& props);

#endif // PROPERTIES_H
