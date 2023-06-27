#include <dht.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

#define DHT11_PIN 7

SoftwareSerial Blue(19,18);
int Relay = 4;
long int data;
long int pass1 = 92; // ON
long int pass2 = 79; // OFF
char state = 0;

LiquidCrystal_I2C lcd( 0x27, 16, 2 );
dht DHT;

void setup()
{
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, HIGH);

  Serial.begin(9600);
  Blue.begin(9600);
  lcd.init();
  lcd.backlight();

  
  //delay(1000);
  
}

void loop()
{
  int chk = DHT.read11(DHT11_PIN);
  int soil_val = analogRead(A0);
  float temp = DHT.temperature;
  float humidity = DHT.humidity;
  
  
 
  Serial.print("Temperatura: ");
  Serial.println(DHT.temperature);
  Blue.print("Temperatura: ");
  Blue.print(DHT.temperature);
  Blue.println(" *C");

  Serial.print("Umiditate aer: ");
  Serial.println(DHT.humidity);
  Blue.print("Umiditate aer: ");
  Blue.print(DHT.humidity);
  Blue.println(" %");

  Serial.print("Umiditate sol: ");
  Serial.println(soil_val);
  Blue.print("Umiditatea sol: ");
  //Blue.println(soil_val);

  lcd.setCursor(0,0); 
  lcd.print("Temp: ");
  lcd.print(DHT.temperature);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(DHT.humidity);
  lcd.print("%");
  
  delay(3000);
  lcd.clear();

  //Zona functionalitate
  if (soil_val > 950  ) {
    digitalWrite(Relay, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Water Pump is ON ");
  } 
  else if (soil_val < 950 )
  {
    digitalWrite(Relay, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Water Pump is OFF");
  }


//Zona afisare BT/LCD
  if (soil_val < 500) 
  {
    lcd.setCursor(0, 1);
    lcd.print("Moisture : HIGH");
    Blue.println("Ridicata");
    Blue.println("Pompa e oprita");
  } 
  else if (soil_val > 500 && soil_val < 950) 
  {
    lcd.setCursor(0, 1);
    lcd.print("Moisture : MID ");
    Blue.println("Potrivita");
    Blue.println("Pompa e oprita");

  }
  else if (soil_val > 950) 
  {
    lcd.setCursor(0, 1);
    lcd.print("Moisture : LOW ");
    Blue.println("Slaba");
    Blue.println("Pompa e pornita");
  }
  Blue.println(" ");
  delay(3000);
  lcd.clear();
}