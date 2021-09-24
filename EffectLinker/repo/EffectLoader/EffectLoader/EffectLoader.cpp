#include "plugin.h"
//>
#include <filesystem>
//<

using namespace plugin;
//>
using namespace std;

string effectspath;

void cleanUp() {
	if (filesystem::exists(effectspath) && filesystem::is_directory(effectspath)) {
		for (filesystem::directory_entry directoryentry : filesystem::directory_iterator(effectspath)) {
			if (filesystem::is_directory(directoryentry)) {
				filesystem::remove_all(directoryentry);
			}
		}

		fstream readmefile;
		readmefile.open(effectspath + "readme.txt", fstream::out);
		readmefile << "This folder stores EffectLoader effects hard-linked by EffectLinker.";
		readmefile.close();
	}
}
//<

class EffectLoader {
public:
    EffectLoader() {
        // Initialise your plugin here
        
//>
		LoadLibrary(PLUGIN_PATH("EffectLoader.dll"));

		effectspath = string(GAME_PATH("EffectLoader")) + '/';
		filesystem::create_directories(effectspath);

		Events::attachRwPluginsEvent.after += cleanUp;

		Events::initScriptsEvent += cleanUp;
//<
    }
//>
//<
} effectLoader;

//>
//<