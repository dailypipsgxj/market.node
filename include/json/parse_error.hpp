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

#include <string>
#include "platform.h"

namespace market { 
    namespace json {
        // An ParseError exception is thrown by the "read_or_throw" functions below on finding an error.
        // Note the "read_or_throw" functions are around 3 times slower than the standard functions "read"
        // functions that return a bool.
        struct JSON_SPIRIT_EXPORT ParseError {
            ParseError();
            ParseError( unsigned int line, unsigned int column, const std::string& reason );
            bool operator==( const ParseError& lhs ) const;
            unsigned int line_;
            unsigned int column_;
            std::string reason_;
        };

        inline ParseError::ParseError() : line_( 0 ), column_( 0 ) {}

        inline ParseError::ParseError(
            unsigned int line,
            unsigned int column,
            const std::string& reason
        )
        : line_( line ), 
          column_( column ),
          reason_( reason )
        {}

        inline bool ParseError::operator==( const ParseError& lhs ) const {
            if( this == &lhs ) return true;

            return ( reason_ == lhs.reason_ ) && ( line_   == lhs.line_ ) && ( column_ == lhs.column_ );
        }
    }
}
