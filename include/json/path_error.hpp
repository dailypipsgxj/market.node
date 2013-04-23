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
        /// A PathError is thrown when you try to access an element by path, e.g. by
        /// calling Value::getObject("foo.bar.baz") and there is some error in accessing
        /// the path: one of the values on the path isn't an object or doesn't
        /// exist. This can also be thrown on Value::insert() or Value::put() calls if
        ///  you specify a path that contains a non-object.
        template<typename StringT>
        struct BasicPathError {
            BasicPathError(
                const StringT& path_,
                const StringT& element_,
                const std::string& reason_ = std::string("") 
            )
            : path(path_), 
              element(element_), 
              reason(reason_)
            {}

            bool operator==(const BasicPathError& rhs) const {
                return (path == rhs.path && element == rhs.element);
                // Ignore the reason since the strings could change -- we really care
                // that the path and element are identical.
            }

            StringT path;
            StringT element;
            std::string reason;
        };
    }
}
