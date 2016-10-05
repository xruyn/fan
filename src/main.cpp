/* Вытяжной вентилятор на Pro Mini, DS1307, DHT22 и фоторезисторе. Вентилятор управляется твердотельным реле */
#include <Arduino.h>
#include <RTClib.h>
#include <Wire.h>
#include <DHT.h>
#define DHTPIN 10   //пин для подключения DHT
#define DHTTYPE DHT22 //выбор датчика
DHT dht(DHTPIN, DHTTYPE); // инициализация DHT
RTC_DS1307 rtc;       //выбор DS


int pin_relay = 8; //пин для управление реле (выход)
int pin_photores = 9; //пин для подключения фоторезистора (вход)
byte hum_summer = 60;
byte hum_winter = 38;
byte temp = 30;
// byte month_;
// byte day;
// byte hour;
// byte minute;

void setup() {
        Serial.begin(9600);
        Wire.begin();
        rtc.begin();
        dht.begin();
        pinMode(pin_relay, OUTPUT);
        pinMode(pin_photores, INPUT);
        pinMode(13, OUTPUT);

}
//now.month()>3 && now.month()<9
//dht.readHumidity()>65  && dht.readTemperature()>29
void loop() {
        DateTime now = rtc.now();
        if (digitalRead(pin_photores) == LOW) {
                if (now.month()>3 && now.month()<9) {     //летний  период
                        if (dht.readHumidity()>65  && dht.readTemperature()>28) {
                                delay(2500);
                                if (dht.readHumidity()>hum_summer) {
                                        digitalWrite(pin_relay, LOW); //включаем вентилятор пока не опуститься
                                }
                                else {digitalWrite(pin_relay, HIGH); }
                        }
                }
                else {

                        if (dht.readHumidity()>47  && dht.readTemperature()>28) { //зимний  период
                                delay(2500);
                                if (dht.readHumidity()>hum_winter) {
                                        digitalWrite(pin_relay, LOW); //включаем вентилятор пока не опуститься
                                }
                                else {digitalWrite(pin_relay, HIGH); }
                        }
                }
        }
        else {digitalWrite(pin_relay, HIGH); }

}
