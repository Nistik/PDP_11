//
// Created by Nist on 05/03/15.
// Copyright (c) 2015 ___FULLUSERNAME___. All rights reserved.
//

/*
*
*
* THIS CODE IS UNSAFE, IT DOES NOT CHECKS NULL POINTERS.
*
*
* */

#include <iostream>
#include "PDPEmulator.h"

using namespace std;

PDPEmulator::PDPEmulator() {
	registerFunctionForCommand(string("nop"), &PDPEmulator::c_nop);
	registerFunctionForCommand(string("add"), &PDPEmulator::c_add);
	registerFunctionForCommand(string("seti"), &PDPEmulator::c_seti);

	_ROM.push_back(Command("nop"));
	_ROM.push_back(Command("seti", "R1", "4"));
	_ROM.push_back(Command("seti", "R2", "8"));
	_ROM.push_back(Command("add", "R1", "R2"));
}

void PDPEmulator::runLoop() {
	for (; ;) {
		if (_PC >= _ROM.size())
			break;
		tick();
	}

	for (int i = 0; i < 8; ++i) {
		cout << "R" << i << ": " << _registers[i] << endl;
	}
}

void PDPEmulator::tick() {
	execute(_ROM[_PC++]);
}

void PDPEmulator::execute(Command &c) {
	fptr func = getFunctionForCommand(c);
	(this->*func)(c);
}

void PDPEmulator::fillROMWithCommands(vector<Command> &commands) {
	_ROM.clear();
	_ROM.reserve(commands.size());
	_ROM.insert(_ROM.end(), commands.begin(), commands.end());
}


void PDPEmulator::registerFunctionForCommand(string commandName, fptr f) {
	_commandFunctions[commandName] = f;
}

fptr PDPEmulator::getFunctionForCommand(Command &command) {
	return _commandFunctions[command.command];
}

#pragma mark Helper functions

uint16 PDPEmulator::getRegisterFromArgString(string &arg) {
	return (uint16) stoi(arg.substr(1, 1));
}

uint16 PDPEmulator::getImmediateFromArgString(string &arg) {
	return (uint16) stoi(arg);
}

#pragma mark Command Functions Implementations

void PDPEmulator::c_nop(Command &command) {
	cout << "ПОШЕЛ НАХУЙ\n";
}

void PDPEmulator::c_seti(Command &command) {
	uint16 reg = getRegisterFromArgString(command.arg1);
	uint16 immediate = getImmediateFromArgString(command.arg2);

	_registers[reg] = immediate;
}

void PDPEmulator::c_add(Command &command) {
	uint16 reg1 = getRegisterFromArgString(command.arg1);
	uint16 reg2 = getRegisterFromArgString(command.arg2);

	_registers[reg1] = _registers[reg1] + _registers[reg2];
	/* Добавить работу с флагами состяния */
}

