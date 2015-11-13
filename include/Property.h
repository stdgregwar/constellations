#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>
#include <map>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

class Property
{
    //struct Bool{bool value;};
    public:
        enum Type
        {
            EMPTY,
            FLOAT,
            INT,
            BOOL,
            STRING,
            VEC2,
            RECT
        };

        Property(Type t = EMPTY);
        Property(const std::string& str, bool autodetect = false);
        Property(const char* c, bool autodetect = false);
        Property(const float& f);
        Property(const double& d);
        Property(const int& i);
        Property(const bool& b);
        Property(const sf::Vector2f& vec2);
        Property(const sf::FloatRect& rect);
        Property(const sf::IntRect& rect);
        Property(const Property& other);

        Property(const Property&& other);
        Property& operator=(const Property&& other);

        Property& operator=(const Property& other);
        Property& operator=(const float & f);
        Property& operator=(const double & d);
        Property& operator=(const int& i);
        Property& operator=(const bool& b);
        Property& operator=(const std::string& s);
        Property& operator =(const sf::Vector2f& vec2);
        Property& operator=(const sf::FloatRect& rect);
        Property& operator=(const sf::IntRect& rect);
        float toFloat() const;
        int toInt() const;
        const bool& toBool() const;
        const sf::Vector2f& toVec2() const;
        const sf::FloatRect& toFRect() const;
        sf::IntRect toIRect() const;
        const std::string toString() const;
        const Type& type() const;
        Type determineType(const std::string & value) const;
        virtual ~Property();
        friend std::ostream& operator<<(std::ostream& os, const Property& prop);
    private:
        const std::string toString(const sf::FloatRect& rect) const;
        const std::string toString(const sf::Vector2f& vec2) const;
        void loadRect(const std::string& str);
        void loadVec2(const std::string& str);
        std::string toString(bool b) const;

        void allocateString();
        void deleteString();


        union{
            float mFloat;
            int mInt;
            bool mBool;
            sf::Vector2f mVec2;
            sf::FloatRect mFloatRect;
            std::string mString;
        };
        Type mType;
};

std::ostream& operator<<(std::ostream& os, const Property& prop);

#endif // PROPERTY_H
