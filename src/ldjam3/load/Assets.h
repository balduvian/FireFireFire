
#ifndef FFF_ASSETS
#define FFF_ASSETS

#include "resource.h"

namespace FFF {
	class Assets {
	public:
		u32 numLoads;
		Resource** loads;

		Assets(u32 numLoads, Resource** loads);
	};
}

#endif