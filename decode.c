#include <stdio.h>
#include "chip8.h"

void decode(chip8 *c, uint16_t opcode)
{
	uint16_t X, Y, N, NN, NNN, op;

	op = (opcode & 0xF000) >> 12;
	X = (opcode & 0x0F00) >> 8;
	Y = (opcode & 0x00F0) >> 4;

	N = (opcode & 0x000F);
	NN = (opcode & 0x00FF);
	NNN = (X << 8) | NN;

	switch (op) {
	case 0:
		op_00E0(c);
		break;
	case 1:
		op_1NNN(c, NNN);
		break;
	case 6:
		op_6XNN(c, NN, X);
		break;
	case 7:
		op_7XNN(c, NN, X);
		break;
	case A:
		op_ANNN(c, NNN);
		break;
	case D:
		op_DXYN(c, N, X, Y);
	default:
		printf("ERROR: Opcode %#x not implemented.\n", opcode);
	}
}

void op_00E0(chip8 *c)
{
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			c->scr[y][x] = 0;

}

void op_1NNN(chip8 *c, uint16_t NNN)
{
	c->PC = NNN;
}

void op_6XNN(chip8 *c, uint16_t NN, uint16_t X)
{
	c->V[X] = NN;
}

void op_7XNN(chip8 *c, uint16_t NN, uint16_t X)
{
	c->V[X] += NN;
}

void op_ANNN(chip8 *c, uint16_t NNN)
{
	c->I = NNN;
}

void op_DXYN(chip8 *c, uint16_t N, uint16_t X, uint16_t Y)
{
	uint16_t xcord, ycord, sprite, bit;

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
}
