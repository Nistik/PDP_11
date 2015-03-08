//
// Created by Nist on 05/03/15.
// Copyright (c) 2015 ___FULLUSERNAME___. All rights reserved.
//


#ifndef __PDPEmulator_H_
#define __PDPEmulator_H_

#include <sys/types.h>
#include <unordered_map>
#include <vector>
#include "string"

class Command;

class PDPEmulator;

typedef u_int8_t uint8;
typedef u_int16_t uint16;

typedef void(PDPEmulator::*fptr)(Command &);

using namespace std;

class Command {
public:
	string command;
	string arg1;
	/* String like 'RN', where N is general register number, or immediate */
	string arg2;

	/* String like 'RN', where N is general register number, or immediate */

	Command(string c) : command(c) {
	};

	Command(string c, string a1) : command(c), arg1(a1) {
	};

	Command(string c, string a1, string a2) : command(c), arg1(a1), arg2(a2) {
	};
};

class PDPEmulator {
public:
	PDPEmulator();

	~PDPEmulator() {
	};

	void runLoop();

public:
	/*CPU*/
	uint16 _registers[8] = {0};
	uint16 &_FP = _registers[5];
	uint16 &_SP = _registers[6];
	uint16 &_PC = _registers[7];
	uint8 _T;
	uint8 _N;
	uint8 _Z;
	uint8 _V;
	uint8 _C;

	unordered_map<string, fptr> _commandFunctions;

	/*Storage*/
	/*ROM is 1024 16-bit words*/
	vector<Command> _ROM;
	uint16 _RAM[64 * 1024] = {0};
	uint16 _VRAM[64 * 1024] = {0};


	void tick();
	void execute(Command &c);

	void fillROMWithCommands(vector<Command> &);
protected:
	void registerFunctionForCommand(string commandName, fptr f);
	fptr getFunctionForCommand(Command &command);

#pragma mark Helper functions
	uint16 getRegisterFromArgString(string &arg);
	uint16 getImmediateFromArgString(string &arg);

#pragma mark Command Functions Implementations
	/*Does nothing*/
	void c_nop(Command &);
	/*Sets register to constant*/
	void c_seti(Command &);
	/*Adds two registers*/
	void c_add(Command &);
};

#endif //__PDPEmulator_H_
