#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>

#include "chip8.h"
#include "stack.h"

int main() {
	uint16_t opcode;
	chip8 *c;

	c = malloc(sizeof (chip8));

	// Load ROM
	load_rom(c, "./roms/ibm.ch8");

	// Raylib
	InitWindow(WIDTH*10, HEIGHT*10, "Chip-8!");
	SetTargetFPS(2);

	while (!WindowShouldClose()) {
		// Fetch
		opcode = fetch(c);

		BeginDrawing();

		ClearBackground(BLACK);

		// Decode/Execute
		decode(c, opcode);

		// Draw tiles in screen
		draw_scr(c);

		EndDrawing();
	}
	CloseWindow();
}

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

int load_rom(chip8 *c, const char *path)
{
	FILE *fp;
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

	memcpy(c->mem, font, 80);

	// Map ROM/font to memory
	fp = fopen(path, "r+");

	if (fp == NULL) {
		printf("ERROR: ROM not found.");
		exit(1);
	}

	// TODO: Fix hardcoded length of opcodes
	for (int i = 0; i < 133; i++)
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

