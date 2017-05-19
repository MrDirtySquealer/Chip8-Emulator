#include "Chip-8.h"
#include <SFML\Graphics.hpp>
#include <Windows.h>
using namespace sf;

void Chip8::emulateCycle()
{
	opcode = memory[pc] << 8 | memory[pc + 1];

	if ((opcode & 0xF000) == 0x0000)
		opcodeDict[opcode & 0xF00F]();
	else
	if ((opcode & 0xF000) == 0x8000)
		opcodeDict[opcode & 0xF00F]();
	else
	if ((opcode & 0xF000) == 0xE000)
		opcodeDict[opcode & 0xF00F]();
	else
		if ((opcode & 0xF000) == 0xF000)
			opcodeDict[opcode & 0xF0FF]();
		else
			opcodeDict[opcode & 0xF000]();



		// Update timers
		if (delay_timer > 0)
			--delay_timer;

		if (sound_timer > 0)
		{
			if (sound_timer == 1)
				Beep(523.26, 50);
				
			--sound_timer;
		}
	}



bool Chip8::loadGame(string path)
{
	int i = 0X200;
	unsigned char ch;
	ifstream fin(path, ios::in | ios::binary);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			fin.read((char*)&ch, sizeof(ch));
			memory[i] = ch;
			i++;
		}
		return 1;
	}
	else
	{
		cout << "Game is'nt found" << endl;
		return 0;
	}

}

Chip8::Chip8()
{
	pc = 0x200;

	PressedKey = 0x10;

	opcode = 0;
	I = 0;
	sp = 0;

	for (int i(0); i < 64 * 32; ++i)
		display[i] = '\0';

	for (size_t i = 0; i < 16; i++) {
		stack[i] = 0;
		V[i] = 0;
	}

	for (size_t i = 0; i < 4096; i++)
		memory[i] = '\0';

	for (int i = 0; i < 80; ++i)
		memory[i] = chip8_fontset[i];


	opcodeDict[0x0000] = std::bind(&Chip8::OC_00E0, this);
	opcodeDict[0x000E] = std::bind(&Chip8::OC_00EE, this);
	opcodeDict[0x1000] = std::bind(&Chip8::OC_1NNN, this);
	opcodeDict[0x2000] = std::bind(&Chip8::OC_2NNN, this);
	opcodeDict[0x3000] = std::bind(&Chip8::OC_3XNN, this);
	opcodeDict[0x4000] = std::bind(&Chip8::OC_4XNN, this);
	opcodeDict[0x5000] = std::bind(&Chip8::OC_5XY0, this);
	opcodeDict[0x6000] = std::bind(&Chip8::OC_6XNN, this);
	opcodeDict[0x7000] = std::bind(&Chip8::OC_7XNN, this);
	opcodeDict[0x8000] = std::bind(&Chip8::OC_8XY0, this);
	opcodeDict[0x8001] = std::bind(&Chip8::OC_8XY1, this);
	opcodeDict[0x8002] = std::bind(&Chip8::OC_8XY2, this);
	opcodeDict[0x8003] = std::bind(&Chip8::OC_8XY3, this);
	opcodeDict[0x8004] = std::bind(&Chip8::OC_8XY4, this);
	opcodeDict[0x8005] = std::bind(&Chip8::OC_8XY5, this);
	opcodeDict[0x8006] = std::bind(&Chip8::OC_8XY6, this);
	opcodeDict[0x8007] = std::bind(&Chip8::OC_8XY7, this);
	opcodeDict[0x800E] = std::bind(&Chip8::OC_8XYE, this);
	opcodeDict[0x9000] = std::bind(&Chip8::OC_9XY0, this);
	opcodeDict[0xA000] = std::bind(&Chip8::OC_ANNN, this);
	opcodeDict[0xB000] = std::bind(&Chip8::OC_BNNN, this);
	opcodeDict[0xC000] = std::bind(&Chip8::OC_CXNN, this);
	opcodeDict[0xD000] = std::bind(&Chip8::OC_DXYN, this);
	opcodeDict[0xE00E] = std::bind(&Chip8::OC_EX9E, this);
	opcodeDict[0xE001] = std::bind(&Chip8::OC_EXA1, this);
	opcodeDict[0xF007] = std::bind(&Chip8::OC_FX07, this);
	opcodeDict[0xF00A] = std::bind(&Chip8::OC_FX0A, this);
	opcodeDict[0xF015] = std::bind(&Chip8::OC_FX15, this);
	opcodeDict[0xF018] = std::bind(&Chip8::OC_FX18, this);
	opcodeDict[0xF01E] = std::bind(&Chip8::OC_FX1E, this);
	opcodeDict[0xF029] = std::bind(&Chip8::OC_FX29, this);
	opcodeDict[0xF033] = std::bind(&Chip8::OC_FX33, this);
	opcodeDict[0xF055] = std::bind(&Chip8::OC_FX55, this);
	opcodeDict[0xF065] = std::bind(&Chip8::OC_FX65, this);

	KeyboardDict[Keyboard::Num1] = 1;
	KeyboardDict[Keyboard::Num2] = 2;
	KeyboardDict[Keyboard::Num3] = 3;
	KeyboardDict[Keyboard::Num4] = 0xC;
	KeyboardDict[Keyboard::Q] = 4;
	KeyboardDict[Keyboard::W] = 5;
	KeyboardDict[Keyboard::E] = 6;
	KeyboardDict[Keyboard::R] = 0xD;
	KeyboardDict[Keyboard::A] = 7;
	KeyboardDict[Keyboard::S] = 8;
	KeyboardDict[Keyboard::D] = 9;
	KeyboardDict[Keyboard::F] = 0xE;
	KeyboardDict[Keyboard::Z] = 0xA;
	KeyboardDict[Keyboard::X] = 0;
	KeyboardDict[Keyboard::C] = 0xB;
	KeyboardDict[Keyboard::V] = 0xF;

}