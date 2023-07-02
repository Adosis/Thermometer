#include <OneWire.h>              // using more than one sensor at one port
#include <DallasTemperature.h>    // library for using the DS18B20
#include <Adafruit_NeoPixel.h>    // library for using the WS2812B-stripes

// fill in the parameters of you thermometer
float numLed = 68;      // number of LEDs of your stripe
float lenThermo = 46;   // the distance [cm] between lowest and highest temperature of your thermometer and also the lenght of your led stripe
float minTemp =(-10);   // the lowest temperatur of your thermometer [°C]
float maxTemp = 40;     // the highest temerature of your thermometer [°C]

float temp;             // the temperature measuring by the DS18B20
int anzLed;             // numbers of LED needed to display the measured temperature

int pinTempSens=14;     // DS18B20 (Temp) is connected to pin 14 (input)
int pinPixel=13;        // WS2812B (LED) is connected to pin 13 (output)

// initialize the led stripe WS2812B
#define NUMPIXELS numLed
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, pinPixel, NEO_GRB + NEO_KHZ800);

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(pinTempSens);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

void setup() 
{
  Serial.begin(115200); // Start the Serial Monitor
  sensors.begin();      // Start the DS18B20 sensor
}

void loop() 
{
  sensors.requestTemperatures();        // preparing the temperature sensor 
  temp = sensors.getTempCByIndex(0);    // get the temperature of the sensor in °C; please use sensors.getTempFByIndex(0) for temperature in Fahrenheit

  // output on serial monitor 
  Serial.print(temp);   
  Serial.println("ºC");  

  for (int i =0; i<=numLed;i++)  {pixels.setPixelColor(i,pixels.Color(0,0,0));}  // turn of all LEDs   

  // example:
  // -10°C is the lowest and 40°C is the highets temperature of the scale of the used thermometer
  // the distance between -10°C and 40°C was 46cm
  // the used WS1820 has 144 LED/m or 1.44 LED/cm
  anzLed = round ((temp-minTemp)*((lenThermo/(maxTemp-minTemp))*1.44));   // calculate the number of LEDs to display the temperature
  //use this line, if led 1 of your stripe shows the highest temperatur
  for (int i = numLed; i>=numLed-anzLed;i--)  {pixels.setPixelColor(i,pixels.Color(255,0,0));} // Rot
  //use this line, if led 1 of your stripe shows the lowest temperatur    
  //for (int i = 0; i<=anzLed;i++)  {pixels.setPixelColor(i,pixels.Color(255,0,0));} // Rot    
  pixels.show(); 
  delay(1000);
}