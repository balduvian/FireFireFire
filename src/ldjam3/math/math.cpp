#include <cmath>

#include "math.h"

namespace FFF {
	
	f32 mod(f32 a, f32 b) {
		return fmod(b + fmod(a, b), b);
	}
		
	f64 mod(f64 a, f64 b) {
		return fmod(b + fmod(a, b), b);
	}
}
