#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <string.h>
#include <time.h>

#include "chip8.h"

void draw_scr(chip8 *c)
{
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (c->scr[y][x] == 1)
				DrawRectangle(x*10, y*10, 10, 10, GRAY);
			else
				DrawRectangle(x*10, y*10, 10, 10, BLACK);
		}
	}
}

int init_chip8(chip8 *c, const char *path)
{
	uint8_t font[80] = {
		0xFA, 0xBE, 0x90, 0x90, 0xF0, // 0
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

	uint8_t keypad[16] = {
		KEY_ZERO, KEY_ONE, KEY_TWO, KEY_THREE,
		KEY_FOUR, KEY_FIVE, KEY_SIX, KEY_SEVEN,
		KEY_EIGHT, KEY_NINE, KEY_A, KEY_B,
		KEY_C, KEY_D, KEY_E, KEY_F
	};

	srand(time(NULL));

	// Map ROM/font to memory
	memcpy(c->mem, font, 80);
	memcpy(c->keypad, keypad, 16);

	return load_rom(c, path);
}

int load_rom(chip8 *c, const char *path)
{
	FILE *fp;
	int file_size;

	fp = fopen(path, "r+");

	if (fp == NULL) {
		printf("ERROR: ROM not found.\n");
		exit(1);
	}

	// Get ROM size
	fseek(fp, 0L, SEEK_END);
	file_size = ftell(fp);
	rewind(fp);

	for (int i = 0; i < file_size; i++)
		c->mem[512+i] = getc(fp);
	c->PC = 512;

	return 1;
}

uint16_t fetch(chip8 *c)
{
	uint16_t opcode;

	opcode = (c->mem[c->PC++] << 8) | c->mem[c->PC++];

	return opcode;
}
