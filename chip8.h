#include <stdint.h>
#include "stack.h"

#define HEIGHT 32
#define WIDTH 64

enum hex { A = 10, B, C, D, E, F };

// Emulator
typedef struct chip8 {
	// Memory + Screen
	uint8_t mem[4096];
	uint8_t scr[HEIGHT][WIDTH];

	// Program Counter + Index
	uint16_t PC;
	uint16_t I;

	// Stack
	stack *stack;

	// {Delay,Sound} Timer
	uint8_t DT;
	uint8_t ST;

	// Variable registers
	uint16_t V[16];
} chip8;

uint16_t fetch(chip8 *c);
void decode(chip8 *c, uint16_t opcode);
int load_rom(chip8 *c, const char *path);
void draw_scr(chip8 *c);

// Opcodes
void op_00E0(chip8 *c);
void op_00EE(chip8 *c);
void op_1NNN(chip8 *c, uint16_t NNN);
void op_2NNN(chip8 *c, uint16_t NNN);
void op_3XNN(chip8 *c, uint16_t NN, uint16_t X);
void op_4XNN(chip8 *c, uint16_t NN, uint16_t X);
void op_5XY0(chip8 *c, uint16_t X, uint16_t Y);
void op_6XNN(chip8 *c, uint16_t NN, uint16_t X);
void op_7XNN(chip8 *c, uint16_t NN, uint16_t X);
void op_9XY0(chip8 *c, uint16_t X, uint16_t Y);
void op_ANNN(chip8 *c, uint16_t NNN);
void op_DXYN(chip8 *c, uint16_t N, uint16_t X, uint16_t Y);
