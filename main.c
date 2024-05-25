#include <raylib.h>
#include <stdlib.h>

#include "chip8.h"

int main(int argc, char **argv) {
	uint16_t opcode;
	chip8 *c;

	c = malloc(sizeof (chip8));

	init_chip8(c, argv[1]);

	// Raylib
	InitWindow(WIDTH*10, HEIGHT*10, "Chip-8!");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		// Emulate Chip-8 CPU
		for (int i = 0; i < 11; i++) {
			opcode = fetch(c);
			decode(c, opcode);
		}

		// Draw tiles in screen
		BeginDrawing();
			ClearBackground(BLACK);
			draw_scr(c);
		EndDrawing();
	}

	free(c);
	CloseWindow();
}
