#ifndef BUTTON_H
#define BUTTON_H

	class Button
	{
	private:
		uint8_t fpin;

		uint8_t fPressCount;
		uint8_t fMaxPressCountToValid;
		bool fClick;

    bool Clicked;

		bool fKeyPress;

		inline void BaseInit(const uint8_t pin, const bool PULLUP)
		{
			fpin = pin;
			fKeyPress = false;
			fPressCount = 0;
      fClick = true;
      
      Clicked = false;

			if(PULLUP) 
				pinMode(fpin, INPUT_PULLUP);
			else
				pinMode(fpin, INPUT);
		}

	public:

		Button(const uint8_t pin, const bool PULLUP)
		{
			BaseInit(pin, PULLUP);
			fMaxPressCountToValid = 15;
		}

		Button(const char pin, const char MaxPressCountToValid, const bool PULLUP)
		{
			BaseInit(pin, PULLUP);
			fMaxPressCountToValid = MaxPressCountToValid;
		}

		void ScanState()
		{
			if ( fClick == (digitalRead(fpin)) ) 
			{
			    fPressCount = 0;
			}
			else 
			{
          
			    ++fPressCount;

			    if ( fPressCount >= fMaxPressCountToValid ) 
			    {
             	fKeyPress = fClick;
              Clicked = !fClick;
			      	fClick = !fClick;
			      	fPressCount = 0;
			    }   
			}
		}

		inline bool Pressed()
		{
			return fKeyPress;
		}

   inline bool Click()
   {
    bool tmp = Clicked;
    if(tmp) Clicked = false;
    return tmp;
   }

   void ResetClick()
   {
      fKeyPress = false;
      fPressCount = 0;
      fClick = true;
      Clicked = false;
   }

		char pin()
		{
			return fpin;
		}

		~Button()
		{
			
		}
	};

  class JoyStick
  {
    private:
      int fPinAxisX;
      int fPinAxisY;
      int fPinButton;
      int fAxisX;
      int fAxisY;

      Button* fbutton;
    public:
      JoyStick(int PinAxisX, int PinAxisY, char PinButton);
      
      void ScanState();
      
      inline int AxisX()
      {
        return fAxisX;
      }
      inline int AxisY()
      {
        return fAxisY;
      }
      
      inline bool Pressed()
      {
        //return false;
        return fbutton->Pressed();
      }
      inline bool Click()
      {
        return fbutton->Click();
        //return false;
      }
      inline void ResetClick()
      {
        fbutton->ResetClick();
      }
      inline char pinAxisX()
      {
        return fPinAxisX;
      }
      inline char pinAxisY()
      {
        return fPinAxisY;
      }
      inline char pinButton()
      {
        return fPinButton;
      }
      
      ~JoyStick();
  };

  JoyStick::JoyStick(int PinAxisX, int PinAxisY, char PinButton)
  {
    fPinAxisX = PinAxisX;
    fPinAxisY = PinAxisY;
    fPinButton = PinButton;

    pinMode(fPinAxisX, INPUT_PULLUP);
    pinMode(fPinAxisY, INPUT_PULLUP);
    fbutton = new Button(fPinButton, true);
  }
  
  void JoyStick::ScanState()
  {
    fAxisX = analogRead(fPinAxisX) - 512;
    fAxisY = analogRead(fPinAxisY) - 512;
    fbutton->ScanState();
  }

  JoyStick::~JoyStick()
  {
    Serial.println("JoyD");
    delete fbutton;
  }
  

#endif
