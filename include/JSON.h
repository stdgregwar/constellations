/*
 * prjsv 2015
 * 2014
 * Marco Antognini
 */

#ifndef INFOSV_JSON_HPP
#define INFOSV_JSON_HPP

#include "JSONImpl.h"

#include <cstddef>
#include <list>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>

/**
 *  Minimalist and approximative JSON implementation
 *
 *  See http://www.json.org/ for the full requirement. Here we only
 *  support the following values:
 *
 *  String:
 *    Strings are simplified and exclusively rely on std::string.
 *    Therefore there's no support for special value such as \b
 *    or \uxxxx, or even \".
 *
 *  Number:
 *    Again, the implementation relies on the standard tools to parse
 *    numbers; more specifically on std::basic_istream and its >> operators.
 *    The conversion from real to integer is done simply by dropping the
 *    decimal part of the number. No conversion error is reported.
 *    Internally a number is stored as a double. This means that in some
 *    situations some precision is lost.
 *
 *  Boolean:
 *    True and false are supported as described in the official
 *    specificiation, that is all lowercase.
 *
 *  Object:
 *    As described in the official specificiation.
 *
 *  Array:
 *    As described in the official specificiation.
 *
 *  Null:
 *    This value is dropped.
 */

namespace j
{
    class Value;
    typedef std::vector<Value> VArray;

class BadConversion : public std::logic_error
{
public:
    BadConversion(std::string const& from, std::string const& to);
};

class NoSuchElement : public std::logic_error
{
public:
    NoSuchElement(std::string const& elem); // For object access
    NoSuchElement(std::size_t index);       // For array access
};

/**
 *  JSON Value: either a string, a number, a boolean,
 *  an object or an array
 *
 *  To construct a Value, use the factory methods:
 *  string(), number(), boolean(), object() and array()
 */
class Value
{
    typedef std::pair<std::string, Value> NamedValue;
protected:
    static constexpr struct ObjectTag {
    } objectTag{};
    static constexpr struct ArrayTag {
    } arrayTag{};


    Value(ObjectTag);
    Value(ArrayTag);

    // Make factories friends
    friend Value string(std::string const& str);
    friend Value number(int num);
    friend Value number(double num);
    friend Value boolean(bool b);
    friend Value object();
    friend Value array();

    Value() = delete; // This is *not* a valid value

    // Another friend for ease of implementation
    friend bool operator==(Value const& v, Value const& u);

public:
    // Construct
    Value(std::string const& str);
    Value(int num);
    Value(double num);
    Value(bool boolean);
    Value(std::initializer_list<NamedValue> l); //Object cstr
    Value(const VArray& a);
    Value(const char *cstr);

    // Copy / update
    Value(Value const& other);
    Value& operator=(Value const& other);

    // Introspection
    bool isString() const;
    bool isNumber() const;
    bool isBoolean() const;
    bool isObject() const;
    bool isArray() const;

    // Conversion, throws a BadConversion if type mismatches
    std::string toString() const;
    int toInt() const;
    double toDouble() const;
    bool toBool() const;

    //* Object functions *//

    // Throws a BadConversion if the value is not an object

    // Access the value associated with the given id
    // Throw a NoSuchElement exception if the id doesn't exist
    Value& operator[](std::string const& id);
    Value const& operator[](std::string const& id) const;
    bool hasValue(std::string const& id) const;

    // Update/insert a value
    // Return true if there was no such value before the insertion
    bool set(std::string const& id, Value const& v);

    // Remove the corresponding value from the Object
    // Throw NoSuchElement when the id is not present in the Object
    void remove(std::string const& id);

    // Return the set of ids present in the object
    std::vector<std::string> keys() const;

    //* Array functions *//

    // Throws a BadConversion if the value is not an array

    // Access the value at the given index
    // Throw NoSuchElement if the index invalid
    Value& operator[](std::size_t i);
    Value const& operator[](std::size_t i) const;
    std::size_t size() const;

    // Insert a new value at the end of the array
    void add(Value const& v);

    // Remove the element at the given index
    // Throw NoSuchElement when the array is empty or the index is too big
    void remove(std::size_t i);

private:
    std::unique_ptr<impl::AbstractValue> mImpl;
};

// Factory methods
Value string(std::string const& str);
Value number(int num);
Value number(double num);
Value boolean(bool b);
Value object();
Value array();

/**
 *  @brief Get access to a property through several JSON object layers
 *
 *  @param root the base JSON object
 *  @param property property's path
 *
 *  @throw NoSuchElement when the path doesn't lead to a value
 *
 *  @return the corresponding JSON value if it exists
 */
Value& getProperty(Value& root, std::list<std::string> property);

// Comparison operators
bool operator==(Value const& v, Value const& u);
bool operator==(std::string const& v, Value const& u);
bool operator==(Value const& v, std::string const& u);
bool operator==(char const* v, Value const& u);
bool operator==(Value const& v, char const* u);
bool operator==(int v, Value const& u);
bool operator==(Value const& v, int u);
bool operator==(double v, Value const& u);
bool operator==(Value const& v, double u);
bool operator==(bool v, Value const& u);
bool operator==(Value const& v, bool u);

bool operator!=(Value const& v, Value const& u);
bool operator!=(std::string const& v, Value const& u);
bool operator!=(Value const& v, std::string const& u);
bool operator!=(char const* v, Value const& u);
bool operator!=(Value const& v, char const* u);
bool operator!=(int v, Value const& u);
bool operator!=(Value const& v, int u);
bool operator!=(double v, Value const& u);
bool operator!=(Value const& v, double u);
bool operator!=(bool v, Value const& u);
bool operator!=(Value const& v, bool u);

} // j

#endif // INFOSV_JSON_HPP
