#include "qh_string.h"

#include <string.h>

namespace qh
{
    // TODO ½«ÔÚÕâÀïÐ´ÊµÏÖ´úÂë

    string::string()
        : data_(NULL), len_(0)
    {
    }

    string::string( const char* s )
    {
        if(s == NULL)
            return;

        len_ = strlen(s);
        data_ = new char[len_+1];
        strcpy(data_, s);
    }

    string::string( const char* s, size_t len )
    {
        len_ = len;
        data_ = new char[len_+1];
        strcpy(data_, s);
    }

    string::string( const string& rhs )
    {
        len_ = rhs.len;
        data_ = new char[len_+1];
        strcpy(data_, rhs.data_);
    }

    string& string::operator=( const string& rhs )
    {
        if(this != &rhs)
        {
            if(len_<rhs.len_)
            {
                delete[] data_;
                data_ = new char[rhs.len_+1];
            }

            len_ = rhs.len_;
            strcpy(data_, rhs.data_);
        }
        return *this;
    }

    string::~string()
    {
        delete[] data_;
    }

    size_t string::size() const
    {
        return len_;
    }

    const char* string::data() const
    {
        return data_;
    }

    const char* string::c_str() const
    {
        return data_;
    }

    char* string::operator[]( size_t index )
    {
        assert(index>=0 && index <= len_);
        return data_[index];
    }
}
