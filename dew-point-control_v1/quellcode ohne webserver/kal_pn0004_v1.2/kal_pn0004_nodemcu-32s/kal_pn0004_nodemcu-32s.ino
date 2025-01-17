// projektnummer      : kal_pn0004
// datum              : 25.12.2023
// version            : v1.2
// software by        : makinghub
// ohne webserver

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>


#include <FS.h>
#include <SD.h>
#include <SPI.h>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define luefter 26 // pin für relais/ luefter
//sensoren 
#define sens_aussen 15   //signal pin für dht22 sensor aussen
#define sens_innen  16    //signal pin für dht22 sensor innen


#define dhttype    DHT22     // sensortyp DHT 22 (AM2302)


DHT_Unified dht_aussen (sens_aussen, dhttype);
DHT_Unified dht_innen (sens_innen, dhttype);


double temp_aussen, temp_innen, hum_aussen, hum_innen;
uint32_t delayMS;
int counter = 0; 
String luefter_start ;
String luefter_stop ;

String str_hum_aussen;
String str_hum_innen;
String str_temp_aussen;
String str_temp_innen;

const double Mw = 18.016; // molekulargewicht wasserdampf in kg/kmol
const double Ur = 8314.3; // universelle gaskonstante in J (kmol*K)
double a_innen,b_innen, a_aussen, b_aussen ; // zusatzwerte abh. von >0>
double DD_aussen, DD_innen; // dampfdruck innen/aussen
double hum_abs_innen, hum_abs_aussen; // absolute luftfeuchtigkeint innen/aussen
String str_abs_hum_innen, str_abs_hum_aussen;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// define the SD card pins
#define CS  5
#define MOSI  23
#define MISO  19
#define SCK 18

// initialize the SPI bus
SPIClass spi(VSPI);

File datalog;

int timer = 0;


void setup() {

  Serial.begin(9600);
////////////////////////////////////////////////////////////////////
spi.begin(SCK,MISO,MOSI,CS);
if(!SD.begin(5)){
    Serial.println("Card Mount Failed");
    return;
  }
  

/////////////////////////////////////////////////////////////////////
  // pinmode für relais pin
  pinMode(luefter, OUTPUT);
  pinMode(21, OUTPUT);
  // Initialize device.

  dht_aussen.begin();
  dht_innen.begin();

  Serial.println(F("kal_pn0004, version: v1.0 "));

//////////////////////////////////////////////////////////////////////

  // Print temperature sensor details.
  sensor_t sensor;
  dht_aussen.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));

  // Print humidity sensor details.
  dht_aussen.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;

  timer = millis();
}






void loop() 
{

  // pin 21 wird als extra spannungsquelle verwendet, deshalb dauerhaft high
  digitalWrite(21,HIGH);

  // aufruf der funktionen 
 
  get_value_innen();
  get_value_aussen();
  hum_abs();
  relay_control();
  datalogging();
 

  // Delay between measurements.
  delay(delayMS);

 

  
 
}
