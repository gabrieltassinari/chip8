#include <stdio.h>
#include <stdlib.h>
#include "chip8.h"

void decode(chip8 *c, uint16_t opcode)
{
	uint16_t X, Y, N, NN, NNN;

	X = (opcode & 0x0F00) >> 8;
	Y = (opcode & 0x00F0) >> 4;

	N = (opcode & 0x000F);
	NN = (opcode & 0x00FF);
	NNN = (X << 8) | NN;


	switch (opcode & 0xF000) {
	case 0x0000:
		switch (opcode & 0x00FF) {
		case 0X00E0:
			op_00E0(c);
			return;
		case 0x00EE:
			op_00EE(c);
			return;
		}
	case 0x1000:
		op_1NNN(c, NNN);
		break;
	case 0x2000:
		op_2NNN(c, NNN);
		break;
	case 0x3000:
		op_3XNN(c, X, NN);
		break;
	case 0x4000:
		op_4XNN(c, X, NN);
		break;
	case 0x5000:
		op_5XY0(c, X, Y);
		break;
	case 0x6000:
		op_6XNN(c, X, NN);
		break;
	case 0x7000:
		op_7XNN(c, X, NN);
		break;
	case 0x8000:
		switch (opcode & 0x000F) {
		case 0x0000:
			op_8XY0(c, X, Y);
			return;
		case 0x0001:
			op_8XY1(c, X, Y);
			return;
		case 0x0002:
			op_8XY2(c, X, Y);
			return;
		case 0x0003:
			op_8XY3(c, X, Y);
			return;
		case 0x0004:
			op_8XY4(c, X, Y);
			return;
		case 0x0005:
			op_8XY5(c, X, Y);
			return;
		case 0x0006:
			op_8XY6(c, X, Y);
			return;
		case 0x0007:
			op_8XY7(c, X, Y);
			return;
		case 0x000E:
			op_8XYE(c, X, Y);
			return;
		}
	case 0x9000:
		op_9XY0(c, X, Y);
		break;
	case 0xA000:
		op_ANNN(c, NNN);
		break;
	case 0xB000:
		op_BNNN(c, X, NNN);
		break;
	case 0xC000:
		op_CXNN(c, X, NN);
		break;
	case 0xD000:
		op_DXYN(c, X, Y, N);
		break;
	default:
		printf("ERROR: Opcode %#x not implemented.\n", opcode);
	}
}

void op_00E0(chip8 *c)
{
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++)
			c->scr[y][x] = 0;
	}

}

void op_00EE(chip8 *c)
{
	c->PC = pop(&c->stack);
}

void op_1NNN(chip8 *c, uint16_t NNN)
{
	c->PC = NNN;
}

void op_2NNN(chip8 *c, uint16_t NNN)
{
	push(&c->stack, c->PC);
	c->PC = NNN;
}

void op_3XNN(chip8 *c, uint16_t X, uint16_t NN)
{
	if (c->V[X] == NN)
		c->PC += 2;
}

void op_4XNN(chip8 *c, uint16_t X, uint16_t NN)
{
	if (c->V[X] != NN)
		c->PC += 2;
}

void op_5XY0(chip8 *c, uint16_t X, uint16_t Y)
{
	if (c->V[X] == c->V[Y])
		c->PC += 2;
}

void op_6XNN(chip8 *c, uint16_t X, uint16_t NN)
{
	c->V[X] = NN;
}

void op_7XNN(chip8 *c, uint16_t X, uint16_t NN)
{
	c->V[X] += NN;
}

void op_8XY0(chip8 *c, uint16_t X, uint16_t Y)
{
	c->V[X] = c->V[Y];
}

void op_8XY1(chip8 *c, uint16_t X, uint16_t Y)
{
	c->V[X] = c->V[X] | c->V[Y];
}

void op_8XY2(chip8 *c, uint16_t X, uint16_t Y)
{
	c->V[X] = c->V[X] & c->V[Y];
}

void op_8XY3(chip8 *c, uint16_t X, uint16_t Y)
{
	c->V[X] = c->V[X] ^ c->V[Y];
}

void op_8XY4(chip8 *c, uint16_t X, uint16_t Y)
{
	c->V[X] = c->V[X] + c->V[Y];

	if (c->V[X] + c->V[Y] > 255)
		c->V[F] = 1;
	else
		c->V[F] = 0;
}

void op_8XY5(chip8 *c, uint16_t X, uint16_t Y)
{
	c->V[X] = c->V[X] - c->V[Y];

	if (c->V[X] > c->V[Y])
		c->V[F] = 1;
	else
		c->V[F] = 0;
}

void op_8XY6(chip8 *c, uint16_t X, uint16_t Y)
{
	if (c->cosmac_vip)
		c->V[X] = c->V[Y];

	c->V[F] = c->V[X] & 0x01;
	c->V[X] = c->V[X] >> 1;
}

void op_8XY7(chip8 *c, uint16_t X, uint16_t Y)
{
	c->V[X] = c->V[Y] - c->V[X];

	if (c->V[Y] > c->V[X])
		c->V[F] = 1;
	else
		c->V[F] = 0;
}

void op_8XYE(chip8 *c, uint16_t X, uint16_t Y)
{
	if (c->cosmac_vip)
		c->V[X] = c->V[Y];

	c->V[F] = (c->V[X] & 0x80) >> 7;
	c->V[X] = c->V[X] << 1;
}

void op_9XY0(chip8 *c, uint16_t X, uint16_t Y)
{
	if (c->V[X] != c->V[Y])
		c->PC += 2;
}

void op_ANNN(chip8 *c, uint16_t NNN)
{
	c->I = NNN;
}

void op_BNNN(chip8 *c, uint16_t X, uint16_t NNN)
{
	if (c->cosmac_vip)
		c->PC = c->mem[NNN] + c->V[0];
	else
		c->PC = c->mem[NNN] + c->V[X];
}

void op_CXNN(chip8 *c, uint16_t X, uint16_t NN)
{
	uint16_t n_random;

	n_random = rand() % 256;

	c->V[X] = n_random & NN;
}

void op_DXYN(chip8 *c, uint16_t X, uint16_t Y, uint16_t N)
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
