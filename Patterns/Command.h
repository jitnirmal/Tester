#pragma once

#include <memory>
#include <iostream>
#include <chrono>
#include <thread>
#include "Composite.h"

class Command {
public:
	virtual ~Command() = default;
	virtual void execute() = 0;
};

using CommandPtr = std::shared_ptr<Command>;


class APServer {
public:
	void acceptCommand(const CommandPtr& command) {
		command->execute();
	}
};

class FirstCommand : public Command {
public:
	virtual void execute() override {
		std::cout << "First Command" << "\n";
	}
};

class SecondCommand : public Command {
public:
	virtual void execute() override {
		std::cout << "Second Command" << "\n";
	}
};

class ThirdCommand : public Command {
public:
	virtual void execute() override {
		std::cout << "ThirdCommand " << "\n";
	}
};

class WaitCommand : public Command {
public:
	explicit WaitCommand(const unsigned int durationInMilliseconds) noexcept :
		durationInMilliseconds{ durationInMilliseconds } { };
	virtual void execute() override {
		std::chrono::milliseconds dur(durationInMilliseconds);
		std::cout << "ThirdCommand " << "\n";
		std::this_thread::sleep_for(dur);
	}
private:
	unsigned int durationInMilliseconds{ 1000 };
};



class Client {
public:
	void run() {
		APServer theServer{};

		const unsigned int SERVER_DELAY_TIMESPAN{ 3000 };
		CommandPtr waitCommand = std::make_shared<WaitCommand>(SERVER_DELAY_TIMESPAN);
		theServer.acceptCommand(waitCommand);

		auto compositeCommand = std::make_shared<CompositeCommand>();
		compositeCommand->addCommand(std::make_shared<FirstCommand>());
		compositeCommand->addCommand(std::make_shared<SecondCommand>());
		compositeCommand->addCommand(std::make_shared<ThirdCommand>());

		theServer.acceptCommand(compositeCommand);
	}
};