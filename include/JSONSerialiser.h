/*
 * prjsv 2015
 * 2014
 * Marco Antognini
 */

#ifndef INFOSV_JSONSERIALISER_HPP
#define INFOSV_JSONSERIALISER_HPP

#include "JSON.h"

#include <stdexcept>
#include <string>

namespace j
{

class BadPayload : std::runtime_error
{
public:
    BadPayload(std::string const& msg);
};

// Read a JSON value from a payload string
// Throw a BadPayload when the format is invalid
Value readFromString(std::string const& payload);

// Like `readFromString` but the payload is read from the given file
Value readFromFile(std::string const& fileapath);

// Convert a JSON value to the corresponding payload string
std::string writeToString(Value const& value);

// Like `writeToString` but write it to the given file
void writeToFile(Value const& value, std::string const& fileapath);

} // j

#endif // INFOSV_JSONSERIALISER_HPP
