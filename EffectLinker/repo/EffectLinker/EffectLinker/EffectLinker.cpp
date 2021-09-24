#include "plugin.h"
//>>>
#include "filesystem"
//<<<

using namespace plugin;
//>>>
using namespace std;

HMODULE effectmodule;
string effectspath;

bool checkDirectory(string directorypath) {
	return filesystem::exists(directorypath) && filesystem::is_directory(directorypath);
}

string pluginpath;

void createLinks() {
	if (checkDirectory(pluginpath)) {
		for (filesystem::directory_entry directoryentry : filesystem::directory_iterator(pluginpath)) {
			if (checkDirectory(directoryentry.path().string())) {
				for (filesystem::directory_entry effectfile : filesystem::directory_iterator(directoryentry)) {
					filesystem::path entrypath = effectfile.path();
					filesystem::path targetpath = effectspath + directoryentry.path().filename().string() + '/' + entrypath.filename().string();
					filesystem::create_directories(targetpath.parent_path());
					filesystem::remove_all(targetpath);
					if (filesystem::is_directory(effectfile)) {
						filesystem::create_directories(targetpath);
					}
					else {
						filesystem::create_hard_link(entrypath, targetpath);
					}
				}
			}
		}
	}
}
//<<<

class EffectLinker {
public:
    EffectLinker() {
        // Initialise your plugin here
        
//>>>
		Events::initGameEvent.before += [] {
			effectmodule = GetModuleHandle("EffectLoader.asi");
			if (effectmodule) {
				pluginpath = PLUGIN_PATH("") + filesystem::path(PLUGIN_FILENAME).stem().string() + '/';

				effectspath = string(GAME_PATH("EffectLoader")) + '/';

				createLinks();
			}
		};
//<<<
    }
//>>>
//<<<
} effectLinker;

//>>>
//<<<