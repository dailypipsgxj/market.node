// Copyright John W. Wilkinson 2007 - 2011
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

#include "json/platform.hpp"
#include "json/value.hpp"
#include "json/parse_error.hpp"
#include <iostream>

namespace market {
    namespace json_spirit {
        // functions to read JSON values

        #ifdef JSON_SPIRIT_VALUE_ENABLED
        bool JSON_SPIRIT_FUNCTION_EXPORT read(const std::string& s, Value& value);
        bool JSON_SPIRIT_FUNCTION_EXPORT read(std::istream& is, Value& value);
        bool JSON_SPIRIT_FUNCTION_EXPORT read(std::string::const_iterator& begin, std::string::const_iterator end, Value& value);

        void JSON_SPIRIT_FUNCTION_EXPORT read_or_throw(const std::string& s, Value& value);
        void JSON_SPIRIT_FUNCTION_EXPORT read_or_throw(std::istream& is, Value& value);
        void JSON_SPIRIT_FUNCTION_EXPORT read_or_throw(std::string::const_iterator& begin, std::string::const_iterator end, Value& value);
        #endif

        #if defined( JSON_SPIRIT_WVALUE_ENABLED ) && !defined( BOOST_NO_STD_WSTRING )
        bool JSON_SPIRIT_FUNCTION_EXPORT read(const std::wstring& s, wValue& value);
        bool JSON_SPIRIT_FUNCTION_EXPORT read(std::wistream& is, wValue& value);
        bool JSON_SPIRIT_FUNCTION_EXPORT read(std::wstring::const_iterator& begin, std::wstring::const_iterator end, wValue& value);

        void JSON_SPIRIT_FUNCTION_EXPORT read_or_throw(const std::wstring& s, wValue& value);
        void JSON_SPIRIT_FUNCTION_EXPORT read_or_throw(std::wistream& is, wValue& value);
        void JSON_SPIRIT_FUNCTION_EXPORT read_or_throw(std::wstring::const_iterator& begin, std::wstring::const_iterator end, wValue& value);
        #endif
    }
}
