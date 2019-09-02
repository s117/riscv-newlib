/* Copyright (c) 2019  SiFive Inc. All rights reserved.

   This copyrighted material is made available to anyone wishing to use,
   modify, copy, or redistribute it subject to the terms and conditions
   of the FreeBSD License.   This program is distributed in the hope that
   it will be useful, but WITHOUT ANY WARRANTY expressed or implied,
   including the implied warranties of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  A copy of this license is available at
   http://www.opensource.org/licenses.
*/

#if defined(__riscv_flen) && __riscv_flen >= 32
#include <math.h>

float
fmaf (float x, float y, float z)
{
  float result;
  asm ("fmadd.s\t%0, %1, %2, %3" :
       "=f" (result) : "f" (x), "f" (y), "f" (z));
  return result;
}

#else
#include "../../common/sf_fma.c"
#endif
