#include "WS2812DisplayDriver.h"

//const uint8_t Display::font5by3[3][5][3];
//Display* Display:selfPointer;

Display::Display(CRGB ledDisplay[][DISPLAY_HEIGHT], CRGB leds[], bool invertDisplay){
	
	pLedDisplay = ledDisplay;
	pLeds = leds;
  inverted = invertDisplay;
	
	this->setStringColor({40,40,40});
		
	//----- Numbers -----
	this->dic[48] = 0; //0
	this->dic[49] = 1; //1
	this->dic[50] = 2; //2
	this->dic[51] = 3; //3
	this->dic[52] = 4; //4
	this->dic[53] = 5; //5
	this->dic[54] = 6; //6
	this->dic[55] = 7; //7
	this->dic[56] = 8; //8
	this->dic[57] = 9; //9
	
	//----- captial Letters -----
	this->dic[65] = 10; // A
	this->dic[66] = 11; // B
	this->dic[67] = 12; // C
	this->dic[68] = 13; // D
	this->dic[69] = 14; // E
	this->dic[70] = 15; // F
	this->dic[71] = 16; // G
	this->dic[72] = 17; // H
	this->dic[73] = 18; // I
	this->dic[74] = 19; // J
	this->dic[75] = 20; // K
	this->dic[76] = 21; // L
	this->dic[77] = 22; // M
	this->dic[78] = 23; // N
	this->dic[79] = 24; // O
	this->dic[80] = 25; // P
	this->dic[81] = 26; // Q
	this->dic[82] = 27; // R
	this->dic[83] = 28; // S
	this->dic[84] = 29; // T
	this->dic[85] = 30; // U
	this->dic[86] = 31; // V
	this->dic[87] = 32; // W
	this->dic[88] = 33; // X
	this->dic[89] = 34; // Y
	this->dic[90] = 35; // Z
	
	//----- small Letters -----
	this->dic[97] = 10; // a
	this->dic[98] = 11; // b
	this->dic[99] = 12; // c
	this->dic[100] = 13; // d
	this->dic[101] = 14; // e
	this->dic[102] = 15; // f
	this->dic[103] = 16; // g
	this->dic[104] = 17; // h
	this->dic[105] = 18; // i
	this->dic[106] = 19; // j
	this->dic[107] = 20; // k
	this->dic[108] = 21; // l
	this->dic[109] = 22; // m
	this->dic[110] = 23; // n
	this->dic[111] = 24; // o
	this->dic[112] = 25; // p
	this->dic[113] = 26; // q
	this->dic[114] = 27; // r
	this->dic[115] = 28; // s
	this->dic[116] = 29; // t
	this->dic[117] = 30; // u
	this->dic[118] = 31; // v
	this->dic[119] = 32; // w
	this->dic[120] = 33; // x
	this->dic[121] = 34; // y
	this->dic[122] = 35; // z
	
	//----- Symbols -----
	this->dic[32] = 36; // Space
	this->dic[44] = 37; // ,
	this->dic[46] = 38; // .
	this->dic[34] = 39; // "
	this->dic[63] = 40; // ?
	this->dic[33] = 41; // !
	this->dic[95] = 42; // _
	this->dic[42] = 43; // *
	this->dic[35] = 44; // #
	this->dic[36] = 45; // $
	this->dic[37] = 46; // %
	this->dic[38] = 47; // &
	this->dic[40] = 48; // (
	this->dic[41] = 49; // )
	this->dic[43] = 50; // +
	this->dic[45] = 51; // -
	this->dic[47] = 52; // /
	this->dic[':'] = 53; // :
	this->dic[';'] = 54; // ;
	this->dic['<'] = 55; // <
	this->dic['='] = 56; // =
	this->dic['>'] = 57; // >
	this->dic['['] = 58; // [
	this->dic['\\'] = 59; // Backspace
	this->dic[']'] = 60; // ]
	this->dic[94] = 61; // ^
	this->dic[96] = 62; // `
	this->dic['{'] = 63; // {
	this->dic['|'] = 64; // |
	this->dic['}'] = 65; // }
	this->dic['~'] = 66; // ~
}

void Display::show(){
  if(inverted) {
    for (int x = 0; x < DISPLAY_WIDTH; x++) {
      for (int y = 0; y < DISPLAY_HEIGHT; y++) {
        if ( x % 2) { //odd row
          pLeds[(DISPLAY_WIDTH - 1)* DISPLAY_HEIGHT -(x * DISPLAY_HEIGHT) +y] = pLedDisplay[x][y];
          //pLeds[90 - x * DISPLAY_HEIGHT + y] = CRGB(0, 60, 0);
        }
        else { //even row
          pLeds[DISPLAY_WIDTH* DISPLAY_HEIGHT -1 -(x * DISPLAY_HEIGHT) -y] = pLedDisplay[x][y];
          //pLeds[94 - x * DISPLAY_HEIGHT - y] = CRGB(60, 0, 0);
        }
      }
    }
  }
  else{
    for (int x = 0; x < DISPLAY_WIDTH; x++) {
      for (int y = 0; y < DISPLAY_HEIGHT; y++) {
        if ( x % 2) { //odd row
          pLeds[x * DISPLAY_HEIGHT + 4 - y] = pLedDisplay[x][y];
        }
        else { //even row
          pLeds[x * DISPLAY_HEIGHT + y] = pLedDisplay[x][y];
        }
      }
    }
  }
	FastLED.show();
}

void Display::clear(){
	for (int x = 0; x < DISPLAY_WIDTH; x++) {
		for (int y = 0; y < DISPLAY_HEIGHT; y++) {
			pLedDisplay[x][y].r = 0;
			pLedDisplay[x][y].g = 0;
			pLedDisplay[x][y].b = 0;
		}
	}
}

void Display::setString(char* newString){
	
	this->strLength = strlen(newString);
	
	if(strLength >= STRING_DISPLAY_MAX_LENGTH) { //make sure we have no buffer overflow
		strLength = STRING_DISPLAY_MAX_LENGTH - 1;
	}
	
	memset(this->string, 0, STRING_DISPLAY_MAX_LENGTH);	
	strncpy(this->string, newString, strLength);
	this->string[strLength] = '\0';
	
	int lineCounter = 0;
	
	for (int i = 0; i < strLength; i++) {
		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 5; y++) {
				if (font5by3[dic[string[i]]][y][x]) { //x and y are flipped here to make the font dictionary easier to read
					frameBuffer[lineCounter][y].r = charColor[i].r;
					frameBuffer[lineCounter][y].g = charColor[i].g;
					frameBuffer[lineCounter][y].b = charColor[i].b;
				}
				else {
					frameBuffer[lineCounter][y].r = 0;
					frameBuffer[lineCounter][y].g = 0;
					frameBuffer[lineCounter][y].b = 0;
				}
			}
			lineCounter++;
		}
		lineCounter++;
	}
	
	lineCounter = strLength * 4;
		
	this->frameOffset = 0;
	this->updateFrame();
}

char* Display::getString(){	
	return this->string;
}

void Display::updateFrame(){
	for (int x = 0; x < DISPLAY_WIDTH; x++) {
		for (int y = 0; y < DISPLAY_HEIGHT; y++) {
			if (x + frameOffset < strLength * 4){
				pLedDisplay[x][y] = frameBuffer[x + frameOffset][y];
			}
			else{
				pLedDisplay[x][y] = frameBuffer[x - (strLength*4 - frameOffset)][y];
			}
		}
	}
}

void Display::shiftFrame(){
	frameOffset++;
	if (frameOffset > strLength * 4){
		frameOffset= 0;
	}
	
	this->updateFrame();
}

int Display::setCharColor(int charNo, CRGB newCharColor){
	if(charNo < STRING_DISPLAY_MAX_LENGTH - 1){
		this->charColor[charNo].r = newCharColor.r;
		this->charColor[charNo].g = newCharColor.g;
		this->charColor[charNo].b = newCharColor.b;
	}
}

int Display::setStringColor(CRGB newStringColor){
	for(int i = 0; i < STRING_DISPLAY_MAX_LENGTH; i++){
		this->charColor[i].r = newStringColor.r;
		this->charColor[i].g = newStringColor.g;
		this->charColor[i].b = newStringColor.b;
	}
}

int Display::getStringLength(){
	return this->strLength;
}

void Display::test(){ //only used for debbuging
}