#include <stdio.h>
#include "chip8.h"

void decode(chip8 *c, uint16_t opcode)
{
	uint16_t X, Y, N, NN, NNN, op;
	uint16_t xcord, ycord, sprite, bit;

	op = (opcode & 0xF000) >> 12;
	X = (opcode & 0x0F00) >> 8;
	Y = (opcode & 0x00F0) >> 4;

	N = (opcode & 0x000F);
	NN = (opcode & 0x00FF);
	NNN = (X << 8) | NN;

	switch (op) {
	case 0:
		// 00E0
		for (int y = 0; y < HEIGHT; y++)
			for (int x = 0; x < WIDTH; x++)
				c->scr[y][x] = 0;
		break;
	case 1:
		// 1NNN
		c->PC = NNN;
		break;
	case 6:
		// 6XNN
		c->V[X] = NN;
		break;
	case 7:
		// 7XNN
		c->V[X] += NN;
		break;
	case A:
		// ANNN
		c->I = NNN;
		break;
	case D:
		// DXYN

		// TODO: Draw
		xcord = c->V[X] & 63;
		ycord = c->V[Y] & 31;
		c->V[F] = 0;

		for (int i = 0; i < N; i++) {
			xcord = c->V[X] & 63;
			sprite = c->mem[c->I+i];

			for (int j = 0; j < 8; j++) {
				bit = sprite & (0x80 >> j);

				if (bit && c->scr[ycord][xcord] == 1) {
					c->scr[ycord][xcord] = 0;
					c->V[F] = 1;
				} else if (bit && c->scr[ycord][xcord] == 0) {
					c->scr[ycord][xcord] = 1;
				}

				if (++xcord > 63) break;
			}

			if (++ycord > 31) return;
		}
		break;
	default:
		printf("ERROR: Opcode %#x not implemented.\n", opcode);
	}
}
