
#include "AssetsManager.h"
#include "resource.h"
#include <vector>

namespace FFF {
	/// set up our loading pointers
	/// and begin our loading cycle
	void AssetsManager::load(Assets* load, bool cleanLoad, Assets* unload, bool cleanUnload) {
		// set up pointers for assets to load
		auto loadRes = load->loads;

		loadBegin = loadRes;
		loadPtr = loadRes;
		loadEnd = loadRes + load->numLoads;

		this->cleanLoad = cleanLoad;

		// make sure we actually want to unload
		if (unload == nullptr) {
			doUnload = false;
		} else {
			doUnload = true;

			// pointers for assets to unload
			auto unloadRes = unload->loads;

			unloadBegin = unloadRes;
			unloadPtr = unloadRes;
			unloadEnd = unloadRes + unload->numLoads;

			this->cleanUnload = cleanUnload;
		}

		// setup our values for keeping track
		// cleaning adds an additional round of going through for the total
		// not having unload chops off the unloads from total
		loaded = 0;
		total = (load->numLoads * (cleanLoad ? 3 : 2))
			+ (doUnload ? (unload->numLoads * (cleanUnload ? 2 : 1)) : 0);

		// skip the unloading if we are not going to unload
		loadMode = doUnload ? LOAD_MODE_UNLOAD : LOAD_MODE_GATHER;
	}

	/// every frame we call this to move along with the loading process
	/// so that we load without slowing down the entire game
	/// will only do anything if we're actually in a loading cycle

	/// returns true if we're done loading

	void AssetsManager::update() {
		auto resetUnload = [this]() {
			unloadPtr = unloadBegin;
		};

		auto resetLoad = [this]() {
			loadPtr = loadBegin;
		};

		switch (loadMode) {
			case LOAD_MODE_UNLOAD:
				// keep advancing the pointer along
				while (unloadPtr < unloadEnd && (*unloadPtr)->getProcessStatus() == Resource::PROCESS_UNPROCESSED) {
					++unloadPtr;
					++loaded;
				}

				// if we reach the end
				// or if we just hit something that needed to be unloaded
				if (unloadPtr == unloadEnd)
					if (cleanUnload) {
						loadMode = LOAD_MODE_CLEAN_UNLOAD;
						resetUnload();

					}
					else
						loadMode = LOAD_MODE_GATHER;
				else
					(*unloadPtr)->unload();

				break;
			case LOAD_MODE_CLEAN_UNLOAD:
				while (unloadPtr < unloadEnd && (*unloadPtr)->getGatherStatus() == Resource::GATHER_UNGATHERED) {
					++unloadPtr;
					++loaded;
				}

				if (unloadPtr == unloadEnd)
					loadMode = LOAD_MODE_GATHER;
				else
					(*unloadPtr)->discard();

				break;
			case LOAD_MODE_GATHER:
				// an additional check to see if there is no gather for this resource
				while (loadPtr < loadEnd && (!(*loadPtr)->getHasGather() || (*loadPtr)->getGatherStatus() == Resource::GATHER_GATHERED)) {
					(*loadPtr)->joinThread();
					++loadPtr;
					++loaded;
				}

				// if we reach the end reset load pointer for processing
				if (loadPtr == loadEnd) {
					loadMode = LOAD_MODE_PROCESS;
					resetLoad();

					// if we haven't started it gathering yet
				}
				else if ((*loadPtr)->getGatherStatus() == Resource::GATHER_UNGATHERED)
					(*loadPtr)->gather();

				break;
			case LOAD_MODE_PROCESS:
				while (loadPtr < loadEnd && (*loadPtr)->getProcessStatus() == Resource::PROCESS_PROCESSED) {
					++loadPtr;
					++loaded;
				}

				if (loadPtr == loadEnd) {
					if (cleanLoad) {
						loadMode = LOAD_MODE_CLEAN_LOAD;
						resetLoad();
					}
					else
						loadMode = LOAD_MODE_DONE;

				} else {
					(*loadPtr)->process();
				}

				break;
			case LOAD_MODE_CLEAN_LOAD:
				while (loadPtr < loadEnd && (*loadPtr)->getGatherStatus() == Resource::GATHER_UNGATHERED) {
					++loadPtr;
					++loaded;
				}

				if (loadPtr == loadEnd)
					loadMode = LOAD_MODE_DONE;
				else
					(*loadPtr)->discard();

				break;
		}
	}

	void AssetsManager::quickLoad(Assets* load, bool cleanLoad) {
		auto loadRes = load->loads;

		loadBegin = loadRes;
		loadPtr = loadRes;
		loadEnd = loadRes + load->numLoads;

		auto resetLoad = [this]() {
			loadPtr = loadBegin;
		};

		// an additional check to see if there is no gather for this resource
		while (loadPtr < loadEnd) {
			if ((*loadPtr)->getHasGather() && (*loadPtr)->getGatherStatus() == Resource::GATHER_UNGATHERED) {
				(*loadPtr)->gather();
				(*loadPtr)->joinThread();
			}

			++loadPtr;
		}
			
		resetLoad();

		while (loadPtr < loadEnd) {
			if((*loadPtr)->getProcessStatus() == Resource::PROCESS_UNPROCESSED)
				(*loadPtr)->process();

			++loadPtr;
		}

		if (cleanLoad) {
			resetLoad();

			while (loadPtr < loadEnd) {
				if ((*loadPtr)->getGatherStatus() == Resource::GATHER_GATHERED)
					(*loadPtr)->discard();

				++loadPtr;
			}
		}
	}

	i32 AssetsManager::getLoadMode() {
		return loadMode;
	}

	i32 AssetsManager::getLoaded() {
		return loaded;
	}

	i32 AssetsManager::getTotal() {
		return total;
	}

}
