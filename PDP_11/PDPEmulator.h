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


using namespace std;

class PDPEmulator {
public:
	PDPEmulator();

	~PDPEmulator() {
	};

	void fillROM();
	void tick();

public:
	/*CPU*/

	uint8 _T;
	uint8 _N;
	uint8 _Z;
	uint8 _V;
	uint8 _C;

	const uint16 _registers_offset = 0;
	const uint16 _RAM_offset = 8;
	const uint16 _VRAM_offset = 16*512;
	const uint16 _ROM_offset = 48*512;

	uint16 _memory[64*1024] = {0}; // 64*1024 bytes, uint16 = 2 bytes

	uint16 *_registers = _memory + _registers_offset;
	uint16 &_FP = _registers[5];
	uint16 &_SP = _registers[6];
	uint16 &_PC = _registers[7];

	uint16 *_RAM = _memory + _RAM_offset;
	uint16 *_VRAM = _memory + _VRAM_offset;
	uint16 *_ROM = _memory + _ROM_offset;



protected:
	void add(uint16 dest, uint16 source);
	void mov(uint16 dest, uint16 source);
	void sub(uint16 dest, uint16 source);
	void cmp(uint16 dest, uint16 source);
	void bnei(uint16 dest, uint16 source);
	void bis(uint16 dest, uint16 source);

	void movi(uint16 dest, uint16 source);
	void movp1(uint16 dest, uint16 source);
	void movp2(uint16 dest, uint16 source);
	void movpa(uint16 dest, uint16 source);
	void movp1i(uint16 dest, uint16 source);
	void addi(uint16 dest, uint16 source);
	void cmpi(uint16 dest, uint16 source);
	void jmp(uint16 dest, uint16 source);
};

#endif //__PDPEmulator_H_
