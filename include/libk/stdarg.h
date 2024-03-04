/*
MIT License

Copyright (c) 2024 Alexander (@alkuzin)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef _LIBK_STDARG_H_
#define _LIBK_STDARG_H_

#include <libk/stddef.h>

/*
The  va_start()  macro  initializes  ap  for subsequent use by
va_arg() and va_end(), and must be called first.

The argument last is the name of the last argument before  the
variable  argument  list,  that is, the last argument of which
the calling function knows the type.

Because the address of  this  argument  may  be  used  in  the
va_start()  macro,  it  should  not  be declared as a register
variable, or as a function or an array type.*/
#define va_start(ap, last_arg) ((ap) = (char*)&(last_arg) + sizeof(last_arg))

/*
The va_arg() macro expands to an expression that has the  type
and  value  of the next argument in the call.  The argument ap
is the va_list ap initialized by  va_start().   Each  call  to
va_arg()  modifies  ap  so that the next call returns the next
argument.  The argument type is a type name specified so  that
the type of a pointer to an object that has the specified type
can be obtained simply by adding a * to type.

The  first  use  of  the  va_arg()  macro  after  that  of the
va_start() macro returns the argument after last.   Successive
invocations return the values of the remaining arguments.

If  there  is  no  next argument, or if type is not compatible
with the type of the actual next argument (as promoted accord‐
ing to the default argument promotions),  random  errors  will
occur.

If  ap is passed to a function that uses va_arg(ap,type), then
the value of ap is undefined after the return  of  that  func‐
tion.*/
#define va_arg(ap, type) (*(type*)(ap += sizeof(type)))

/*
Each invocation of va_start() must be matched by a correspond‐
ing  invocation  of  va_end() in the same function.  After the
call va_end(ap) the variable ap is undefined.   Multiple  tra‐
versals of the list, each bracketed by va_start() and va_end()
are possible.  va_end() may be a macro or a function.
*/
#define va_end(ap) (ap = NULL)

typedef char* va_list;

#endif /* _LIBK_STDARG_H_ */
