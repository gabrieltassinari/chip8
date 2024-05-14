#include <stdlib.h>
#include <raylib.h>

#include "chip8.h"

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
