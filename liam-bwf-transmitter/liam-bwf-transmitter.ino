/* Liam BWF Transmitter
   --------------------
   
   This program will send out a +/- signal of 100µs, then delay 10ms.
 
   
   100µs
    __                           
   |  |                           
   |  |        10ms                
   |  |   ______________
      |  |             
      |  |              
      |__|                       
  
   The signal will be recieved differently by the cutter depending on
   if it is inside or outside of the BWF
   For this reason, it is important to connect the BWF ends the right
   way. Should the cutter think it is outside, try switching the ends.
  
   There are serveral different versions of this shield

   1. A standalone shield connected to an aruduino through a cable
      - A standalone shield can be run on higher voltage and has a
        built in voltage converter for the arduino
        This is perfect for larger lawns which requires a strong signal
   2. A normal L298 motor shield on an Arduino
      - Easy to put together. Same as for the Liam reciever but max 12V
   3. A L293 motor shield on an Arduino
      - A very low cost shield but limited in voltage (12V) and speed
   4. A MegaMoto shield on an Arduino
      - Higher cost but very powerful and strong signal with little heat generation

*/

// Select which transmitter type you have by uncommenting that line

#define __1_L298_Standalone__
//#define __2_L298_Shield__
//#define __3_L293_Shield__
//#define __4_MegaMoto_Shield__

/*
   Connector usage
   ---------------
   The BWF should be connected to motor A or motor 0 on all shields

   For the standalone shield (nr 1), pins A0 and A1 should be connected to input pins
   for motor 1 on the shield (In1 and In2)
*/


//--------------- End of definition --------------------------
//---- No need to change anything below ----------------------

// Arduino pins and timing for the PWM signals.
#ifdef __1_L298_Standalone__ 
	#define PIN1_PWM A0
	#define PIN2_PWM A1
	#define PIN3_PWM A2
	#define PIN4_PWM A3
	#define LONG_DELAY 8000	
	#define SHORT_DELAY 250			
#endif

#ifdef __2_L298_Shield__
	#define PIN1_PWM 3
	#define PIN2_PWM 12
	#define PIN_BREAK_A 9
	#define LONG_DELAY 8000
	#define SHORT_DELAY 250		
#endif

#ifdef __3_L293_Shield__
	#define MOTORLATCH 12
	#define MOTORCLK 4
	#define MOTORENABLE 7
	#define MOTORDATA 8
	#define LONG_DELAY 8000		//L293 shield is 130ms slower to change
	#define SHORT_DELAY 250		//L293 shield is 130ms slower to change
#endif

#ifdef __4_MegaMoto_Shield__
	#define PIN1_PWM 5
	#define PIN2_PWM 7
	#define LONG_DELAY 8000
	#define SHORT_DELAY 250		
#endif




void setup()
{
  Serial.begin(9600);
  Serial.println("Liam BWF Transmitter");
#ifdef __1_L298_Standalone__
  pinMode(PIN1_PWM,OUTPUT);
  pinMode(PIN2_PWM,OUTPUT);
  pinMode(PIN3_PWM,OUTPUT);
  pinMode(PIN4_PWM,OUTPUT);
#endif

#ifdef __2_L298_Shield__
  pinMode(PIN1_PWM,OUTPUT);
  pinMode(PIN2_PWM,OUTPUT);
  pinMode(PIN_BREAK_A, OUTPUT);
#endif

#ifdef __3_L293_Shield__
    // Set pins for shift register to output
    pinMode(MOTORLATCH, OUTPUT);
    pinMode(MOTORENABLE, OUTPUT);
    pinMode(MOTORDATA, OUTPUT);
    pinMode(MOTORCLK, OUTPUT);

    // Set pins for shift register to default value (low);
    digitalWrite(MOTORDATA, LOW);
    digitalWrite(MOTORLATCH, LOW);
    digitalWrite(MOTORCLK, LOW);
    // Enable the shift register, set Enable pin Low.
    digitalWrite(MOTORENABLE, LOW);
#endif

#ifdef __4_MegaMoto_Shield__
  pinMode(PIN1_PWM,OUTPUT);
  pinMode(PIN2_PWM,OUTPUT);
#endif


}


void loop()
{

  // This is where the signal is generated.
  // Repeat indefinately
  high();
  delayMicroseconds(SHORT_DELAY);  
  low();
  delayMicroseconds(SHORT_DELAY);
  none();
  delayMicroseconds(LONG_DELAY);
  
  }

void high() {
	#ifdef __1_L298_Standalone__
  		digitalWrite(PIN1_PWM, HIGH);
  		digitalWrite(PIN2_PWM, LOW);
  		digitalWrite(PIN3_PWM, HIGH);
  		digitalWrite(PIN4_PWM, LOW);
  	#endif
  	
	#ifdef __2_L298_Shield__
		digitalWrite(PIN_BREAK_A, LOW);
  		digitalWrite(PIN1_PWM, HIGH);
  		digitalWrite(PIN2_PWM, LOW);
  	#endif
  	
	#ifdef __3_L293_Shield__
  		shiftItOut(39);
  	#endif

	#ifdef __4_MegaMoto_Shield__
  		digitalWrite(PIN1_PWM, HIGH);
  		digitalWrite(PIN2_PWM, LOW);
  	#endif


}

void none() {
	#ifdef __1_L298_Standalone__
  		digitalWrite(PIN1_PWM, LOW);
  		digitalWrite(PIN2_PWM, LOW);
  		digitalWrite(PIN3_PWM, LOW);
  		digitalWrite(PIN4_PWM, LOW);
  	#endif
  	
	#ifdef __2_L298_Shield__
		digitalWrite(PIN_BREAK_A, LOW);
  		digitalWrite(PIN1_PWM, LOW);
  		digitalWrite(PIN2_PWM, LOW);
  	#endif
  	
	#ifdef __3_L293_Shield__
  		shiftItOut(0);
  	#endif

	#ifdef __4_MegaMoto_Shield__
  		digitalWrite(PIN1_PWM, LOW);
  		digitalWrite(PIN2_PWM, LOW);
  	#endif

}

void low() {
	#ifdef __1_L298_Standalone__
  		digitalWrite(PIN1_PWM, LOW);
  		digitalWrite(PIN2_PWM, HIGH);
  		digitalWrite(PIN3_PWM, LOW);
  		digitalWrite(PIN4_PWM, HIGH);
  	#endif
  	
	#ifdef __2_L298_Shield__
		digitalWrite(PIN_BREAK_A, LOW);
  		digitalWrite(PIN1_PWM, HIGH);
  		digitalWrite(PIN2_PWM, HIGH);
  	#endif
  	
	#ifdef __3_L293_Shield__
  		shiftItOut(216);
  	#endif

	#ifdef __4_MegaMoto_Shield__
  		digitalWrite(PIN1_PWM, HIGH);
  		digitalWrite(PIN2_PWM, HIGH);
  	#endif

}

#ifdef __3_L293_Shield__
void shiftItOut(int out_byte) {
  // Use the default Arduino 'shiftOut()' function to
  // shift the bits with the MOTORCLK as clock pulse.
  // The 74HC595 shiftregister wants the MSB first.
  // After that, generate a latch pulse with MOTORLATCH.
  
  shiftOut(MOTORDATA, MOTORCLK, MSBFIRST, out_byte);
  delayMicroseconds(5);    // For safety, not really needed.
  digitalWrite(MOTORLATCH, HIGH);
  delayMicroseconds(5);    // For safety, not really needed.
  digitalWrite(MOTORLATCH, LOW);

}
#endif