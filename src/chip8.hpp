#include <stdint.h>
#include <chrono>
#include <random>
#include <string.h>

class CPU{

	public:
		CPU(const char * filename);
		void LoadROM(char const* filename);
		void decode();
		void Cycle();
		void OP_00E0();
		void OneNNN();
		void SIXXNN();
		void SevenXNN();
		void ANNN();
		void DXYN();
    void OP_00EE();
    void OP_2NNN();
    void OP_3XNN();
    void OP_4XNN();
    void OP_5XY0();
    void OP_9XY0();
    void OP_8XY0();
    void OP_8XY1();
    void OP_8XY2();
    void OP_8XY3();
    void OP_8XY4();
    void OP_8XY5();
    void OP_8XY7();
    void OP_8XY6();
    void OP_8XYE();
    void OP_BNNN();
    void OP_CXNN();
    void OP_EX9E();
    void OP_FX07();
    void OP_FX15();
    void OP_FX18();
    void OP_FX1E();
    void OP_FX0A();
    void OP_FX29();
    void OP_FX33();
    void OP_FX55();
    void OP_FX65();
    void OP_EXA1();

			
		uint8_t fontset[80] = { 0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
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

		const uint8_t MAX_WIDTH = 64;
		const uint8_t MAX_HEIGHT = 32;

		std::uniform_int_distribution<uint8_t> randByte;
			//input keys and display memory
		uint8_t input[16]{};
		uint32_t video_buffer[64*32];
			
		uint8_t timer;
		uint8_t soundtimer;
    uint8_t key;
			/*registers,memory,stack,stack_pointer,program_counter
				delaytimer,soundtimer,opcodes			*/
	 private:		
		uint8_t registers[16];
		uint8_t memory[4096];
		uint16_t index_register;
		uint16_t pc;
		uint16_t stack[16];
		uint8_t sp;
		uint16_t opcode;
    char const* romFilename;

};




