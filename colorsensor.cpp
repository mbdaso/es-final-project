#include "mbed.h"

// We set the sensor address. For TCS34725 is 0x29 = ‭‭0010 1001‬ (bin) ->> ‭0101 0010‬ (bin) = 0x52
// We shift 1 bit to the left because in I2C protocol slave address is 7-bit. So we discard the 8th bit
#define SENSOR_ADDR (0x29<<1)
int clear_value, red_value, green_value, blue_value;
char dominant_color;

bool readColour =  false; //Variable for ISR

Thread colorsensor_thread(osPriorityNormal, 1024); // 1K stack size

//ISR code
void read_colour (void) {
	readColour =  true;
}

//Get max value (r,g,b) function
char getMax(int r, int g, int b) {
  char result;
  if (r>g && r>b){ 
    result = 'r';  
  } 
	else if (g>b){
    result = 'r';
  }
  else{
    result = 'b';
  }
  return result;
}

void colorsensor_callback(); 

void colorsensor_callback() {
  // Example program connecting the TCS34725 Color Sensor to the B-L072Z-LRWAN1 using I2C
	I2C i2c(PB_9,PB_8); //pins for I2C communication (SDA, SCL)
	
	DigitalOut whiteLed(PB_7); // TCS34725 led
	
	DigitalOut ledR(PA_14); //RGB led - red light
	DigitalOut ledG(PH_1);  //RGB led - green light 
	DigitalOut ledB(PA_4);  //RGB led - blue light
	
	//Variable for ISR
	bool read_Colour;
	
	DigitalOut green(LED1); //LED of B-L072Z-LRWAN1 board
	Ticker t;
	
	t.attach(read_colour, 1.0); // Every second the ticker triggers an interruption
  green = 1; // LED of B-L072Z-LRWAN1 board on
    
  // Connect to the Color sensor and verify whether we connected to the correct sensor. 
    
  //  i2c.frequency(200000);
  /*******************************************************
	* id_regval contains command register value: ‭1001 0010 *
	* COMMAND REGISTER structure                           *
	* 7   |  6     5  |  4   3   2   1  0                  *
	* CMD      TYPE          ADDR/SF                       *
	*                                                      *
	* CMD=1                                                *
	* TYPE=00 -> repeated byte protocol transaction        *
	* ADDR/SF= 10010 -> ADDR 0x12 - Device ID              *
	********************************************************/
	char id_regval[1] = {0x92}; //‭1001 0010‬ (bin)
	char data[1] = {0}; //‭0000 0000‬
	
	/**********************************************************************
	* int write(int address, const char *data, int length, bool repeated) *
	* int read(int address, char *data, int length, bool repeated)        *
	***********************************************************************/
	//We obtain device ID from ID register (0x12)
  i2c.write(SENSOR_ADDR,id_regval,1, true);
  i2c.read(SENSOR_ADDR,data,1,false); 
	
	   //We check that the ID is the TCS34725 one. If it is, we switch off a LED on the board, wait for 2s, and switch on again
	if (data[0]==0x44) { //‭ 0100 0100‬ -> Value for the part number (0x44 for TCS34725)
		green = 0;
		wait (1);
		green = 1;
	} 
	else {
		green = 0;
	}
	
	// Initialize color sensor
    
	// Timing register address 0x01 (0000 0001). We set 1st bit to 1 -> 1000 0001
	char timing_register[2] = {0x81,0x50}; //0x50 ~ 400ms
	i2c.write(SENSOR_ADDR,timing_register,2,false); 
    
	// Control register address 0x0F (0000 1111). We set 1st bit to 1 -> 1000 1111
	char control_register[2] = {0x8F,0}; //{0x8F, 0x00}, {1000 1111, 0000 0000} -> 1x gain
	i2c.write(SENSOR_ADDR,control_register,2,false);
    
	// Enable register address 0x00 (0000 0000). We set 1st bit to 1 -> 1000 0000
	char enable_register[2] = {0x80,0x03}; //{0x80, 0x03}, {1000 0000, 0000 0011} -> AEN = PON = 1
	i2c.write(SENSOR_ADDR,enable_register,2,false);
    
  // Read data from color sensor (Clear/Red/Green/Blue)
	char clear_reg[1] = {0x94}; // {‭1001 0100‬} -> 0x14 and we set 1st bit to 1
	char clear_data[2] = {0,0};
	char red_reg[1] = {0x96}; // {‭1001 0110‬} -> 0x16 and we set 1st bit to 1
	char red_data[2] = {0,0};
	char green_reg[1] = {0x98}; // {‭1001 1000‬} -> 0x18 and we set 1st bit to 1
	char green_data[2] = {0,0};
	char blue_reg[1] = {0x9A}; // {‭1001 1010‬} -> 0x1A and we set 1st bit to 1
	char blue_data[2] = {0,0};
   
	whiteLed = 1;
  while (true) {
		
		if (read_Colour){
			
			readColour = 0; //readColour = false
			//Reads clear value
			i2c.write(SENSOR_ADDR,clear_reg,1, true);
			Thread::wait(100);
			i2c.read(SENSOR_ADDR,clear_data,2, false);
				
			//We store in clear_value the concatenation of clear_data[1] and clear_data[0]
			clear_value = ((int)clear_data[1] << 8) | clear_data[0];
				
			//Reads red value
			i2c.write(SENSOR_ADDR,red_reg,1, true);
			i2c.read(SENSOR_ADDR,red_data,2, false);
				
			//We store in red_value the concatenation of red_data[1] and red_data[0]
			red_value = ((int)red_data[1] << 8) | red_data[0];
				
			//Reads green value
			i2c.write(SENSOR_ADDR,green_reg,1, true);
			i2c.read(SENSOR_ADDR,green_data,2, false);
				
			//We store in green_value the concatenation of green_data[1] and green_data[0]
			green_value = ((int)green_data[1] << 8) | green_data[0];
				
			//Reads blue value
			i2c.write(SENSOR_ADDR,blue_reg,1, true);
			i2c.read(SENSOR_ADDR,blue_data,2, false);
				
			//We store in blue_value the concatenation of blue_data[1] and blue_data[0]
			blue_value = ((int)blue_data[1] << 8) | blue_data[0];
				
			//Obtains which one is the greatest - red, green or blue
			dominant_color = getMax(red_value, green_value, blue_value);
		
			//Switchs the color of the greatest value. First, we switch off all of them
			ledR.write(1);
			ledG.write(1);
			ledB.write(1);
			
			switch (dominant_color){
				case 'r':
					ledR.write(0);
					break;
				case 'g':
					ledG.write(0);
					break;
				case 'b':
					ledB.write(0);
					break;
			} 
			//whiteLed = 0;
		}
		Thread::wait(1000);
	}
}



