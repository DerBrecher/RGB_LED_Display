#ifndef WS2812DISPLAY_H
#define WS2812DISPLAY_H

//#include <Arduino.h>
//#define WS2812_DISPLAY_DRIVER_FASTLED
#define WS2812_DISPLAY_DRIVER_NEOPIXEL

#ifdef WS2812_DISPLAY_DRIVER_FASTLED
	#include <FastLED.h>
#endif

#ifdef WS2812_DISPLAY_DRIVER_NEOPIXEL
	#include <NeoPixelBus.h>
#endif


#define DISPLAY_HEIGHT 5
#define DISPLAY_WIDTH 19
#define STRING_DISPLAY_MAX_LENGTH 28



struct RGBPixel;

struct RGBPixel {
	union {
		struct  {
			union {
				uint8_t r;
				uint8_t red;
			};
			union {
				uint8_t g;
				uint8_t green;
			};
			union {
				uint8_t b;
				uint8_t blue;
			};
		};
		uint8_t raw[3];
	};
	

	// Array access operator to index into the crgb object
	inline uint8_t& operator[] (uint8_t x) __attribute__((always_inline))
	{
		return raw[x];
	}

	// default values are UNINITIALIZED
	inline RGBPixel() __attribute__((always_inline))
	{
	}

	// allow construction from R, G, B
	inline RGBPixel(uint8_t ir, uint8_t ig, uint8_t ib)  __attribute__((always_inline))
	: r(ir), g(ig), b(ib)
	{
	}

	// allow copy construction
	inline RGBPixel(const RGBPixel& rhs) __attribute__((always_inline))
	{
		r = rhs.r;
		g = rhs.g;
		b = rhs.b;
	}

	// allow assignment from one RGB struct to another
	inline RGBPixel& operator= (const RGBPixel& rhs) __attribute__((always_inline))
    {
        r = rhs.r;
        g = rhs.g;
        b = rhs.b;
        return *this;
    }
};


class Display {
	public:
		#ifdef WS2812_DISPLAY_DRIVER_FASTLED
		Display(CRGB outputLedArray[], bool invertDisplay);
		#endif

		#ifdef WS2812_DISPLAY_DRIVER_NEOPIXEL
		Display(NeoPixelBus<NeoGrbFeature, NeoEsp8266Dma800KbpsMethod> *outputStrip, bool invertDisplay);
		#endif

		int setCharColor(int charNo, RGBPixel charColor);
		int setStringColor(RGBPixel newStringColor);
		void clear();
		void show();
		void shiftFrame();
		void setBrightness(int newBrightness);
		void setString(char* newString);
		char* getString();
		int getStringLength();
		
		void test(); //only used for debbuging

	protected:
		bool inverted = false;
		int brightness = 40;
		uint8_t dic[255];
		char* string = {"This was a great test"};
		int strLength;
		int frameOffset = 0;
		
		RGBPixel frameBuffer[STRING_DISPLAY_MAX_LENGTH * 4][DISPLAY_HEIGHT];
		RGBPixel charColor[STRING_DISPLAY_MAX_LENGTH];
		
		void updateFrame();
		void initDic();

		#ifdef WS2812_DISPLAY_DRIVER_FASTLED
		CRGB  *pLeds;
		#endif
		
		#ifdef WS2812_DISPLAY_DRIVER_NEOPIXEL
		NeoPixelBus<NeoGrbFeature, NeoEsp8266Dma800KbpsMethod> *pStrip;
		#endif
		

		uint8_t font5by3[67][5][3] = {
			//----- Numbers -----
			{ //zero 
				{1,1,1},
				{1,0,1},
				{1,0,1},
				{1,0,1},
				{1,1,1}
			},
			{ //one
				{0,1,0},
				{1,1,0},
				{0,1,0},
				{0,1,0},
				{1,1,1}
			},
			{ //two
				{1,1,0},
				{0,0,1},
				{0,1,0},
				{1,0,0},
				{1,1,1}
			},
			{ //three
				{1,1,1},
				{0,0,1},
				{1,1,1},
				{0,0,1},
				{1,1,1}
			},
			{ //four
				{1,0,1},
				{1,0,1},
				{1,1,1},
				{0,0,1},
				{0,0,1}
			},
			{ //five
				{1,1,1},
				{1,0,0},
				{1,1,1},
				{0,0,1},
				{1,1,1}
			},
			{ //six
				{1,1,1},
				{1,0,0},
				{1,1,1},
				{1,0,1},
				{1,1,1}
			},
			{ //seven
				{1,1,1},
				{0,0,1},
				{0,1,0},
				{0,1,0},
				{0,1,0}
			},
			{ //eight
				{1,1,1},
				{1,0,1},
				{1,1,1},
				{1,0,1},
				{1,1,1}
			},
			{ //nine
				{1,1,1},
				{1,0,1},
				{1,1,1},
				{0,0,1},
				{1,1,1}
			},
			//----- Letters -----
			{ //A
				{1,1,1},
				{1,0,1},
				{1,1,1},
				{1,0,1},
				{1,0,1}
			},
			{ //B
				{1,1,0},
				{1,0,1},
				{1,1,0},
				{1,0,1},
				{1,1,0}
			},
			{ //C
				{0,1,0},
				{1,0,1},
				{1,0,0},
				{1,0,1},
				{0,1,0}
			},
			{ //D
				{1,1,0},
				{1,0,1},
				{1,0,1},
				{1,0,1},
				{1,1,0}
			},
			{ //E
				{1,1,1},
				{1,0,0},
				{1,1,1},
				{1,0,0},
				{1,1,1}
			},
			{ //F
				{1,1,1},
				{1,0,0},
				{1,1,1},
				{1,0,0},
				{1,0,0}
			},
			{ //G
				{0,1,1},
				{1,0,0},
				{1,0,0},
				{1,0,1},
				{0,1,1}
			},
			{ //H
				{1,0,1},
				{1,0,1},
				{1,1,1},
				{1,0,1},
				{1,0,1}
			},
			{ //I 
				{1,1,1},
				{0,1,0},
				{0,1,0},
				{0,1,0},
				{1,1,1}
			},
			{ //J
				{0,0,1},
				{0,0,1},
				{0,0,1},
				{1,0,1},
				{0,1,0}
			},
			{ //K
				{1,0,1},
				{1,0,1},
				{1,1,0},
				{1,0,1},
				{1,0,1}
			},
			{ //L
				{1,0,0},
				{1,0,0},
				{1,0,0},
				{1,0,0},
				{1,1,1}
			},
			{ //M
				{1,0,1},
				{1,1,1},
				{1,0,1},
				{1,0,1},
				{1,0,1}
			},
			{ //N
				{1,1,0},
				{1,0,1},
				{1,0,1},
				{1,0,1},
				{1,0,1}
			},
			{ //O
				{0,1,0},
				{1,0,1},
				{1,0,1},
				{1,0,1},
				{0,1,0}
			},
			{ //P
				{1,1,0},
				{1,0,1},
				{1,1,0},
				{1,0,0},
				{1,0,0}
			},
			{ //Q 
				{0,1,0},
				{1,0,1},
				{1,0,1},
				{1,1,1},
				{0,1,1}
			},
			{ //R
				{1,1,0},
				{1,0,1},
				{1,1,0},
				{1,0,1},
				{1,0,1}
			},
			{ //S
				{0,1,1},
				{1,0,0},
				{0,1,0},
				{0,0,1},
				{1,1,0}
			},
			{ //T
				{1,1,1},
				{0,1,0},
				{0,1,0},
				{0,1,0},
				{0,1,0}
			},
			{ //U
				{1,0,1},
				{1,0,1},
				{1,0,1},
				{1,0,1},
				{1,1,1}
			},
			{ //V
				{1,0,1},
				{1,0,1},
				{1,0,1},
				{1,1,1},
				{0,1,0}
			},
			{ //W
				{1,0,1},
				{1,0,1},
				{1,0,1},
				{1,1,1},
				{1,0,1}
			},
			{ //X
				{1,0,1},
				{1,0,1},
				{0,1,0},
				{1,0,1},
				{1,0,1}
			},
			{ //Y
				{1,0,1},
				{1,0,1},
				{1,1,1},
				{0,1,0},
				{0,1,0}
			},
			{ //Z
				{1,1,1},
				{0,0,1},
				{0,1,0},
				{1,0,0},
				{1,1,1}
			},
			//----- Symbols -----
			{ //Space
				{0,0,0},
				{0,0,0},
				{0,0,0},
				{0,0,0},
				{0,0,0}
			},
			{ //.
				{0,0,0},
				{0,0,0},
				{0,0,0},
				{0,0,0},
				{1,0,0}
			},
			{ //,
				{0,0,0},
				{0,0,0},
				{0,0,0},
				{0,1,0},
				{1,0,0}
			},
			{ //"
				{1,0,1},
				{1,0,1},
				{0,0,0},
				{0,0,0},
				{0,0,0}
			},
			{ //?
				{1,1,0},
				{0,0,1},
				{0,1,0},
				{0,0,0},
				{0,1,0}
			},
			{ //!
				{0,1,0},
				{0,1,0},
				{0,1,0},
				{0,0,0},
				{0,1,0}
			},
			{ //_
				{0,0,0},
				{0,0,0},
				{0,0,0},
				{0,0,0},
				{1,1,1}
			},
			{ //*
				{0,0,0},
				{1,0,1},
				{0,1,0},
				{1,0,1},
				{0,0,0}
			},
			{ //#
				{1,0,1},
				{1,1,1},
				{1,0,1},
				{1,1,1},
				{1,0,1}
			},
			{ //$
				{0,1,1},
				{1,1,0},
				{0,1,0},
				{0,1,1},
				{1,1,0}
			},
			{ //%
				{1,0,0},
				{0,0,1},
				{0,1,0},
				{1,0,0},
				{0,0,1}
			},
			{ //&
				{0,1,1},
				{1,0,0},
				{0,1,1},
				{1,0,1},
				{0,1,1}
			},
			{ //(
				{0,0,1},
				{0,1,0},
				{0,1,0},
				{0,1,0},
				{0,0,1}
			},
			{ //)
				{1,0,0},
				{0,1,0},
				{0,1,0},
				{0,1,0},
				{1,0,0}
			},
			{ //+
				{0,0,0},
				{0,1,0},
				{1,1,1},
				{0,1,0},
				{0,0,0}
			},
			{ //-
				{0,0,0},
				{0,0,0},
				{1,1,1},
				{0,0,0},
				{0,0,0}
			},
			{ ///
				{0,0,1},
				{0,0,1},
				{0,1,0},
				{1,0,0},
				{1,0,0}
			},
			{ //:
				{0,0,0},
				{0,1,0},
				{0,0,0},
				{0,1,0},
				{0,0,0}
			},
			{ //;
				{0,0,0},
				{0,1,0},
				{0,0,0},
				{0,1,0},
				{1,0,0}
			},
			{ //<
				{0,0,1},
				{0,1,0},
				{1,0,0},
				{0,1,0},
				{0,0,1}
			},
			{ //=
				{0,0,0},
				{1,1,1},
				{0,0,0},
				{1,1,1},
				{0,0,0}
			},
			{ //>
				{1,0,0},
				{0,1,0},
				{0,0,1},
				{0,1,0},
				{1,0,0}
			},
			{ //[
				{0,1,1},
				{0,1,0},
				{0,1,0},
				{0,1,0},
				{0,1,1}
			},
			{ // Backslash
				{1,0,0},
				{1,0,0},
				{0,1,0},
				{0,0,1},
				{0,0,1}
			},
			{ // ]
				{1,1,0},
				{0,1,0},
				{0,1,0},
				{0,1,0},
				{1,1,0}
			},
			{ // ^
				{0,1,0},
				{1,0,1},
				{0,0,0},
				{0,0,0},
				{0,0,0}
			},
			{ // `
				{1,0,0},
				{0,1,0},
				{0,0,0},
				{0,0,0},
				{0,0,0}
			},
			{ // {
				{0,1,1},
				{0,1,0},
				{1,1,0},
				{0,1,0},
				{0,1,1}
			},
			{ // |
				{0,1,0},
				{0,1,0},
				{0,1,0},
				{0,1,0},
				{0,1,0}
			},
			{ // }
				{1,1,0},
				{0,1,0},
				{0,1,1},
				{0,1,0},
				{1,1,0}
			},
			{ // ~
				{0,0,0},
				{0,1,1},
				{1,1,0},
				{0,0,0},
				{0,0,0}
			}
		};
};
#endif