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

#define JSON_SPIRIT_PLATFORM_WINDOWS 0
#define JSON_SPIRIT_PLATFORM_LINUX   1
#define JSON_SPIRIT_PLATFORM_MAC     2

#if defined(__WIN32__) || defined(_WIN32)
#  define JSON_SPIRIT_PLATFORM JSON_SPIRIT_PLATFORM_WINDOWS
#elif defined(__APPLE_CC__) || defined(__APPLE__)
#  define JSON_SPIRIT_PLATFORM JSON_SPIRIT_PLATFORM_MAC
#  ifndef __MACOSX__
#    define __MACOSX__
#  endif
#else
#  define JSON_SPIRIT_PLATFORM JSON_SPIRIT_PLATFORM_LINUX
#endif

#ifdef JSON_SPIRIT_DEBUG_BUILD
#define JSON_SPIRIT_DEBUG 1
#else
#define JSON_SPIRIT_DEBUG 0
#endif

#ifndef JSON_SPIRIT_EXPORT
# if JSON_SPIRIT_PLATFORM == JSON_SPIRIT_PLATFORM_WINDOWS
#   if defined(JSON_SPIRIT_STATIC_LINKED)
#     define JSON_SPIRIT_EXPORT
#   else
#     if defined(JSON_SPIRIT_LIBRARY_BUILD)
#       define JSON_SPIRIT_EXPORT __declspec(dllexport)
#       define JSON_SPIRIT_EXPORT_TEMPLATE
#     else
#       define JSON_SPIRIT_EXPORT __declspec(dllimport)
#       define JSON_SPIRIT_EXPORT_TEMPLATE extern
#     endif
#   endif
#   define JSON_SPIRIT_PLUGIN_EXPORT __declspec(dllexport)
# else
#   if defined(__GNUC__) && __GNUC__ >= 4
#     define JSON_SPIRIT_EXPORT __attribute__ ((visibility("default")))
#     define JSON_SPIRIT_PLUGIN_EXPORT __attribute__ ((visibility("default")))
#   else
#     define JSON_SPIRIT_EXPORT
#     define JSON_SPIRIT_PLUGIN_EXPORT
#   endif
#   define JSON_SPIRIT_EXPORT_TEMPLATE
# endif
#endif


#ifndef JSON_SPIRIT_FUNCTION_EXPORT
# if JSON_SPIRIT_PLATFORM == JSON_SPIRIT_PLATFORM_WINDOWS
#   if defined(JSON_SPIRIT_STATIC_LINKED)
#     define JSON_SPIRIT_FUNCTION_EXPORT
#   else
#     if defined(JSON_SPIRIT_LIBRARY_BUILD)
#       define JSON_SPIRIT_FUNCTION_EXPORT __declspec(dllexport)
#     else
#       define JSON_SPIRIT_FUNCTION_EXPORT __declspec(dllimport)
#     endif
#   endif
# else
#   if defined(__GNUC__) && __GNUC__ >= 4
#     define JSON_SPIRIT_FUNCTION_EXPORT __attribute__ ((visibility("default")))
#   else
#     define JSON_SPIRIT_FUNCTION_EXPORT
#   endif
# endif
#endif
