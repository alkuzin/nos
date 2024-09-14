/**
 * The Null Operating System (NOS).
 * Copyright (C) 2024  Alexander (@alkuzin).
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <nos/stdlib.hpp>


namespace kernel {
namespace std {

// Convertion Functions ---------------------------------------------

f64 atof(const char *str)
{
    f64 res      = 0;
    f64 fraction = 1;
    s32 sign     = 1;
    s32 decimal  = 0;

    while (*str == ' ')
        str++;

    if (*str == '-') {
        sign = -1;
        str++;
    } 
    else if (*str == '+')
        str++;

    while (*str != '\0') {

        if (*str >= '0' && *str <= '9') {
            res = res * 10 + (*str - '0');

            if (decimal)
                fraction *= 10;
        } 
        else if (*str == '.')
            decimal = 1;
        else
            break;

        str++;
    }
    
    return (sign * res) / fraction;
}

s32 atoi(const char *str)
{
    s32 i           = 0;
    s32 res         = 0;
    s32 is_negative = 0;
    
    if(str[i] == '-') {
        is_negative = 1;
        i++;
    }
    
    while(str[i] && (str[i] >= '0' && str[i] <= '9')) {
        res *= 10;
        res += (static_cast<int>(str[i]) - '0');
        i++;
    }

    if(is_negative)
        return -res;
    
    return res;
}

// Pseudo-random Functions ---------------------------------------------

static u64 next = 1;

s32 rand(void)
{
    next = next * 1103515245 + 12345;
    return static_cast<u32>(next / 65536) % RAND_MAX;
}

void srand(u32 seed)
{
    next = seed;
}

} // namespace std    
} // namespace kernel