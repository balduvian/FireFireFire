/*******************************************************************************
 *
 * Copyright (c) 2019 Gnarwhal, Gatcuddy
 *
 * -----------------------------------------------------------------------------
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *******************************************************************************/

#ifndef FFF_TYPES
#define FFF_TYPES

#include <stdint.h>
#include <memory>
#include <vector>

using u8   = uint8_t;
using i8   =  int8_t;
using u16  = uint16_t;
using i16  =  int16_t;
using u32  = uint32_t;
using i32  =  int32_t;
using u64  = uint64_t;
using i64  =  int64_t;
using size =   size_t;

constexpr auto operator "" _u8  (unsigned long long int num) noexcept -> u8   { return (u8  ) num; }
constexpr auto operator "" _i8  (unsigned long long int num) noexcept -> i8   { return (u8  ) num; }
constexpr auto operator "" _u16 (unsigned long long int num) noexcept -> u16  { return (u16 ) num; }
constexpr auto operator "" _i16 (unsigned long long int num) noexcept -> i16  { return (i16 ) num; }
constexpr auto operator "" _u32 (unsigned long long int num) noexcept -> u32  { return (u32 ) num; }
constexpr auto operator "" _i32 (unsigned long long int num) noexcept -> i32  { return (i32 ) num; }
constexpr auto operator "" _u64 (unsigned long long int num) noexcept -> u64  { return (u64 ) num; }
constexpr auto operator "" _i64 (unsigned long long int num) noexcept -> i64  { return (i64 ) num; }
constexpr auto operator "" _size(unsigned long long int num) noexcept -> size { return (size) num; }

using c8  = u8;
using c16 = u16;
using c32 = u32;

constexpr auto operator "" _c8 (char c) noexcept -> c8  { return (c8 ) (c & 0xFF); }
constexpr auto operator "" _c16(char c) noexcept -> c16 { return (c16) (c & 0xFF); }
constexpr auto operator "" _c32(char c) noexcept -> c32 { return (c32) (c & 0xFF); }
constexpr auto operator "" _c8 (unsigned long long int c) noexcept -> c8  { return (c8 ) c; }
constexpr auto operator "" _c16(unsigned long long int c) noexcept -> c16 { return (c16) c; }
constexpr auto operator "" _c32(unsigned long long int c) noexcept -> c32 { return (c32) c; }

using f32 = float;
using f64 = double;

constexpr auto operator "" _f32(long double num)            noexcept -> f32 { return (f32) num; }
constexpr auto operator "" _f32(unsigned long long int num) noexcept -> f32 { return (f32) num; }
constexpr auto operator "" _f64(long double num)            noexcept -> f64 { return (f64) num; }
constexpr auto operator "" _f64(unsigned long long int num) noexcept -> f64 { return (f64) num; }

template <typename T>
using uptr = std::unique_ptr<T>;

template <typename T>
using sptr = std::shared_ptr<T>;

#endif // FFF_TYPES
