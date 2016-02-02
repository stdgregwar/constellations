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

BadConversion::BadConversion(std::string const& from, std::string const& to)
: std::logic_error("Cannot convert JSON value " + from + " to " + to)
{
}

NoSuchElement::NoSuchElement(std::string const& elem)
: std::logic_error("No such element with id " + elem + " in JSON object")
{
}

NoSuchElement::NoSuchElement(std::size_t index)
: std::logic_error("No such index " + std::to_string(index) + " in JSON array")
{
}

Value::Value(std::string const& str)
: mImpl(new impl::String(str))
{
}

Value::Value(std::initializer_list<NamedValue> l)
    : mImpl(new impl::Object())
{
    for(auto& p : l)
    {
        set(p.first,p.second);
    }
}

Value::Value(const VArray& a)
    : mImpl(new impl::Array)
{
   for(auto& val : a)
   {
       add(val);
   }
}

Value::Value(const char * cstr) : Value(std::string(cstr))
{
}

Value::Value(int num)
: mImpl(new impl::Number(num))
{
}

Value::Value(double num)
: mImpl(new impl::Number(num))
{
}

Value::Value(bool b)
: mImpl(new impl::Boolean(b))
{
}

Value::Value(ObjectTag)
: mImpl(new impl::Object())
{
}

Value::Value(ArrayTag)
: mImpl(new impl::Array())
{
}

Value::Value(Value const& other)
: mImpl(other.mImpl->clone())
{
}

Value& Value::operator=(Value const& other)
{
    mImpl.reset(other.mImpl->clone());
    return *this;
}

bool Value::isString() const
{
    return mImpl->isString();
}

bool Value::isNumber() const
{
    return mImpl->isNumber();
}

bool Value::isBoolean() const
{
    return mImpl->isBoolean();
}

bool Value::isObject() const
{
    return mImpl->isObject();
}

bool Value::isArray() const
{
    return mImpl->isArray();
}

std::string Value::toString() const
{
    return mImpl->asString().toRawString();
}

int Value::toInt() const
{
    return mImpl->asNumber().toInt();
}

double Value::toDouble() const
{
    return mImpl->asNumber().toDouble();
}

bool Value::toBool() const
{
    return mImpl->asBoolean().toBool();
}

Value& Value::operator[](std::string const& id)
{
    return mImpl->asObject()[id];
}

Value const& Value::operator[](std::string const& id) const
{
    return mImpl->asObject()[id];
}

bool Value::hasValue(std::string const& id) const
{
    return mImpl->asObject().hasValue(id);
}

bool Value::set(std::string const& id, Value const& v)
{
    return mImpl->asObject().set(id, v);
}

void Value::remove(std::string const& id)
{
    mImpl->asObject().remove(id);
}

std::vector<std::string> Value::keys() const
{
    return mImpl->asObject().keys();
}

Value& Value::operator[](std::size_t i)
{
    return mImpl->asArray()[i];
}

Value const& Value::operator[](std::size_t i) const
{
    return mImpl->asArray()[i];
}

std::size_t Value::size() const
{
    return mImpl->asArray().size();
}

void Value::add(Value const& v)
{
    mImpl->asArray().add(v);
}

void Value::remove(std::size_t i)
{
    mImpl->asArray().remove(i);
}

Value string(std::string const& str)
{
    return { str };
}

Value number(int num)
{
    return { num };
}

Value number(double num)
{
    return { num };
}

Value boolean(bool b)
{
    return { b };
}

Value object()
{
    return { Value::objectTag };
}

Value array()
{
    return { Value::arrayTag };
}

Value& getProperty(Value& root, std::list<std::string> property)
{
    if (property.empty()) {
        return root;
    } else {
        auto const& head = property.front();
        property.pop_front();
        auto& nextRoot = root[head];
        return getProperty(nextRoot, property);
    }
}

bool operator==(Value const& v, Value const& u)
{
    if (u.isString() && v.isString()) {
        return u.toString() == v.toString();
    } else if (u.isNumber() && v.isNumber()) {
        return u.toDouble() == v.toDouble();
    } else if (u.isBoolean() && v.isBoolean()) {
        return u.toBool() == v.toBool();
    } else if (u.isObject() && v.isObject()) {
        return u.mImpl->asObject() == v.mImpl->asObject();
    } else if (u.isArray() && v.isArray()) {
        return u.mImpl->asArray() == v.mImpl->asArray();
    } else {
        return false;
    }
}

bool operator==(std::string const& v, Value const& u)
{
    return u.isString() && u.toString() == v;
}

bool operator==(Value const& v, std::string const& u)
{
    return u == v;
}

bool operator==(char const* v, Value const& u)
{
    return std::string(v) == u;
}

bool operator==(Value const& v, char const* u)
{
    return u == v;
}

bool operator==(int v, Value const& u)
{
    return static_cast<double>(v) == u;
}

bool operator==(Value const& v, int u)
{
    return static_cast<double>(u) == v;
}

bool operator==(double v, Value const& u)
{
    return u.isNumber() && u.toDouble() == v;
}

bool operator==(Value const& v, double u)
{
    return u == v;
}

bool operator==(bool v, Value const& u)
{
    return u.isBoolean() && u.toBool() == v;
}

bool operator==(Value const& v, bool u)
{
    return u == v;
}

bool operator!=(Value const& v, Value const& u)
{
    return !(v == u);
}

bool operator!=(std::string const& v, Value const& u)
{
    return !(v == u);
}

bool operator!=(Value const& v, std::string const& u)
{
    return !(u == v);
}

bool operator!=(char const* v, Value const& u)
{
    return !(v == u);
}

bool operator!=(Value const& v, char const* u)
{
    return !(u == v);
}

bool operator!=(int v, Value const& u)
{
    return !(v == u);
}

bool operator!=(Value const& v, int u)
{
    return !(u == v);
}

bool operator!=(double v, Value const& u)
{
    return !(v == u);
}

bool operator!=(Value const& v, double u)
{
    return !(u == v);
}

bool operator!=(bool v, Value const& u)
{
    return !(v == u);
}

bool operator!=(Value const& v, bool u)
{
    return !(u == v);
}


} // j
