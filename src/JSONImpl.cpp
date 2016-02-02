/*
 * prjsv 2015
 * 2014
 * Marco Antognini
 */

#include "JSON.h"
#include "JSONImpl.h"

#include <cassert>

namespace j
{

namespace impl
{

    bool AbstractValue::isString() const
    {
        return false;
    }

    bool AbstractValue::isNumber() const
    {
        return false;
    }

    bool AbstractValue::isBoolean() const
    {
        return false;
    }

    bool AbstractValue::isObject() const
    {
        return false;
    }

    bool AbstractValue::isArray() const
    {
        return false;
    }

    std::string AbstractValue::getTypeName() const
    {
        if (isString())
            return "String";
        else if (isNumber())
            return "Number";
        else if (isBoolean())
            return "Boolean";
        else if (isObject())
            return "Object";
        else if (isArray())
            return "Array";
        else
            assert(false);
    }

    String& AbstractValue::asString()
    {
        badConversion("String");
    }

    String const& AbstractValue::asString() const
    {
        badConversion("String");
    }

    Number& AbstractValue::asNumber()
    {
        badConversion("Number");
    }

    Number const& AbstractValue::asNumber() const
    {
        badConversion("Number");
    }

    Boolean& AbstractValue::asBoolean()
    {
        badConversion("Boolean");
    }

    Boolean const& AbstractValue::asBoolean() const
    {
        badConversion("Boolean");
    }

    Object& AbstractValue::asObject()
    {
        badConversion("Object");
    }

    Object const& AbstractValue::asObject() const
    {
        badConversion("Object");
    }

    Array& AbstractValue::asArray()
    {
        badConversion("Array");
    }

    Array const& AbstractValue::asArray() const
    {
        badConversion("Array");
    }

    void AbstractValue::badConversion(std::string const& to) const
    {
        throw BadConversion(getTypeName(), to);
    }

    String::String(std::string const& str)
    : mString(str)
    {
    }

    std::string String::toRawString() const
    {
        return mString;
    }

    void String::set(std::string const& str)
    {
        mString = str;
    }

    bool String::isString() const
    {
        return true;
    }

    String& String::asString()
    {
        return *this;
    }

    String const& String::asString() const
    {
        return *this;
    }

    AbstractValue* String::clone() const
    {
        return new String(mString);
    }

    Number::Number(int integer)
    : mNumber(integer)
    {
    }

    Number::Number(double real)
    : mNumber(real)
    {
    }

    int Number::toInt() const
    {
        return static_cast<int>(mNumber);
    }

    double Number::toDouble() const
    {
        return mNumber;
    }

    bool Number::isNumber() const
    {
        return true;
    }

    Number& Number::asNumber()
    {
        return *this;
    }

    Number const& Number::asNumber() const
    {
        return *this;
    }

    AbstractValue* Number::clone() const
    {
        return new Number(mNumber);
    }

    Boolean::Boolean(bool b)
    : mBool(b)
    {
    }

    bool Boolean::toBool() const
    {
        return mBool;
    }

    bool Boolean::isBoolean() const
    {
        return true;
    }

    Boolean& Boolean::asBoolean()
    {
        return *this;
    }

    Boolean const& Boolean::asBoolean() const
    {
        return *this;
    }

    AbstractValue* Boolean::clone() const
    {
        return new Boolean(mBool);
    }

    bool Object::operator==(Object const& other) const
    {
        if (mData.size() != other.mData.size()) {
            return false;
        }

        for (auto const& p : mData) {
            // If p.first is present in other and the associated
            // value correspond to p.second then we continue
            // searching for a difference.

            auto it = other.mData.find(p.first);
            if (it == other.mData.end() || *it->second != *p.second) {
                return false;
            }
        }

        // No difference found
        return true;
    }

    Value& Object::operator[](std::string const& id)
    {
        auto it = mData.find(id);
        if (it == mData.end()) {
            throw NoSuchElement(id);
        } else {
            return *it->second;
        }
    }

    Value const& Object::operator[](std::string const& id) const
    {
        auto it = mData.find(id);
        if (it == mData.end()) {
            throw NoSuchElement(id);
        } else {
            return *it->second;
        }
    }

    bool Object::hasValue(std::string const& id) const
    {
        return mData.find(id) != mData.end();
    }

    bool Object::set(std::string const& id, Value const& v)
    {
        auto it = mData.find(id);
        if (it == mData.end()) {
            mData[id].reset(new Value(v));
            return true;
        } else {
            *mData[id] = v;
            return false;
        }
    }

    void Object::remove(std::string const& id)
    {
        auto it = mData.find(id);
        if (it == mData.end()) {
            throw NoSuchElement(id);
        } else {
            mData.erase(it);
        }
    }

    std::vector<std::string> Object::keys() const
    {
        std::vector<std::string> keys;
        keys.reserve(mData.size());

        for (auto const& p : mData) {
            keys.push_back(p.first);
        }

        return keys;
    }

    bool Object::isObject() const
    {
        return true;
    }

    Object& Object::asObject()
    {
        return *this;
    }

    Object const& Object::asObject() const
    {
        return *this;
    }

    AbstractValue* Object::clone() const
    {
        auto ptr = new Object();
        for (auto const& id : keys()) {
            ptr->set(id, (*this)[id]);
        }
        return ptr;
    }

    bool Array::operator==(Array const& other) const
    {
        if (size() != other.size()) {
            return false;
        }

        for (std::size_t i = 0; i < size(); ++i) {
            // Check if the value at the same index is equivalent or not
            if ((*this)[i] != other[i]) {
                return false;
            }
        }

        // No difference found
        return true;
    }

    Value& Array::operator[](std::size_t i)
    {
        if (i >= size()) {
            throw NoSuchElement(i);
        } else {
            return *mData[i];
        }
    }

    Value const& Array::operator[](std::size_t i) const
    {
        if (i >= size()) {
            throw NoSuchElement(i);
        } else {
            return *mData[i];
        }
    }

    std::size_t Array::size() const
    {
        return mData.size();
    }

    void Array::add(Value const& v)
    {
        mData.emplace_back(new Value(v));
    }

    void Array::remove(std::size_t i)
    {
        if (i >= size()) {
            throw NoSuchElement(0);
        } else {
            mData.erase(mData.begin() + i);
        }
    }

    bool Array::isArray() const
    {
        return true;
    }

    Array& Array::asArray()
    {
        return *this;
    }

    Array const& Array::asArray() const
    {
        return *this;
    }

    AbstractValue* Array::clone() const
    {
        auto ptr = new Array();
        ptr->mData.reserve(size());
        for (std::size_t i = 0; i < size(); ++i) {
            ptr->add((*this)[i]);
        }
        return ptr;
    }

} // j::impl

} // j
