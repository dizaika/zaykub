#ifndef VISUALIZER_H
#define VISUALIZER_H
#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

	struct Color
	{
		static long FromRGB(unsigned char r, unsigned char g, unsigned char b)
		{
			long res = r;
			res = (res << 8) + g;
			res = (res << 8) + b;
			return res;
		};
	};

	class Visualizer
	{
	private:
		int fDataPin;
		int fLEDCount;

		Adafruit_NeoPixel* pixels;

	public:
		Visualizer(const int DataPin, const int LEDCount);
		void Show();	

		void SetPixelColor(int num, char red, char green, char blue);
		void SetPixelColor(int num, long color);
		void SetPixelColor(int from, int to, char red, char green, char blue);
		void SetPixelColor(int from, int to, long color);

		void SetAllPixelColor(char red, char green, char blue);
		void SetAllPixelColor(long color);
		void Clear(bool show);

		~Visualizer();
	};

	Visualizer::Visualizer(const int DataPin, const int LEDCount)
		{
		fDataPin = DataPin;
		fLEDCount = LEDCount;

		#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
				clock_prescale_set(clock_div_1);
		#endif

		pixels = new Adafruit_NeoPixel(fLEDCount, fDataPin, NEO_GRB + NEO_KHZ800);
		pixels->begin();
		Clear(true);
	}

	void Visualizer::Show()
	{
		pixels->show();
	}

	void Visualizer::Clear(bool show)
	{
		pixels->clear();
    if(show) Show();
	}

	void Visualizer::SetAllPixelColor(char red, char green, char blue)
	{
		for(int i = 0; i < fLEDCount; ++i)
		{
			SetPixelColor(i, red, green, blue);
		}
	}

	void Visualizer::SetAllPixelColor(long color)
	{
		char red   = (char)((color & 0x00FF0000) >> 16);
		char green = (char)((color & 0x0000FF00) >> 8);
		char blue  = (char)((color & 0x000000FF));

		SetAllPixelColor(red, green, blue);
	}

	void Visualizer::SetPixelColor(int num, char red, char green, char blue)
	{
		pixels->setPixelColor(num, pixels->Color(red, green, blue));
	}

	void Visualizer::SetPixelColor(int num, long color)
	{
		char red   = (char)((color & 0x00FF0000) >> 16);
		char green = (char)((color & 0x0000FF00) >> 8);
		char blue  = (char)((color & 0x000000FF));

		SetPixelColor(num, red, green, blue);
	}

	void Visualizer::SetPixelColor(int from, int to, char red, char green, char blue)
	{
		for(int i = from; i <= to; ++i)
		{
			SetPixelColor(i, red, green, blue);
		}
	}

	void Visualizer::SetPixelColor(int from, int to, long color)
	{
		char red   = (char)((color & 0x00FF0000) >> 16);
		char green = (char)((color & 0x0000FF00) >> 8);
		char blue  = (char)((color & 0x000000FF));

		SetPixelColor(from, to, red, green, blue);
	}

	Visualizer::~Visualizer()
	{
		//delete pixels;
	}

#endif
