#pragma once
#include "Command.h"
#include <vector>
class CompositeCommand : public Command {
public:
	void addCommand(CommandPtr command) {
		commands.push_back(command);
	}
	virtual void execute() override {
		for (const auto& command : commands) {
			command->execute();
		}
	}
	
private:
	std::vector<CommandPtr> commands;
};

