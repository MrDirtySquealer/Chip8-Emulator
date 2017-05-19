#include "Chip-8.h"

void Chip8::OC_00E0()
{
	for (size_t i = 0; i < 64 * 32; i++)
		display[i] = '\0';
	pc += 2;
}

void Chip8::OC_00EE()
{
	sp--;
	pc = stack[sp];
	pc += 2;
}

void Chip8::OC_1NNN()
{
	pc = opcode & 0x0FFF;
}

void Chip8::OC_2NNN()
{
	stack[sp] = pc;
	sp++;
	
	pc = opcode & 0x0FFF;
}

void Chip8::OC_3XNN()
{
	if (V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF))
		pc += 4;
	else pc += 2;
}

void Chip8::OC_4XNN()
{
	if (V[(opcode & 0x0F00) >> 8] != (opcode & 0x0FF))
		pc += 4;
	else pc += 2;
}

void Chip8::OC_5XY0()
{
	if (V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F0) >> 4])
		pc += 4;
	else pc += 2;
}

void Chip8::OC_6XNN()
{
	V[(opcode & 0x0F00) >> 8] = (opcode & 0x00FF);

	pc += 2;
}

void Chip8::OC_7XNN()
{
	V[(opcode & 0x0F00) >> 8] += (opcode & 0x00FF);

	pc += 2;
}

void Chip8::OC_8XY0()
{
	V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4];

	pc += 2;
}

void Chip8::OC_8XY1()
{
	V[(opcode & 0x0F00) >> 8] |= V[(opcode & 0x00F0) >> 4];

	pc += 2;
}

void Chip8::OC_8XY2()
{
	V[(opcode & 0x0F00) >> 8] &= V[(opcode & 0x00F0) >> 4];

	pc += 2;
}

void Chip8::OC_8XY3()
{
	V[(opcode & 0x0F00) >> 8] ^= V[(opcode & 0x00F0) >> 4];

	pc += 2;
}

void Chip8::OC_8XY4()
{
	if (V[(opcode & 0x0F00) >> 8] + V[(opcode & 0x00F0) >> 4] > UCHAR_MAX)
		V[15] = 1;
	else V[15] = 0;
	V[(opcode & 0x0F00) >> 8] += V[(opcode & 0x00F0) >> 4];

	pc += 2;
}

void Chip8::OC_8XY5()
{
	if (V[(opcode & 0x0F00) >> 8] - V[(opcode & 0x00F0) >> 4] < 0)
		V[15] = 0;
	else V[15] = 1;

	V[(opcode & 0x0F00) >> 8] -= V[(opcode & 0x00F0) >> 4];
	pc += 2;
}

void Chip8::OC_8XY6()
{
	V[15] = V[(opcode & 0x0F00) >> 8] & 0x0001;
	V[(opcode & 0x0F00) >> 8] >>= 1;
	pc += 2;
}

void Chip8::OC_8XY7()
{
	if (V[(opcode & 0x00F0) >> 8] - V[(opcode & 0x0F00) >> 4] < 0)
		V[15] = 0;
	else V[15] = 1;

	V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4] - V[(opcode & 0x0F00) >> 8];
	pc += 2;
}

void Chip8::OC_8XYE()
{
	V[15] = V[(opcode & 0x0F00) >> 8] & 0x8000;
	V[(opcode & 0x0F00) >> 8] <<= 1;
	pc += 2;
}

void Chip8::OC_9XY0()
{
	if (V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 4])
		pc += 4;
	else pc += 2;
}

void Chip8::OC_ANNN()
{
	I = (opcode & 0x0FFF);
	pc += 2;
}

void Chip8::OC_BNNN()
{
	stack[sp] = pc;
	sp++;
	pc = V[0] + (opcode & 0x0FFF);
}

void Chip8::OC_CXNN()
{
	V[(opcode & 0x0F00) >> 8] = (rand() % 256) & (opcode & 0x00FF);
	pc += 2;
}

void Chip8::OC_DXYN()
{
	unsigned int x = V[(opcode & 0x0F00) >> 8];
	unsigned int y = V[(opcode & 0x00F0) >> 4];
	unsigned int n = opcode & 0x000F;

	unsigned short pixel;
	V[0xF] = 0;
	for (size_t i = 0; i < n; i++)
	{
		pixel = memory[I + i];
		for (size_t j = 0; j < 8; j++)
		{
			if ((pixel & (0x80 >> j)) != 0)
			{
				if (display[(x + j + ((y + i) * 64))] == 1)
					V[0xF] = 1;
					display[x + j + ((y + i) * 64)] ^= 1;
			}
		}
	}
	drawFlag = true;
	pc += 2;
}

void Chip8::OC_EX9E()
{
	if (V[(opcode & 0x0F00) >> 8] == PressedKey)
		pc += 4;
	else
		pc += 2;
}

void Chip8::OC_EXA1()
{
	if (V[(opcode & 0x0F00) >> 8] != PressedKey)
		pc += 4;
	else
		pc += 2;
}

void Chip8::OC_FX07()
{
	V[(opcode & 0x0F00) >> 8] = delay_timer;
	pc += 2;
}

void Chip8::OC_FX0A()
{
	if (PressedKey != 0x10)
	{
		V[(opcode & 0x0F00) >> 8] = PressedKey;
		pc += 2;
	}
}

void Chip8::OC_FX15()
{
	delay_timer = V[(opcode & 0x0F00) >> 8];
	pc += 2;
}

void Chip8::OC_FX18()
{
	sound_timer = V[(opcode & 0x0F00) >> 8];
	pc += 2;
}

void Chip8::OC_FX1E()
{
	I += V[(opcode & 0x0F00) >> 8];
	pc += 2;
}

void Chip8::OC_FX29()
{
	if (V[(opcode & 0x0F00) >> 8] == 0)
		I = 0;
	else
		I = V[(opcode & 0x0F00) >> 8] * 5;

	pc += 2;
}

void Chip8::OC_FX33()
{
	unsigned short value = V[(opcode & 0x0F00) >> 8];

	memory[I + 2] = value % 10;
	value /= 10;

	memory[I + 1] = value % 10;
	value /= 10;

	memory[I] = value % 10;

	pc += 2;
}

void Chip8::OC_FX55()
{
	for (size_t i = 0; i <= ((opcode & 0x0F00) >> 8); i++)
		memory[i + I] = V[i];
	pc += 2;
}

void Chip8::OC_FX65()
{
	for (size_t i = 0; i <= ((opcode & 0x0F00) >> 8); i++)
		V[i] = memory[i + I];
	pc += 2;
}
