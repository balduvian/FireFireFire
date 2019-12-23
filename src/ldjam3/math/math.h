
#ifndef FFF_MATH
#define FFF_MATH

#include "../Types.h"

namespace FFF {

	template<typename T>
	T mod(T a, T b) {
		return (b + (a % b)) % b;
	}

	template<>
	f32 mod<f32>(f32 a, f32 b);

	template<>
	f64 mod<f64>(f64 a, f64 b);
}

#endif // FFF_MATH
