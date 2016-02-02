/*
 * prjsv 2015
 * 2014
 * Marco Antognini
 */

#ifndef INFOSV_JSONIMPL_HPP
#define INFOSV_JSONIMPL_HPP

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace j
{
// Forward declaration
class Value;

namespace impl
{
    class String;
    class Number;
    class Boolean;
    class Object;
    class Array;

    class AbstractValue
    {
    public:
        AbstractValue() = default;
        // Forbid copy
        AbstractValue(AbstractValue const&) = delete;
        AbstractValue& operator=(AbstractValue const&) = delete;

        // Virtual destructor
        virtual ~AbstractValue() = default;

        // Introspection
        virtual bool isString() const;
        virtual bool isNumber() const;
        virtual bool isBoolean() const;
        virtual bool isObject() const;
        virtual bool isArray() const;

        // Human readable type name
        std::string getTypeName() const;

        // Conversion, throws a BadConversion if type mismatch
        virtual String& asString();
        virtual String const& asString() const;
        virtual Number& asNumber();
        virtual Number const& asNumber() const;
        virtual Boolean& asBoolean();
        virtual Boolean const& asBoolean() const;
        virtual Object& asObject();
        virtual Object const& asObject() const;
        virtual Array& asArray();
        virtual Array const& asArray() const;

        // Return a clone of this, the caller is the owner of the pointer
        virtual AbstractValue* clone() const = 0;

    private:
        /**
         *  @brief Fire a BadConversion exception
         *
         *  @param to another type
         *
         *  @return never returns
         */
        [[ noreturn ]]
        void badConversion(std::string const& to) const;
    };

    class String : public AbstractValue
    {
    public:
        String(std::string const& str);

        // Explicit conversion
        std::string toRawString() const;

        // Update the value
        void set(std::string const& str);

        // Implement AbstractValue introspection and conversion functions
        bool isString() const override final;
        String& asString() override final;
        String const& asString() const override final;

        // Cloning
        AbstractValue* clone() const override final;

    private:
        std::string mString;
    };

    class Number : public AbstractValue
    {
    public:
        Number(int integer);
        Number(double real);

        // Explicit convertion
        int toInt() const;
        double toDouble() const;

        // Update the value
        void set(int integer);
        void set(double read);

        // Implement AbstractValue introspection and conversion functions
        bool isNumber() const override final;
        Number& asNumber() override final;
        Number const& asNumber() const override final;

        // Cloning
        AbstractValue* clone() const override final;

    private:
        double mNumber;
    };

    class Boolean : public AbstractValue
    {
    public:
        Boolean(bool b);

        // Explicit conversion to bool
        bool toBool() const;

        // Update the value
        void set(bool b);

        // Implement AbstractValue introspection and conversion functions
        bool isBoolean() const override final;
        Boolean& asBoolean() override final;
        Boolean const& asBoolean() const override final;

        // Cloning
        AbstractValue* clone() const override final;

    private:
        bool mBool;
    };

    class Object : public AbstractValue
    {
    public:
        bool operator==(Object const& other) const;

        // Access the value associated with the given id
        // Throws a NoSuchElement exception if the id doesn't exist
        Value& operator[](std::string const& id);
        Value const& operator[](std::string const& id) const;

        // Introspection
        bool hasValue(std::string const& id) const;

        /**
         *  @brief  Update/insert a value
         *
         *  @param id an identifier for the value
         *  @param v  a value
         *
         *  @return true if there was no such value before the insertion,
         *          false otherwise
         */
        bool set(std::string const& id, Value const& v);

        /**
         *  @brief  Remove the corresponding value from the Object
         *
         *  @throw NoSuchElement when the id is not present in the Object
         *
         *  @param id an id
         */
        void remove(std::string const& id);

        // Return the set of ids present in the object
        std::vector<std::string> keys() const;

        // Implement AbstractValue introspection and conversion functions
        bool isObject() const override final;
        Object& asObject() override final;
        Object const& asObject() const override final;

        // Cloning
        AbstractValue* clone() const override final;

    private:
        std::unordered_map<std::string, std::unique_ptr<Value>> mData;
    };

    class Array : public AbstractValue
    {
    public:
        bool operator==(Array const& other) const;

        // Access the value at the given index
        // Throws a NoSuchElement exception if the index is not in the range of existing elements
        Value& operator[](std::size_t i);
        Value const& operator[](std::size_t i) const;

        // Introspection
        std::size_t size() const;

        // Insert a new value at the end of the array
        void add(Value const& v);

        /**
         *  @brief  Remove the element at the given index
         *
         *  @throw NoSuchElement when the array is empty or the index is to big
         *
         *  @param i an index
         */
        void remove(std::size_t i);

        // Implement AbstractValue introspection and conversion functions
        bool isArray() const override final;
        Array& asArray() override final;
        Array const& asArray() const override final;

        // Cloning
        AbstractValue* clone() const override final;

    private:
        std::vector<std::unique_ptr<Value>> mData;
    };

} // j::impl

} // j

#endif // INFOSV_JSONIMPL_HPP
