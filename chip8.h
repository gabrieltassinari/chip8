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
	uint8_t V[16];

	// Keypad
	uint8_t keypad[16];

	// COSMAC VIP/Super-chip option
	int cosmac_vip;
} chip8;

uint16_t fetch(chip8 *c);
void draw_scr(chip8 *c);
void decode(chip8 *c, uint16_t opcode);
int load_rom(chip8 *c, const char *path);
int init_chip8(chip8 *c, const char *path);

// Opcodes
void op_00E0(chip8 *c);
void op_00EE(chip8 *c);
void op_1NNN(chip8 *c, uint16_t NNN);
void op_2NNN(chip8 *c, uint16_t NNN);
void op_3XNN(chip8 *c, uint16_t X, uint16_t NN);
void op_4XNN(chip8 *c, uint16_t X, uint16_t NN);
void op_5XY0(chip8 *c, uint16_t X, uint16_t Y);
void op_6XNN(chip8 *c, uint16_t X, uint16_t NN);
void op_7XNN(chip8 *c, uint16_t X, uint16_t NN);
void op_8XY0(chip8 *c, uint16_t X, uint16_t Y);
void op_8XY1(chip8 *c, uint16_t X, uint16_t Y);
void op_8XY2(chip8 *c, uint16_t X, uint16_t Y);
void op_8XY3(chip8 *c, uint16_t X, uint16_t Y);
void op_8XY4(chip8 *c, uint16_t X, uint16_t Y);
void op_8XY5(chip8 *c, uint16_t X, uint16_t Y);
void op_8XY6(chip8 *c, uint16_t X, uint16_t Y);
void op_8XY7(chip8 *c, uint16_t X, uint16_t Y);
void op_8XYE(chip8 *c, uint16_t X, uint16_t Y);
void op_9XY0(chip8 *c, uint16_t X, uint16_t Y);
void op_ANNN(chip8 *c, uint16_t NNN);
void op_BNNN(chip8 *c, uint16_t X, uint16_t NNN);
void op_CXNN(chip8 *c, uint16_t X, uint16_t NN);
void op_DXYN(chip8 *c, uint16_t X, uint16_t Y, uint16_t N);
void op_EX9E(chip8 *c, uint16_t X);
void op_EXA1(chip8 *c, uint16_t X);
void op_FX07(chip8 *c, uint16_t X);
void op_FX15(chip8 *c, uint16_t X);
void op_FX18(chip8 *c, uint16_t X);
void op_FX1E(chip8 *c, uint16_t X);
void op_FX0A(chip8 *c, uint16_t X);
void op_FX29(chip8 *c, uint16_t X);
void op_FX33(chip8 *c, uint16_t X);
void op_FX55(chip8 *c, uint16_t X);
void op_FX65(chip8 *c, uint16_t X);
