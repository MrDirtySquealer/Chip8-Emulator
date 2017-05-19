#pragma once

//#include <boost\function.hpp>

#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;



class Chip8
{
private:
	unsigned short opcode;
	unsigned char V[16];
	unsigned char memory[4096];
	unsigned short I;
	unsigned short pc;
	unsigned char delay_timer;
	unsigned char sound_timer;
	unsigned short stack[16];
	unsigned short sp;
	

	map<unsigned short, function<void()>> opcodeDict;

	unsigned char chip8_fontset[80] =
	{
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
		0x20, 0x60, 0x20, 0x20, 0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};

//incstructions:
	void OC_00E0();
	void OC_00EE();
	void OC_1NNN();
	void OC_2NNN();
	void OC_3XNN();
	void OC_4XNN();
	void OC_5XY0();
	void OC_6XNN();
	void OC_7XNN();
	void OC_8XY0();
	void OC_8XY1();
	void OC_8XY2();
	void OC_8XY3();
	void OC_8XY4();
	void OC_8XY5();
	void OC_8XY6();
	void OC_8XY7();
	void OC_8XYE();
	void OC_9XY0();
	void OC_ANNN();
	void OC_BNNN();
	void OC_CXNN();
	void OC_DXYN();
	void OC_EX9E();
	void OC_EXA1();
	void OC_FX07();
	void OC_FX0A();
	void OC_FX15();
	void OC_FX18();
	void OC_FX1E();
	void OC_FX29();
	void OC_FX33();
	void OC_FX55();
	void OC_FX65();

public:
	unsigned char PressedKey;
	map<sf::Keyboard::Key, unsigned char> KeyboardDict;
	bool drawFlag;

	Chip8();
	void emulateCycle();
	bool loadGame(string);
	unsigned char display[64 * 32];
	vector<sf::RectangleShape> rectangleVec;
};