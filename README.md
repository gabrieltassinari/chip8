# Chip-8 Emulator
This is a CHIP-8 emulator built following the [Tobias Guide](https://tobiasvl.github.io/blog/write-a-chip-8-emulator/) using the [raylib](https://www.raylib.com/) library.

## Running the emulator
1. Install the [raylib](https://www.raylib.com/) library using a package manager
```sh
$ dnf install raylib
$ pacman -S raylib
```
Or follow [this guide](https://github.com/raysan5/raylib?tab=readme-ov-file#build-and-installation)

2. Get a chip-8 ROM like the [IBM-logo](https://github.com/loktar00/chip8/raw/master/roms/IBM%20Logo.ch8)

3. Build and run
```sh
$ make
$ ./chip8 ibm.ch8
```
