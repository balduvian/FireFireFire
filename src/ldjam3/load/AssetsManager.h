
#ifndef FFF_ASSETSMANAGER
#define FFF_ASSETSMANAGER

#include "Assets.h"

namespace FFF {
	class AssetsManager {
	private:
		/// for keeping track of how far along we are
		i32 loaded = 0;
		i32 total = 0;

		i32 loadMode = LOAD_MODE_NOT;

	public:
		constexpr static i32 LOAD_MODE_NOT = 0;
		constexpr static i32 LOAD_MODE_UNLOAD = 1;
		constexpr static i32 LOAD_MODE_CLEAN_UNLOAD = 2;
		constexpr static i32 LOAD_MODE_GATHER = 3;
		constexpr static i32 LOAD_MODE_PROCESS = 4;
		constexpr static i32 LOAD_MODE_CLEAN_LOAD = 5;
		constexpr static i32 LOAD_MODE_DONE = 6;

		Resource** loadBegin = nullptr;
		Resource** loadPtr = nullptr;
		Resource** loadEnd = nullptr;

		Resource** unloadBegin = nullptr;
		Resource** unloadPtr = nullptr;
		Resource** unloadEnd = nullptr;

		bool doUnload = false;

		bool cleanLoad = false;
		bool cleanUnload = false;

		i32 getLoaded();
		i32 getTotal();

		/// don't pass in anything to the last two to not unload anything
		void load(Assets* load, bool cleanLoad, Assets* unload = nullptr, bool cleanUnload = false);

		/// quickload is used for blocking loads, runs once
		/// no updating required
		void quickLoad(Assets* load, bool cleanLoad);

		void update();

		i32 getLoadMode();

	};
}

#endif