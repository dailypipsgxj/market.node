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

namespace market { 
    namespace json {
        enum Output_options { 
            pretty_print = 0x01,  // Add whitespace to format the output nicely.
            raw_utf8 = 0x02,      // This prevents non-printable characters from being escapted using "\uNNNN" notation.
                                  // Note, this is an extension to the JSON standard. It disables the escaping of
                                  // non-printable characters allowing UTF-8 sequences held in 8 bit char strings
                                  // to pass through unaltered.
            remove_trailing_zeros = 0x04, 
                                  // outputs e.g. "1.200000000000000" as "1.2"
            single_line_arrays = 0x08
                                  // pretty printing except that arrays printed on single lines unless they contain
                                  // composite elements, i.e. objects or arrays
        };
    }
}
