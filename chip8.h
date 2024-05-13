#include <stdint.h>

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
	uint16_t stack[4];

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
