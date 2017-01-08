#include <TVout.h>
//#include <font4x6.h>
#include <avr/pgmspace.h>
#include "sound.h"

const uint8_t PROGMEM bootlogo[] = {
	0xF0, 0x01, 0x81, 0x8F, 0x8F, 0x3E, 0x60,
	0xD8, 0x01, 0x83, 0xCC, 0xD9, 0xB3, 0xD0,
	0xD8, 0x01, 0x86, 0x6C, 0xD9, 0xB3, 0xB0,
	0xDB, 0xDD, 0x87, 0xEF, 0x99, 0xBF, 0x60,
	0xDE, 0xF1, 0x86, 0x6C, 0xD9, 0xB6, 0x00,
	0xDE, 0xFD, 0x86, 0x6C, 0xD9, 0xB3, 0x00,
	0xDE, 0xCD, 0x86, 0x6C, 0xD9, 0xB3, 0x00,
	0xF3, 0xF9, 0xF6, 0x6F, 0x8F, 0x33, 0x00
};

TVout TV;

unsigned long nextmillis = 0;

void boot_logo() {
	uint8_t frame = 0;
	do {
		if(TV.millis() > nextmillis) {
			nextmillis = TV.millis() + 30;
			frame++;
			if(frame < 8+8) {
				TV.fill(BLACK);
				for(uint8_t y = 0; y < frame-8; y++) {
					for(uint8_t x = 0; x < 7; x++) {
						TV.screen[5+y*16+x] = pgm_read_byte(&(bootlogo[49+(y-frame+9)*7+x]));
					}
				}
			} else if(frame < 8+8+44) {
				TV.fill(BLACK);
				for(uint8_t y = 0; y < 8; y++) {
					for(uint8_t x = 0; x < 7; x++) {
						TV.screen[5+(y+frame-7-8)*16+x] = pgm_read_byte(&(bootlogo[y*7+x]));
					}
				}
			} else if(frame == 8+8+44) {
				play_note_ch1(38, 255, 90, -10, 0);
			} else if(frame == 8+8+44+2) {
				play_note_ch1(47, 255, 90, -6, 0);
			}
		}
	} while(frame < 128);
	TV.fill(BLACK);
}

void draw_sprite(uint8_t x, uint8_t y, const uint8_t *sprite, uint8_t width, uint8_t height) {
	uint16_t offset = (uint16_t)y*16+(uint16_t)x;
	for(; height != 0; height--) {
		for(uint8_t xp = 0; xp < width; xp++) {
			TV.screen[offset+xp] = pgm_read_byte(sprite);
			sprite++;
		}
		offset += 16;
	}
}

/*

0 C X X X X X X X X X X X X X X C0
1 D X X X X X X X X X X X X X X C1
2 X X X X X X X X X X X X X X X .
3 X X X X X X X X X X X X X X X .
X X X X X X X X X X X X X X X X .
X X X X X X X X X X X X X X X X .
X X X X X X X X X X X X X X X X .
X X X X X X X X X X X X X X X X .
X X X X X X X X X X X X X X X X .
X X X X X X X X X X X X X X X X .
A X X X X X X X X X X X X X X BE CA
B X X X X X X X X X X X X X X BF CB

*/

uint8_t bg_tiles[204];

const uint8_t PROGMEM tutorial_level[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x20, 0x21,
	0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
	0x00, 0x02, 0x00, 0x00, 0x14, 0x30, 0x34, 0x37, 0x37, 0x37, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x31, 0x35, 0x3b, 0x38, 0x3a, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x32, 0x3b, 0x35, 0x39, 0x37, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x14, 0x33, 0x36, 0x3a, 0x3a, 0x3a, 0x20, 0x21,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x21,
};

const uint8_t PROGMEM castle_level[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27, 0x27, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27, 0x27, 0x27,
	0x00, 0x00, 0x18, 0x19, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27, 0x27, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27, 0x27, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x19, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x1a, 0x1b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x19, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27, 0x27, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27, 0x27, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27, 0x27, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27, 0x27, 0x27,
	0x00, 0x00, 0x18, 0x19, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27, 0x27, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27, 0x27, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27, 0x27, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27, 0x27, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x19, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x1a, 0x1b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x19, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x19, 0x00, 0x00, 0x26, 0x27, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27, 0x27,
	0x00, 0x1a, 0x1b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x18, 0x19, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27, 0x27,
	0x00, 0x00, 0x18, 0x19, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27, 0x27, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27, 0x27, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27, 0x27, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27, 0x27, 0x27, 0x27,
	0x00, 0x18, 0x19, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27, 0x27, 0x27, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27, 0x27, 0x27, 0x27, 0x27, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x1a, 0x1b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x1a, 0x1b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2c, 0x2d, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x3d, 0x26, 0x27,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x27,
};

const uint8_t PROGMEM tileset[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // tile 0
	0x00, 0x18, 0x25, 0x42, 0x40, 0x20, 0x18, 0x07,  // tile 1
	0x00, 0xE0, 0x10, 0x18, 0x24, 0x04, 0x08, 0xF0,  // tile 2
	0x01, 0x02, 0x0C, 0x12, 0x10, 0x08, 0x07, 0x00,  // tile 3
	0xC0, 0x38, 0x24, 0x42, 0x02, 0x04, 0xF8, 0x00,  // tile 4
	0x00, 0x18, 0x25, 0x43, 0x40, 0x20, 0x1F, 0x00,  // tile 5
	0x6C, 0x92, 0x09, 0x01, 0x21, 0x51, 0x92, 0x0C,  // tile 6
	0x18, 0x34, 0x2C, 0x34, 0x2C, 0x34, 0x2C, 0x34,  // tile 7
	0x00, 0x00, 0x18, 0x24, 0x24, 0x18, 0x00, 0x00,  // tile 8
	0x00, 0x00, 0x1F, 0x20, 0x20, 0x1F, 0x00, 0x00,  // tile 9
	0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00,  // tile 10
	0x00, 0x00, 0xF8, 0x04, 0x04, 0xF8, 0x00, 0x00,  // tile 11
	0x00, 0x00, 0x18, 0x3C, 0x3C, 0x18, 0x00, 0x00,  // tile 12
	0x00, 0x00, 0x1F, 0x3F, 0x3F, 0x1F, 0x00, 0x00,  // tile 13
	0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,  // tile 14
	0x00, 0x00, 0xF8, 0xFC, 0xFC, 0xF8, 0x00, 0x00,  // tile 15
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // tile 16
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18,  // tile 17
	0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x14, 0x18,  // tile 18
	0x00, 0x00, 0x00, 0x18, 0x14, 0x18, 0x10, 0x10,  // tile 19
	0x00, 0x18, 0x14, 0x18, 0x10, 0x10, 0x10, 0x10,  // tile 20
	0x14, 0x18, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,  // tile 21
	0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,  // tile 22
	0x3C, 0x4A, 0xA5, 0x93, 0xC9, 0xA5, 0x93, 0xC9,  // tile 23
	0x18, 0x24, 0x5A, 0x42, 0xA5, 0x81, 0x99, 0x81,  // tile 24
	0xA5, 0x81, 0x99, 0x81, 0xA5, 0x81, 0x99, 0xFF,  // tile 25
	0x14, 0x14, 0x08, 0x08, 0x14, 0x14, 0x08, 0x08,  // tile 26
	0x14, 0x55, 0x14, 0x49, 0x55, 0x2A, 0x14, 0x00,  // tile 27
	0x00, 0x00, 0x24, 0x7E, 0x7E, 0x3C, 0x18, 0x00,  // tile 28
	0x00, 0x00, 0x24, 0x7A, 0x72, 0x34, 0x18, 0x00,  // tile 29
	0x00, 0x00, 0x24, 0x5A, 0x42, 0x24, 0x18, 0x00,  // tile 30
	0x00, 0x00, 0xFF, 0xF5, 0xFB, 0xF5, 0x00, 0x00,  // tile 31
	0xFF, 0x00, 0xFF, 0x00, 0x44, 0x00, 0x11, 0x00,  // tile 32
	0x44, 0x00, 0x11, 0x00, 0x44, 0x00, 0x11, 0x00,  // tile 33
	0x7E, 0x81, 0x81, 0x91, 0x89, 0x81, 0x81, 0x7E,  // tile 34
	0x7F, 0x80, 0x7F, 0x80, 0xAA, 0x95, 0x80, 0x7F,  // tile 35
	0xFF, 0x00, 0xFF, 0x00, 0xAA, 0x55, 0x00, 0xFF,  // tile 36
	0xFE, 0x01, 0xFE, 0x01, 0xA9, 0x55, 0x01, 0xFE,  // tile 37
	0xFF, 0x03, 0x03, 0xFF, 0x00, 0x10, 0x10, 0xF7,  // tile 38
	0x00, 0x02, 0x02, 0xFE, 0x00, 0x10, 0x10, 0xF7,  // tile 39
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // tile 40
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // tile 41
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // tile 42
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // tile 43
	0x07, 0x18, 0x23, 0x4F, 0x59, 0x9D, 0xA7, 0xB3,  // tile 44
	0xB9, 0xAD, 0xA7, 0xB3, 0xB9, 0xAD, 0xA7, 0xB3,  // tile 45
	0x07, 0x18, 0x23, 0x4C, 0x50, 0x90, 0xA0, 0xA0,  // tile 46
	0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0, 0xA0,  // tile 47
	0x7C, 0x44, 0x57, 0x40, 0x5B, 0x40, 0x5E, 0x40,  // tile 48
	0x7C, 0x44, 0xD7, 0x00, 0xBB, 0x00, 0xEE, 0x00,  // tile 49
	0x7C, 0x44, 0xD7, 0x00, 0xBB, 0x00, 0xEE, 0x00,  // tile 50
	0x7C, 0x44, 0xD4, 0x04, 0xB4, 0x04, 0xF4, 0x04,  // tile 51
	0x5B, 0x40, 0x7A, 0x08, 0x0B, 0x08, 0x0A, 0x08,  // tile 52
	0xBB, 0x00, 0xEE, 0x00, 0xBB, 0x00, 0xEE, 0x00,  // tile 53
	0xB4, 0x04, 0xBC, 0x20, 0xA0, 0x20, 0xA0, 0x20,  // tile 54
	0x0B, 0x08, 0x0A, 0x08, 0x0B, 0x08, 0x0A, 0x08,  // tile 55
	0xBB, 0x00, 0xE3, 0x0C, 0xD0, 0x10, 0xA0, 0x20,  // tile 56
	0xBB, 0x00, 0x8E, 0x60, 0x17, 0x10, 0x0A, 0x08,  // tile 57
	0xA0, 0x20, 0xA0, 0x20, 0xA0, 0x20, 0xA0, 0x20,  // tile 58
	0xBB, 0x00, 0xBA, 0x28, 0xBB, 0x00, 0xEE, 0x00,  // tile 59
	0xC0, 0x30, 0x88, 0xE4, 0x74, 0x32, 0x9A, 0xCA,  // tile 60
	0x6A, 0x3A, 0x9A, 0xCA, 0x6A, 0x3A, 0x9A, 0xCA,  // tile 61
	0xC0, 0x30, 0x88, 0x64, 0x14, 0x12, 0x0A, 0x0A,  // tile 62
	0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A,  // tile 63
};

const uint8_t PROGMEM wizard[] = {
	0x30, 0x58, 0xAC, 0xD6, 0xAC, 0xE5, 0xD9, 0xB9, // frame 0
	0x6E, 0x56, 0x6C, 0x54, 0x7C, 0x54, 0x7C, 0x28,
	0x00, 0x30, 0x58, 0xAC, 0xD6, 0xAC, 0xE5, 0xF9, // frame 1
	0xED, 0x56, 0x6E, 0x54, 0x7C, 0x54, 0x7C, 0x14,
	0x30, 0x58, 0xAC, 0xD6, 0xAC, 0xE4, 0xD9, 0xB9, // frame 2
	0x6F, 0x56, 0x6C, 0x54, 0x7C, 0x54, 0x7C, 0x48,
};

const uint8_t PROGMEM wizard_mask[] = {
	0x30, 0x78, 0xFC, 0xFE, 0xFC, 0xFD, 0xD9, 0xB9, // frame 0
	0x7E, 0x7E, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x28,
	0x00, 0x30, 0x78, 0xFC, 0xFE, 0xFC, 0xFD, 0xF9, // frame 1
	0xFD, 0x7E, 0x7E, 0x7C, 0x7C, 0x7C, 0x7C, 0x14,
	0x30, 0x78, 0xFC, 0xFE, 0xFC, 0xFC, 0xD9, 0xB9, // frame 2
	0x7F, 0x7E, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x48,
};

const uint8_t PROGMEM dragon[] = {
	0x03, 0xD8, 0x00, 0x06, 0x26, 0x00, 0x1D, 0x18, 
	0x00, 0x66, 0x08, 0x00, 0x90, 0x44, 0x00, 0xEF, 
	0x23, 0x20, 0x38, 0x92, 0x50, 0x00, 0x82, 0x88, 
	0x00, 0x41, 0x88, 0x20, 0x50, 0x64, 0x18, 0x44, 
	0x14, 0x64, 0x94, 0x0A, 0x1A, 0xA0, 0x46, 0x05, 
	0x20, 0x22, 0x43, 0x44, 0x12, 0x3E, 0x48, 0x09, 
	0x3A, 0x48, 0x65, 0x46, 0x40, 0x91, 0x01, 0x20, 
	0x49, 0x01, 0x14, 0x65, 0x01, 0x12, 0x31, 0x00, 
	0x91, 0x29, 0x00, 0x41, 0x15, 0x00, 0x40, 0x9B, 
	0x0F, 0xC0, 0x88, 0x1A, 0xA4, 0x08, 0x12, 0x10, 
	0xC4, 0x0F, 0xF9, 0x42, 0x00, 0x31, 0x32, 0x00, 
	0x42, 0x19, 0x00, 0x8C, 0x22, 0x00, 0xF0, 0x3C, 
	0x01, 0xEC, 0x00, 0x03, 0x13, 0x00, 0x0E, 0x8C, 
	0x00, 0x33, 0x04, 0x00, 0x48, 0x22, 0x80, 0x77, 
	0x91, 0x20, 0x1C, 0x49, 0x50, 0x00, 0x41, 0x88, 
	0x00, 0x41, 0x88, 0x00, 0x50, 0x64, 0x00, 0x44, 
	0x14, 0x00, 0x94, 0x0A, 0x00, 0x90, 0x46, 0x71, 
	0x20, 0x22, 0x2F, 0x22, 0x12, 0x5E, 0x24, 0x09, 
	0x02, 0x24, 0x65, 0x06, 0x20, 0x91, 0x1B, 0x20, 
	0x49, 0x25, 0x14, 0x65, 0x19, 0x12, 0x31, 0x60, 
	0x91, 0x29, 0x00, 0x41, 0x15, 0x00, 0x40, 0x9B, 
	0x0F, 0xE0, 0x88, 0x1A, 0x54, 0x08, 0x12, 0x18, 
	0x04, 0x0F, 0xF9, 0x42, 0x00, 0x2D, 0x32, 0x00, 
	0x19, 0x09, 0x00, 0x13, 0x05, 0x00, 0x0E, 0x03, 
	0x7F, 0xFF, 0xFF, 0xD0, 0x10, 0x0A, 0x90, 0x28, 
	0x04, 0x7F, 0xFF, 0xFF,
};

const uint8_t PROGMEM spider[] = {
	0xD4, 0xA8, 0xC1, 0xAA, 0xD4, 0xA8, 0x81, 0x55,
};

const uint8_t PROGMEM logo[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x14, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x35, 0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x26, 0xA6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x34, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xC1, 0x80, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xA2, 0x80, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x94, 0x80, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x88, 0x80, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xA2, 0xBC, 0xF1, 0xD7, 0x79, 0xFB, 0xCF, 0x00, 0x00, 
	0xB6, 0xA4, 0x92, 0x51, 0x45, 0x4A, 0x49, 0x00, 0x00, 
	0xAA, 0xA4, 0x94, 0xD7, 0x55, 0x1A, 0x49, 0x00, 0x00, 
	0xA2, 0x93, 0x25, 0x94, 0x85, 0x61, 0x32, 0x00, 0x00, 
	0xA2, 0x88, 0x44, 0x54, 0xB9, 0x40, 0x84, 0x44, 0x00, 
	0xA2, 0x87, 0x5F, 0x56, 0x9D, 0x40, 0x74, 0xAA, 0x00, 
	0xA2, 0x83, 0x50, 0x52, 0xC5, 0x40, 0x34, 0xA8, 0x80, 
	0xE3, 0x82, 0x5F, 0x8E, 0x7D, 0xC0, 0x24, 0x51, 0x22, 
	0x00, 0x04, 0x80, 0x00, 0x00, 0x00, 0x48, 0x19, 0xB5, 
	0x27, 0xFD, 0x00, 0x00, 0x02, 0x7F, 0x90, 0x62, 0x2F, 
	0x87, 0x02, 0x00, 0x00, 0x08, 0x70, 0x20, 0x02, 0x4C, 
	0x27, 0xFC, 0x00, 0x00, 0x02, 0x7F, 0xC0, 0x01, 0x52, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 0x00, 
	0x00, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x00, 
	0x00, 0x55, 0x71, 0xC3, 0x87, 0x1D, 0xFC, 0x55, 0x00, 
	0x00, 0x22, 0x71, 0xC7, 0xC7, 0x1D, 0xFE, 0x22, 0x00, 
	0x00, 0x00, 0x71, 0xCF, 0xE7, 0x1D, 0xCF, 0x00, 0x00, 
	0x00, 0x00, 0x71, 0xDE, 0xF7, 0x9D, 0xC7, 0x00, 0x00, 
	0x00, 0x00, 0x71, 0xDC, 0x77, 0xDD, 0xC7, 0x00, 0x00, 
	0x00, 0x00, 0x71, 0xDC, 0x77, 0xFD, 0xC7, 0x00, 0x00, 
	0x00, 0x00, 0x75, 0xDF, 0xF7, 0x7D, 0xC7, 0x00, 0x00, 
	0x00, 0x00, 0x7F, 0xDF, 0xF7, 0x3D, 0xC7, 0x00, 0x00, 
	0x00, 0x00, 0x7F, 0xDC, 0x77, 0x1D, 0xC7, 0x00, 0x00, 
	0x00, 0x00, 0x7F, 0xDC, 0x77, 0x1D, 0xCF, 0x00, 0x00, 
	0x00, 0x00, 0x7B, 0xDC, 0x77, 0x1D, 0xFE, 0x00, 0x00, 
	0x00, 0x00, 0x71, 0xDC, 0x77, 0x1D, 0xFC, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const uint8_t jump[] = {
	1, 2, 4, 7, 7, 7
};

/* scroll_x: between 0 and 8 (inclusive)
   0 means, that the first tile is fully visible on the left side of the screen
   8 means, that the last tile is fully visible on the right side of the screen
   values in between mean, that parts of first and last row are visible */
void draw_bg(uint8_t scroll_x) {
	for(uint8_t y = 0; y < 12; y++) {
		for(uint8_t i = 0; i < 8; i++) {
			uint8_t line, nextline = pgm_read_byte(&tileset[bg_tiles[y*17]*8+i]);
			for(uint8_t x = 0; x < 16; x++) {
				line = nextline;
				nextline = pgm_read_byte(&tileset[bg_tiles[x+y*17+1]*8+i]);
				if (scroll_x == 8) {
					line = nextline;
				} else if (scroll_x > 0) {
					line = (line << scroll_x) | (nextline >> (8-scroll_x));
				}
				TV.screen[((y*8+i)*16+x)] = line;
			}
		}
	}
}

uint8_t frame_counter;

void draw_object(const uint8_t *object, const uint8_t *mask,
	const uint8_t number_frames, uint8_t xoff, uint8_t y,
	uint8_t width, uint8_t height) {
	uint8_t offset = (frame_counter % number_frames)*width*height;
	uint8_t ymax = y + height;
	for(; y < ymax; y++) {
		uint8_t nextline, nextmaskline, line = 0, maskline = 0;
		for(uint8_t x = 0; x < width; x++) {
			nextline = pgm_read_byte(&object[offset]);
			nextmaskline = (mask == NULL ? 0 : pgm_read_byte(&mask[offset]));
			if(xoff % 8 != 0) {
				line |= (nextline >> (xoff % 8));
				maskline |= (nextmaskline >> (xoff % 8));
				TV.screen[(y*16)+xoff/8+x] = (TV.screen[(y*16)+xoff/8+x] & ~maskline) | line;
				line = (nextline << (8 - (xoff % 8)));
				maskline = (nextmaskline << (8 - (xoff % 8)));
			} else {
				line = nextline;
				maskline = nextmaskline;
				TV.screen[(y*16)+xoff/8+x] = (TV.screen[(y*16)+xoff/8+x] & ~maskline) | line;
			}
			offset++;
		}
		if(xoff % 8 != 0) {
			TV.screen[(y*16)+xoff/8+width] = (TV.screen[(y*16)+xoff/8+width] & ~maskline) | line;
		}
	}
}

void shiftleft_bg_tiles(const uint8_t **nextcolumn) {
	for(uint8_t x = 0; x < 16; x++) {
		for(uint8_t y = 0; y < 12; y++) {
			bg_tiles[y*17+x] = bg_tiles[y*17+x+1];
		}
	}
	for(uint8_t y = 0; y < 12; y++) {
		bg_tiles[y*17+16] = pgm_read_byte((*nextcolumn)++);
	}
}

uint8_t level_scroll_x;
const uint8_t *level_scroll_data;
uint8_t row_counter;

#define FLAG_COUNT_FRAMES 1
#define FLAG_WAIT_BUTTONUP 2
#define FLAG_PC_FALLING 4
#define FLAG_INPUT_SEQUENCE 8
#define FLAG_LEVEL_SCROLLS 16
#define FLAG_GAME_PAUSED 32
uint8_t flags = 0;
uint8_t player_jump = 0, player_xpos, player_ypos, player_fall = 0;

#define TOP_COLLISION 1
#define RIGHT_COLLISION 2
#define BOTTOM_COLLISION 4

void load_level(const uint8_t *level) {
	level_scroll_data = level;
	level_scroll_x = 0;
	row_counter = 0;
	for(uint8_t x = 0; x <= 16; x++) {
		for(uint8_t y = 0; y < 12; y++) {
			bg_tiles[y*17+x] = pgm_read_byte(level_scroll_data++);
		}
	}
	player_xpos = 16;
	player_ypos = 96;
	for(int8_t y = 11; y >= 0; y--) {
		player_ypos = y*8+8;
		if(!(bg_tiles[y*17+2] & 0x20)) {
			break;
		}
	}
}

void scroll_level(uint8_t amount) {
	level_scroll_x += amount;
	while(level_scroll_x >= 8) {
		level_scroll_x -= 8;
		shiftleft_bg_tiles(&level_scroll_data);
		row_counter++;
	}
}

uint8_t bg_collisions() {
	// which bg-tile is possibly colliding with the character?
	// player_ypos = baseline of character (pixels from top)
	// 16 = height of character (in pixels)
	// player_xpos = left position of character (pixels from left)
	// 8 = width of character (in pixels)
	// level_scroll_x = amount of pixels scrolled to the left (i.e. 8-level_scroll_x pixels of the first column are visible)

	//  v- first column (scrolled)
	// ----+------++------++------+
	//     |      ||      ||      |
	//     |      ||      ||      |
	//     |      ||      ||      |
	// ----+------++------++------+
	//     |      || v- player character
	//     |   +------+   ||      |
	//     |   |      |   ||      |
	// ----+---|      |---++------+

	// The player can be positioned in either one or two (like in the picture) columns
	// collisions can occur
	//  - while jumping (to the ceiling) -> collides with one / two of the tiles which are upmost covering the player
	//  - while running (to the right) -> collides with 1-3 of the tiles covering the player on the right side
	//  - while falling (to the bottom)
	//    -> collides with one / two of the tiles which are most bottom covering the player
	//    -> collides with the ground (line 96)
	uint8_t collisions = 0;
	uint8_t coll_tile = (player_ypos/8-3)*17+(player_xpos+level_scroll_x)/8;
	uint8_t top_collision = 0;
	uint8_t multitile = (player_xpos+level_scroll_x) % 8 ? 1 : 0;
	if(player_ypos % 8 == 1) {
		top_collision |= bg_tiles[coll_tile];
	}
	coll_tile += 17;
	if(top_collision & 0x20) {
		collisions |= TOP_COLLISION;
	}

	uint8_t right_collision = 0;
	if((player_xpos+level_scroll_x)%8 == 0) {
		right_collision |= bg_tiles[coll_tile+1+multitile] | bg_tiles[coll_tile+17+1+multitile];
		if(player_ypos % 8) {
			right_collision |= bg_tiles[coll_tile+2*17+1+multitile];
		}
	}
	if(right_collision & 0x20) {
		collisions |= RIGHT_COLLISION;
	}

	coll_tile += 2*17;
	if(player_ypos % 8) {
		coll_tile += 17;
	}
	uint8_t bottom_collision = 0;
	if(player_ypos % 8 == 0) {
		bottom_collision |= bg_tiles[coll_tile];
		if(multitile) {
			bottom_collision |= bg_tiles[coll_tile+1];
		}
		if(bottom_collision & 0x20) {
			collisions |= BOTTOM_COLLISION;
		}
	}
	return collisions;
}

const uint8_t *level_tiles[] = {tutorial_level, castle_level};
const uint8_t level_widths[] = {72, 72};
const uint8_t spiders_per_level[][3] = {{54}, {9, 36}};

void start_screen() {
	load_level(level_tiles[0]);
	bg_tiles[8*17+4] = 8; // 4,8: tile[8]
	draw_bg(0);
	draw_sprite(4, 2*8, logo, 9, 5*8); // 4,2: logo
	// 6,8: Text "START"
	while(PINB & (1 << PB4)) {
		nextmillis = TV.millis() + 15;
		while(TV.millis() < nextmillis) {
			// busy wait loop
		}
	}
	bg_tiles[8*17+4] = 12;
	draw_bg(0);
	draw_sprite(4, 2*8, logo, 9, 5*8); // 4,2: logo
	// 6,8: Text "START"
	while(!(PINB & (1 << PB4))) {
		nextmillis = TV.millis() + 15;
		while(TV.millis() < nextmillis) {
			// busy wait loop
		}
	}
	nextmillis = TV.millis() + 15;
	while(TV.millis() < nextmillis) {
		// busy wait loop
	}
}

void serialPrintChar(char chr) {
	while(!(UCSR0A & (1 << UDRE0))) {
		// ...
	}
    UDR0 = chr;
}

void serialPrint(const char* str) {
	while(*str != '\0') {
		serialPrintChar(*(str++));
	}
}

void serialPrintNumber(uint16_t n) {
	char buf[16];
	char *bufptr = buf+15;
	*bufptr = '\0';
	do {
		*(--bufptr) = '0' + (n%10);
		n=n/10;
	} while(n > 0);
	serialPrint(bufptr);
	serialPrint("\r\n");
}

uint8_t current_level;

int main() {
	sound_init();
	TV.begin(_PAL, 128, 96);
	TV.set_hbi_hook(&vblank_sound);
	DDRB |= (1 << PB4); // button input
	PORTB |= (1 << PB4);

	nextmillis = TV.millis() + 1000;
	while(TV.millis() < nextmillis) {
		// busy wait loop
	}

	//TV.draw_rect(0, 0, 127, 95, 1, -1);
	//TV.select_font(font4x6);
	//TV.print(2, 2, "Hello World!");

	//boot_logo();
	unsigned long lastpress;
	uint8_t store_flags, input_seq = 0;
	while(1) {
		current_level = 0;
		start_screen();
		while(1) {
			load_level(level_tiles[current_level]);
			frame_counter = 0;
			uint8_t spiders_in_level[3];
			int8_t active_spider_positions[3], active_spider_direction[3];
			for(uint8_t i = 0; i < 3; i++) {
				spiders_in_level[i] = spiders_per_level[current_level][i];
				active_spider_positions[i] = 0;
			}
			flags |= FLAG_COUNT_FRAMES;
			while(1) {
				/*while(!(UCSR0A & (1 << RXC0))) {
					// wait for one char
				}
				uint8_t input = UDR0;
				serialPrint("PY=");serialPrintNumber(player_ypos);
				serialPrint("PX=");serialPrintNumber(player_xpos);
				serialPrint("PJ=");serialPrintNumber(player_jump);
				serialPrint("PF=");serialPrintNumber(player_fall);*/
				if(!(flags & (FLAG_INPUT_SEQUENCE)) && !(PINB & (1 << PB4))) {
					// input sequence started
					store_flags = flags;
					flags = FLAG_INPUT_SEQUENCE | FLAG_GAME_PAUSED;
				}
				if(flags & FLAG_INPUT_SEQUENCE) {
					if(flags & FLAG_WAIT_BUTTONUP && (PINB & (1 << PB4))) {
						input_seq <<= 2;
						if(TV.millis() - lastpress < 200) {
							input_seq |= 1;
						} else {
							input_seq |= 2;
						}
						flags &= ~FLAG_WAIT_BUTTONUP;
						lastpress = TV.millis();
					} else if(!(flags & FLAG_WAIT_BUTTONUP)) {
						if(PINB & (1 << PB4)) {
							// button up... check for how long
							if(TV.millis() - lastpress > 150 || input_seq & 0xC0) {
								flags = store_flags;
								if(input_seq == 0x01) {
									if(!(flags & FLAG_PC_FALLING) && player_jump == 0) {
										player_jump = 6;
									}
								} else if(input_seq == 0xC1) {
									// shoot!!
								}
								input_seq = 0;
							}
						} else {
							lastpress = TV.millis();
							flags |= FLAG_WAIT_BUTTONUP;
						}
					}
				}
				if(!(flags & FLAG_GAME_PAUSED)) {
					uint8_t collisions;
					if(player_jump > 0) {
						player_ypos -= jump[--player_jump];
						collisions = bg_collisions();
						// if collision (on head), set player_jump to 0 and player_ypos accordingly. else:
						if(collisions & TOP_COLLISION) {
							player_jump = 0;
							player_ypos = ((player_ypos/8)+1)*8;
							// TODO: sound (ughh, hit a ceiling)
						}
					} else {
						collisions = bg_collisions();
					}
					if(collisions & RIGHT_COLLISION) {
						flags &= ~FLAG_LEVEL_SCROLLS;
					} else {
						flags |= FLAG_LEVEL_SCROLLS;
					}
					//serialPrint("CO=");serialPrintNumber(collisions);
					// check whether there is a solid tile under the character... if not, player has to fall and can not jump while this
					if(!player_jump) {
						if(!(collisions & BOTTOM_COLLISION)) {
							flags |= FLAG_PC_FALLING;
							player_ypos += jump[player_fall];
							if(player_fall < 5) {
								player_fall++;
							}
							if(bg_tiles[(player_ypos/8-1)*17+(player_xpos+level_scroll_x)/8] & 0x20 || ((player_xpos+level_scroll_x) % 8 && bg_tiles[(player_ypos/8-1)*17+(player_xpos+level_scroll_x)/8+1] & 0x20)) {
								player_ypos -= (player_ypos%8)+8;
							}
							collisions = bg_collisions();
						}
						if(collisions & BOTTOM_COLLISION) {
							flags &= ~FLAG_PC_FALLING;
							player_fall = 0;
						}
					}
					if(player_ypos > 96) {
						player_ypos = 16;
					}
					// if there is a collision with an enemy
						// check whether the enemy is right under the character. if so, then hurt the enemy and let the player jump maybe
						// else hurt the player
					if(flags & FLAG_LEVEL_SCROLLS && level_scroll_x == 0) {
						for(uint8_t i = 0; i < 3; i++) {
							if(spiders_in_level[i] > 0)
								spiders_in_level[i]--;
						}
					}
					for(uint8_t i = 0; i < 3; i++) {
						if(active_spider_positions[i] == 0 && spiders_in_level[i] <= 15 && spiders_in_level[i] > 0) {
							active_spider_positions[i] = spiders_in_level[i]*8;
							active_spider_direction[i] = -1;
						}
						if(active_spider_positions[i] >= player_xpos && active_spider_positions[i] <= player_xpos + 7 && player_ypos >= 76 && player_ypos < 80+16) {
							/*if(flags & FLAG_PC_FALLING) {
								active_spider_positions[i] = 0; // spider dead (sound)
								spiders_in_level[i] = 0;
							} else {*/
							// game over!
							current_level = -1;
							break;
							//}
						}
					}
					if(current_level == 255) {
						break;
					}
				}
				draw_bg(level_scroll_x);
				uint8_t draw_input_seq = input_seq, draw_pos = 4;
				while(draw_input_seq != 0) {
					switch(draw_input_seq & (0xC0)) {
						case 0x40:
							draw_sprite(draw_pos++, 24, tileset+96, 1, 8);
							break;
						case 0x80:
							draw_sprite(draw_pos++, 24, tileset+104, 1, 8);
							draw_sprite(draw_pos++, 24, tileset+120, 1, 8);
							break;
						default:
							// nothing
							break;
					}
					draw_input_seq <<= 2;
				}
				if(flags & FLAG_GAME_PAUSED) {
					for(uint8_t i = 0; i < 3; i++) {
						if(active_spider_positions[i] != 0) {
							draw_object(spider, NULL, 2, active_spider_positions[i], 76, 1, 4);
						}
					}					
				} else {
					for(uint8_t i = 0; i < 3; i++) {
						if(active_spider_positions[i] != 0) {
							int8_t spider_walk = active_spider_direction[i] - (flags & FLAG_LEVEL_SCROLLS ? 1 : 0);
							if(active_spider_positions[i] + spider_walk <= 0) {
								active_spider_positions[i] = 0;
								spiders_in_level[i] = 0;
							} else {
								active_spider_positions[i] += spider_walk;
								if(bg_tiles[9*17+(active_spider_positions[i]+level_scroll_x)/8+(active_spider_direction[i]+1)/2] & 0x20) {
									active_spider_positions[i] -= spider_walk;
									active_spider_direction[i] = -active_spider_direction[i];
								}
								draw_object(spider, NULL, 2, active_spider_positions[i], 76, 1, 4);
							}
						}
					}
					if(row_counter < level_widths[current_level]-16) {
						if(flags & FLAG_LEVEL_SCROLLS) {
							scroll_level(1);
						}
						player_xpos = 16;
					} else if(player_xpos < 128-28) {
						player_xpos++;
					} else {
						flags &= ~FLAG_COUNT_FRAMES;
						frame_counter = 0;
						break;
					}
				}
				draw_object(wizard, wizard_mask, sizeof(wizard)/16, player_xpos, player_ypos-16, 1, 16);
				if(flags & FLAG_COUNT_FRAMES) {
					frame_counter++;
				}
				nextmillis += 50;
				while(TV.millis() < nextmillis) {
					// busy wait loop
				}
			}
			// TODO: level completed melody
			nextmillis += 1000;
			while(TV.millis() < nextmillis) {
				// busy wait loop
			}
			if(current_level == 0) {
				current_level++;
			} else {
				break;
			}
		}
	}

	return 0;
}