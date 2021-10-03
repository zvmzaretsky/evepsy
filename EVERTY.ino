#include <MsTimer2.h>                                           //timer library for clock

#include <Wire.h>                                               //I2C library for display
#include <LiquidCrystal_I2C.h>                                  //1602 display library
LiquidCrystal_I2C lcd(0x27, 16, 2);                             //display config

#include <TroykaDHT.h>                                          //DHT temp sensor library
DHT dht(2, DHT22);                                              //DHT config

uint64_t mili_dht;                                              //timeout DHT variable
float    h, t;                                                  //humidity & temperature variables

uint32_t  pin_vent  = 8;                                        //fan pin
uint32_t  pin_heat  = 4;                                        //heater pin
uint32_t  pin_light = 9;                                        //led strip pin (mosfet)
uint32_t  pin_mist  = 7;                                        //humidifier pin

uint32_t  t_min = 18;                                           //max & min maintained temperature
uint32_t  t_max = 22;
uint32_t  h_min = 65;                                           //max & min maintained humidity
uint32_t  h_max = 80;

uint32_t  t_gis = 2;                                            //temperature gisteresis
uint32_t  h_gis = 5;                                            //humidity gisteresis

uint32_t  bright = 0;                                           //LED strip brightness 


uint32_t hours = 0, minutes = 0, seconds = 0;                   //clock variables

//every second the second variable is incremented by one. Time is counted with it help  
void clockFunction(){                                            
    seconds++;                                                   
    if(seconds == 60){minutes++; seconds = 0;}
    if(minutes == 60){hours++; minutes = 0; seconds = 0;}
    if(hours   == 24){hours=0; minutes = 0; seconds = 0;}

    //changing lighting throughout the day
    switch(hours){
        case  5: {bright =  20; break;}
        case  6: {bright =  30; break;}
        case  7: {bright =  50; break;}
        case  8: {bright =  70; break;}
        case  9: {bright = 100; break;}
        case 10: {bright = 140; break;}
        case 11: {bright = 200; break;}
        case 12: {bright = 255; break;}
        case 13: {bright = 255; break;}
        case 14: {bright = 255; break;}
        case 15: {bright = 255; break;}
        case 16: {bright = 255; break;}
        case 17: {bright = 200; break;}
        case 18: {bright = 140; break;}
        case 19: {bright = 100; break;}
        case 20: {bright =  70; break;}
        case 21: {bright =  50; break;}
        case 22: {bright =  30; break;}
        case 23: {bright =  20; break;}
        default: {bright =   0; break;}
    }
    analogWrite(pin_light, bright);
}

void setup()
{   
    //setup pins as outputs
    pinMode (pin_vent,  OUTPUT);
    pinMode (pin_heat,  OUTPUT);
    pinMode (pin_light, OUTPUT);
    pinMode (pin_mist,  OUTPUT);

    //open Serial port for debug
    Serial.begin(9600);

    //turn on DHT
    dht.begin();

    //setup clock timer 
    MsTimer2::set(1000, clockFunction);                     
    MsTimer2::start();

    //turn on LCD display
    lcd.begin();
    lcd.backlight();

    //output "Scientific Mandarins"
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Scientific");
    lcd.setCursor(7, 1);
    lcd.print("Mandarins");

    //output start message 
    Serial.print("Start");
    _delay_ms(1000);
}

void loop()
{
    //parsing temperature and humidity 
    if (millis() - mili_dht > 5000) {
        mili_dht = millis();
        dht.read();
    
        switch(dht.getState()) {
            //read data from DHT
            case DHT_OK:
                 t = dht.getTemperatureC();                     //saving data to variables
                 h = dht.getHumidity();
                 Serial.println(t);
                 Serial.println(h);

                 //send data to display 
                 lcd.clear();
                 lcd.setCursor(0, 0);
                 lcd.print("Temperature: ");                    //display temperature
                 lcd.print(t);
                 lcd.print("°");
                 lcd.print("C");

                 lcd.setCursor(0, 1);
                 lcd.print("Humidity: ");                       //display humidity
                 lcd.print(h);
                 lcd.print("%");
            break;

            //ERROR messages
            case DHT_ERROR_CHECKSUM:
                Serial.println("Checksum error");
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("-- ERROR DHT --");
            break;

            case DHT_ERROR_TIMEOUT:
                Serial.println("Time out error");
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("-- ERROR DHT --");
            break;

            case DHT_ERROR_NO_REPLY:
                Serial.println("Sensor not connected");
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("-- ERROR DHT --");
            break;
        }
    }

    //temperature control
    if (t > t_max - t_gis) {                                    
        digitalWrite (pin_vent, HIGH);                          //if temperature is high - turn on fan
        digitalWrite (pin_heat, LOW);                           //if temperature is high - turn off heater
    }
    else if (t >= (t_min + t_gis) && t <= (t_max - t_gis)) {
        digitalWrite (pin_vent, LOW);                           //if temperature is normal - turn off fan
        digitalWrite (pin_heat, LOW);                           //if temperature is normal - turn off heater
    }
    else if (t < t_min + t_gis) {
        digitalWrite (pin_vent, LOW);                           //if temperature is low - turn off fan
        digitalWrite (pin_heat, HIGH);                          //if temperature is low - turn on heater
    }

    //humidity control
    if (h > h_max - h_gis) {
        digitalWrite (pin_mist, LOW);                           //if humidity is high - turn off humidifier
        digitalWrite (pin_vent, HIGH);                          //if humidity is high - turn on fan
    }
    else if (h >= h_min + h_gis && h <= h_max - h_gis) {
        digitalWrite (pin_mist, LOW);                           //if humidity is normal - turn off humidifier
        digitalWrite (pin_vent, LOW);                           //if humidity is normal - turn off fan
    }
    else if (h < h_min + h_gis) {
        digitalWrite (pin_mist, HIGH);                          //if humidity is low - turn on humidifier
        digitalWrite (pin_vent, LOW);                           //if humidity is low - turn off fan
    }
}
