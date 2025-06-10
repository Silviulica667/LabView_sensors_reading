#include <DHT.h>

// === Pin Definitions ===
const int MQ2_AO = A0;
const int MQ2_DO = 2;

const int MQ9_AO = A1;
const int MQ9_DO = 3;

const int MQ135_AO = A2;
const int MQ135_DO = 4;

#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  
  pinMode(MQ2_DO, INPUT);
  pinMode(MQ9_DO, INPUT);
  pinMode(MQ135_DO, INPUT);
  
  dht.begin();
}

void loop() {
  int mq2Analog = analogRead(MQ2_AO);
  int mq9Analog = analogRead(MQ9_AO);
  int mq135Analog = analogRead(MQ135_AO);

  float mq2_percent = (mq2Analog / 1023.0) * 100.0;
  float mq9_percent = (mq9Analog / 1023.0) * 100.0;
  float mq135_percent = (mq135Analog / 1023.0) * 100.0;

  int mq2Digital = digitalRead(MQ2_DO);
  int mq9Digital = digitalRead(MQ9_DO);
  int mq135Digital = digitalRead(MQ135_DO);

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (!isnan(temperature) && !isnan(humidity)) {
    float heatIndex = dht.computeHeatIndex(temperature, humidity, false);

    // === OUTPUT CSV LINE ===
    Serial.print(mq2_percent, 1); Serial.print(",");
    Serial.print(mq2Digital); Serial.print(",");
    Serial.print(mq9_percent, 1); Serial.print(",");
    Serial.print(mq9Digital); Serial.print(",");
    Serial.print(mq135_percent, 1); Serial.print(",");
    Serial.print(mq135Digital); Serial.print(",");
    Serial.print(temperature, 1); Serial.print(",");
    Serial.print(humidity, 1); Serial.print(",");
    Serial.println(heatIndex, 1);
  }
}
