#include <stdint.h>
#include <chrono>
#include <random>
#include <string.h>
#include "chip8.hpp"


	void CPU::OP_00E0(){
			//clears screen (here we set video buffer to 0)
			memset(video_buffer,0,sizeof(video_buffer));
		}
		void CPU::OneNNN(){
			//gets the pc to jump to an address
			uint16_t address = opcode & 0x0FFFu; 
			pc = address;
		}
		void CPU::SIXXNN(){
			//sets register vx to a value
			uint8_t value = opcode & 0x00FF;
			uint8_t vx = (opcode & 0x0F00) >> 8;
			registers[vx] = value;
		}
		void CPU::SevenXNN(){
			//adds a value to register vx			
			uint8_t value = opcode & 0x00FF;
			uint8_t vx = (opcode & 0x0F00) >> 8;
			registers[vx] += value;
		};
		void CPU::ANNN(){
			uint16_t byte3 = opcode & 0x0FFF;
			index_register = byte3;
		};
		void CPU::DXYN(){
			uint8_t vx = (opcode & 0x0F00) >> 8;
			uint8_t vy = (opcode & 0x00F0) >> 4;
			uint8_t height = (opcode & 0x000F);

			uint8_t x_pos = registers[vx] % MAX_HEIGHT;
			uint8_t y_pos = registers[vy] % MAX_WIDTH;

			registers[15] = 0;

			for(int row=0; row<height; ++row){
				uint8_t spriteByte = memory[index_register + row];
				for(unsigned int col = 0; col < 8; ++col)
				{
					uint8_t spritepixel = spriteByte & (0x80 >> col);
					uint32_t * screenpixel = &video_buffer[(y_pos + row) * MAX_WIDTH + (x_pos + col)];
					// Sprite pixel is on
				if (spritepixel)
				{
				// Screen pixel also on - collision
				if (*screenpixel == 0xFFFFFFFF)
				{
					registers[0xF] = 1;
				}

				// Effectively XOR with the sprite pixel
				*screenpixel ^= 0xFFFFFFFF;
			}
		}
	


				}

			}
		
