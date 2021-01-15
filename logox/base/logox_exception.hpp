#ifndef LOGOX_EXCEPTION_HPP
#define LOGOX_EXCEPTION_HPP

using namespace std;

#include <exception>
#include <string>

namespace logox{
    class LOGOX_EXCEPTION final : public exception{
    public:
        LOGOX_EXCEPTION() : message("\nLOGOX_ERROR"){}
        LOGOX_EXCEPTION(string str) : message("\nLOGOX : " + str){}
        ~LOGOX_EXCEPTION() throw (){}

        virtual const char* what() const throw (){
            return message.c_str();
        }

    private:
        string message;
    };
} // namespace logox

#endif
