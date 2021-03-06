/*
  CELP voice codec, part of the HawkVoice Direct Interface (HVDI)
  cross platform network voice library
  Copyright (C) 2001-2003 Phil Frisbie, Jr. (phil@hawksoft.com)

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Library General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.
  
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Library General Public License for more details.
    
  You should have received a copy of the GNU Library General Public
  License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place - Suite 330,
  Boston, MA  02111-1307, USA.
      
  Or go to http://www.gnu.org/copyleft/lgpl.html
*/

#include "celpint.h"

#ifdef _MSC_VER
#pragma warning (disable:4305) /* to disable const double to float warning */
#endif

/* Extracts of code to do LSP root finding from predictor coefficients, and
   to convert back from roots to predictor coefficients.  */

static float lsp[MAXNO][16] =
{
  {0.01250000,   0.02125000,   0.02812500,   0.03125000,
   0.03500000,   0.04250000,   0.05250000,   0.06250000},
  {0.02625000,   0.02937500,   0.03312500,   0.03687500,
   0.04062500,   0.04500000,   0.05000000,   0.05500000,
   0.06000000,   0.06500000,   0.07000000,   0.07625000,
   0.08375000,   0.09250000,   0.10125000,   0.11000000},
  {0.05250000,   0.05750000,   0.06250000,   0.06750000,
   0.07312500,   0.08000000,   0.08812500,   0.09687500,
   0.10625000,   0.11875000,   0.13125000,   0.14375000,
   0.15625000,   0.16875000,   0.18125000,   0.19375000},
  {0.07750000,   0.08250000,   0.09000000,   0.09937500,
   0.11000000,   0.12125000,   0.13500000,   0.14625000,
   0.15875000,   0.17125000,   0.18375000,   0.19625000,
   0.20875000,   0.22125000,   0.23375000,   0.24625000},
  {0.12500000,   0.13125000,   0.14125000,   0.15125000,
   0.16062500,   0.16875000,   0.17875000,   0.18875000,
   0.19875000,   0.20875000,   0.21875000,   0.23125000,
   0.24375000,   0.25625000,   0.26875000,   0.28125000},
  {0.18375000,   0.19625000,   0.21125000,   0.22875000,
   0.25000000,   0.27500000,   0.30000000,   0.32500000},
  {0.22500000,   0.23500000,   0.24500000,   0.26250000,
   0.28750000,   0.31000000,   0.33750000,   0.36250000},
  {0.27812500,   0.30000000,   0.31562500,   0.33125000,
   0.35000000,   0.36875000,   0.39375000,   0.41875000},
  {0.34500000,   0.36000000,   0.37500000,   0.38750000,
   0.40000000,   0.41375000,   0.42875000,   0.44375000},
  {0.39875000,   0.40875000,   0.41875000,   0.42750000,
   0.43625000,   0.44875000,   0.46375000,   0.47875000}
};

static float table[MAXNO][17] =
{
  { 0.99691746,    0.99110012,    0.98442723,    0.98078609,
    0.97591778,    0.96455891,    0.94608763,    0.92388272,
   -2.00000000,   -2.00000000,   -2.00000000,   -2.00000000,
   -2.00000000,   -2.00000000,   -2.00000000,   -2.00000000,   -2.0},
  { 0.98642983,    0.98301624,    0.97841983,    0.97328029,
    0.96760046,    0.96029536,    0.95105858,    0.94088325,
    0.92977943,    0.91775807,    0.90483103,    0.88741813,
    0.86471905,    0.83581413,    0.80438365,    0.77052259,   -2.0},
  { 0.94608763,    0.93544674,    0.92388272,    0.91140698,
    0.89629734,    0.87631182,    0.85058793,    0.82040883,
    0.78532570,    0.73433325,    0.67881359,    0.61910900,
    0.55558755,    0.48864087,    0.41868168,    0.34614129,   -2.0},
  { 0.88377046,    0.86863696,    0.84433435,    0.81132672,
    0.77052259,    0.72358094,    0.66132536,    0.60669785,
    0.54245932,    0.47487648,    0.40436600,    0.33136257,
    0.25631627,    0.17968976,    0.10195545,    0.02359258,   -2.0},
  { 0.70711856,    0.67881359,    0.63136740,    0.58142959,
    0.53252513,    0.48864087,    0.43289406,    0.37543889,
    0.31650210,    0.25631627,    0.19511892,    0.11756801,
    0.03929228,   -0.03922568,   -0.11750182,   -0.19505355,   -2.0},
  { 0.40436600,    0.33136257,    0.24110239,    0.13315156,
    0.00003333,   -0.15639826,   -0.30897896,   -0.45395190,
   -2.00000000,   -2.00000000,   -2.00000000,   -2.00000000,
   -2.00000000,   -2.00000000,   -2.00000000,   -2.00000000,   -2.0},
  { 0.15646409,    0.09413950,    0.03144340,   -0.07842421,
   -0.23340810,   -0.36808613,   -0.52246020,   -0.64941130,
   -2.00000000,   -2.00000000,   -2.00000000,   -2.00000000,
   -2.00000000,   -2.00000000,   -2.00000000,   -2.00000000,   -2.0},
  {-0.17575978,   -0.30897896,   -0.40071028,   -0.48858271,
   -0.58774750,   -0.67876465,   -0.78528443,   -0.87246873,
   -2.00000000,   -2.00000000,   -2.00000000,   -2.00000000,
   -2.00000000,   -2.00000000,   -2.00000000,   -2.00000000,   -2.0},
  {-0.56204534,   -0.63738701,   -0.70707143,   -0.76037242,
   -0.80898565,   -0.85668907,   -0.90143037,   -0.93817086,
   -2.00000000,   -2.00000000,   -2.00000000,   -2.00000000,
   -2.00000000,   -2.00000000,   -2.00000000,   -2.00000000,   -2.0},
  {-0.80434405,   -0.84006400,   -0.87246873,   -0.89800250,
   -0.92082280,   -0.94858126,   -0.97415943,   -0.99109125,
   -2.00000000,   -2.00000000,   -2.00000000,   -2.00000000,
   -2.00000000,   -2.00000000,   -2.00000000,   -2.00000000,   -2.0}
};

void pctolsp3(float *a, float *freq, int *sbits, int *findex)
{
  register int index;
  int *f, *s;
  float prev1, prev2;
  float *r, *x3, *x4, temp, temp0, temp1, temp2;
  float q[6], p[6];
  q[1] = a[1] + a[10] - 1.0f;
  q[2] = a[2] + a[9] - q[1];
  q[3] = a[3] + a[8] - q[2];
  q[4] = a[4] + a[7] - q[3];
  q[5] = a[5] + a[6] - q[4];
  q[5] /= 2.0f;
  p[1] = a[1] - a[10] + 1.0f;
  p[2] = a[2] - a[9] + p[1];
  p[3] = a[3] - a[8] + p[2];
  p[4] = a[4] - a[7] + p[3];
  p[5] = a[5] - a[6] + p[4];
  p[5] /= 2.0;
  prev1 = 9e9;
  prev2 = 9e9;
  x3 = (&table[0][0]);
  x4 = (&lsp[0][0]);
  r = (&freq[0]);
  s = (&sbits[0]);
  f = (&findex[0]);
  index = 0;
  for (;;)
  {
    for (;;)
    {
      /* evaluate sum polynomial (5 adds, 4 subs, 4 muls) */
      temp = (x3[index]);
      temp1 = 2.0f*temp               + q[1];
      temp2 = 2.0f*temp*temp1 - 1.0f   + q[2];
      temp0 = 2.0f*temp*temp2 - temp1 + q[3];
      temp1 = 2.0f*temp*temp0 - temp2 + q[4];
      temp2 =     temp*temp1 - temp0 + q[5];
      /* look for sign change */
      if ((temp2*prev1) < 0.0f || index+1 == 1<<*s)
      {
        if (fabs(temp2) < fabs(prev1))
          (*r++) = (x4[index]);
        else
          (*r++) = (x4[--index]);
        if (prev1 < 0.0f)
          prev1 = 9e9f;
        else
          prev1 = (-9e9f);
        *f++ = index;
        if (r < (&freq[10]))
        {
          x3 += 17;
          x4 += 16;
          s++;
          index = 0;
          while (x4[index] < *(r-1)) index++;
          break;
        }
        else
          return;
      }
      prev1 = temp2;
      index++;
    }
    for (;;)
    {
      /* evaluate sum polynomial (5 adds, 4 subs, 4 muls) */
      temp = (x3[index]);
      temp1 = 2.0f*temp               + p[1];
      temp2 = 2.0f*temp*temp1 - 1.0f   + p[2];
      temp0 = 2.0f*temp*temp2 - temp1 + p[3];
      temp1 = 2.0f*temp*temp0 - temp2 + p[4];
      temp2 =     temp*temp1 - temp0 + p[5];
      /* look for sign change */
      if ((temp2*prev2) < 0.0f || index+1 == 1<<*s)
      {
        if (fabs(temp2) < fabs(prev2))
          (*r++) = (x4[index]);
        else
          (*r++) = (x4[--index]);
        if (prev2 < 0.0f)
          prev2 = 9e9f;
        else
          prev2 = (-9e9f);
        *f++ = index;
        if (r < (&freq[10]))
        {
          x3 += 17;
          x4 += 16;
          s++;
          index = 0;
          while (x4[index] < *(r-1)) index++;
          break;
        }
        else
          return;
      }
      prev2 = temp2;
      index++;
    }
  }
}


