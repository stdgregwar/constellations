#ifndef CEXCEPTIONS
#define CEXCEPTIONS

#include <exception>

enum EType{
    UNKNOWN,
    WARNING,
    FATAL
};

const std::map<EType,std::string> ETypeNames{
    {UNKNOWN,"UNKNOWN"},
    {WARNING,"WARNING"},
    {FATAL,"FATAL"}
};

class CException : public std::exception
{
public:

    CException(EType type, std::string what) : mType(type), mWhat(what){}
    const char* what() const throw(){return mWhat.c_str();}
    EType type() const throw(){return mType;}
private:
    EType mType;
    std::string mWhat;
};

#endif // EXCEPTIONS

