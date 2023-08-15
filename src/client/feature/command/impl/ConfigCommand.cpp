#include "ConfigCommand.h"
#include "client/config/ConfigManager.h"
#include "client/Latite.h"

ConfigCommand::ConfigCommand() : Command("config", "Do actions related to profiles/configs", "$ load <name>\n$ save", {"profile", "configs", "profiles", "cfg"}) {	
}

bool ConfigCommand::execute(std::string const label, std::vector<std::string> args) {
	if (args.empty()) return false;
	if (args[0] == "save") {
		if (Latite::getConfigManager().saveCurrentConfig())
			message("Saved current config!");
		else message("Something went wrong!", true);
		return true;
	}
	else if (args[0] == "load") {
		if (args.size() < 2) {
			return false;
		}

		if (!Latite::getConfigManager().saveCurrentConfig()) {
			message("Could not save current config before loading!", true);
			return false;
		}

		if (!Latite::getConfigManager().loadUserConfig(util::StrToWStr(args[1]))) {
			message("Could not find config &7" + args[1], true);
			return true;
		}
		message("Successfully loaded config &7" + args[1]);
	}
	return true;
}
