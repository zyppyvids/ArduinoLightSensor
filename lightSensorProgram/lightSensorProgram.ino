#include <Wire.h>
#include <BH1750.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4

BH1750 lightMeter;

Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  
  lightMeter.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)

  display.clearDisplay();
  display.setCursor(0,0);
  display.display();
}

void loop() {

  uint16_t lux = lightMeter.readLightLevel();

  char luxStr[10];
  sprintf(luxStr, "%u", lux);

  if(lux <= 50){
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  }     

  updateDisplay(luxStr);
  delay(1000);
}

void updateDisplay(char *Lux)
{
  setupDisplay(); //Setups the Display for usage

  printSensorModel(); //Prints the Sensor Model
  
  printLightLux(Lux); //Prints the light lux to the Display

  printStatus(); //Print LED Status
  
  display.display(); //Displays everything on the display
}

void setupDisplay(){
  display.clearDisplay(); //Clears the display of all characters
  display.setTextSize(2); //Sets the text size to 2
  display.setTextColor(WHITE,BLACK); // Draw white text
  display.setCursor(0, 0); // Start at top-left corner
  display.cp437(true); // Use full 256 char 'Code Page 437' font
}

void printSensorModel(){
  display.setCursor(5, 0); //Sets the cursor position to X=5 and Y=0
  display.println("- BH1750 -"); 
}

void printLightLux(char *Lux){
  display.setTextSize(1); //Sets the text size to 1
  display.print("Light: ");
  display.print(Lux);
  display.println(" lx");
}

void printStatus(){
  int status = digitalRead(LED_BUILTIN); //Reads the PIN State of the Builtin LED
  
  if(status == 0)
    display.print("Status: OFF");
  else
    display.print("Status: ON");
}
