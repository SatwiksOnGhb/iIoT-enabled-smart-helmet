/*#include <DHT.h>
#include <math.h> // For isnan()

// Pin definitions
#define MQ135_PIN A0
#define MQ7_PIN   A1
#define DHTPIN    2
#define IR_PIN    3
#define TRIG_PIN  9
#define ECHO_PIN  10

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Buzzer timer logic removed, not needed now

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(IR_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // Read sensor values
  int mq135Value = analogRead(MQ135_PIN);
  int mq7Value = analogRead(MQ7_PIN);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int irStatus = digitalRead(IR_PIN);

  // Ultrasonic distance measurement
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout
  int distance = -1;
  if (duration > 0) {
    distance = duration * 0.034 / 2;
  }

  // Display sensor values
  Serial.println("---- Monitoring Data ----");
  Serial.print("Air quality: "); Serial.println(mq135Value);
  Serial.print("Carbon monoxide: "); Serial.println(mq7Value);
  if (distance > 0) {
    Serial.print("Distance: "); Serial.print(distance); Serial.println(" cm");
  } else {
    Serial.println("Ultrasonic sensor error or out of range.");
  }

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT read failed!");
  } else {
    Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" °C");
    Serial.print("Humidity: "); Serial.print(humidity); Serial.println(" %");
  }

  Serial.print("Motion: ");
  if (irStatus == LOW) {
    Serial.println("Triggered");
  } else {
    Serial.println("Normal");
  }
  Serial.println("--------------------------");

  // Hazard detection (for serial feedback only)
  bool hazard = false;

  if (mq135Value > 300) {
    Serial.println("Warning: Air quality too poor.");
    hazard = true;
  }

  if (mq7Value > 250) {
    Serial.println("Warning: Carbon monoxide too high.");
    hazard = true;
  }

  if (distance > 0 && distance < 30) {
    Serial.println("Warning: Obstacle very close.");
    hazard = true;
  }

  if (!isnan(temperature)) {
    if (temperature > 45) {
      Serial.println("Warning: Temperature too high.");
      hazard = true;
    } else if (temperature < 0) {
      Serial.println("Warning: Temperature too low.");
      hazard = true;
    }
  }

  if (!isnan(humidity)) {
    if (humidity > 80) {
      Serial.println("Warning: Humidity too high.");
      hazard = true;
    } else if (humidity < 20) {
      Serial.println("Warning: Humidity too low.");
      hazard = true;
    }
  }

  if (irStatus == LOW) {
    Serial.println("Warning: Motion or impact detected.");
    hazard = true;
  }

  delay(1000);
}*/



/*
#include <DHT.h>
#include <math.h> // For isnan()

// Pin definitions
#define MQ135_PIN A0
#define MQ7_PIN   A1
#define DHTPIN    2
#define IR_PIN    3
#define TRIG_PIN  9
#define ECHO_PIN  10
#define ALERT_PIN 8    // Red LED + Buzzer combo
#define GREEN_LED 7

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(IR_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(ALERT_PIN, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  // IMPORTANT: First line must be titles ONLY for Serial Plotter
  Serial.println("Temperature\tHumidity\tDistance\tAirQ\tCO");
}

void loop() {
  // Sensor readings
  int mq135Value = analogRead(MQ135_PIN);
  int mq7Value = analogRead(MQ7_PIN);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int irStatus = digitalRead(IR_PIN);

  // Ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout
  int distance = (duration > 0) ? duration * 0.034 / 2 : -1;

  // === Serial Plotter Output ===
  if (!isnan(temperature) && !isnan(humidity) && distance > 0) {
    Serial.print(temperature); Serial.print("\t");
    Serial.print(humidity); Serial.print("\t");
    Serial.print(distance); Serial.print("\t");
    Serial.print(mq135Value); Serial.print("\t");
    Serial.println(mq7Value);
  } else {
    // Send dummy data to keep plot consistent
    Serial.println("0\t0\t0\t0\t0");
  }

  // === Hazard detection ===
  bool hazard = false;
  if (mq135Value > 300) hazard = true;
  if (mq7Value > 250) hazard = true;
  if (distance > 0 && distance < 30) hazard = true;
  if (!isnan(temperature) && (temperature > 45 || temperature < 0)) hazard = true;
  if (!isnan(humidity) && (humidity > 80 || humidity < 20)) hazard = true;

  // === LED/Buzzer response ===
  if (hazard) {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(ALERT_PIN, HIGH);
    delay(200);
    digitalWrite(ALERT_PIN, LOW);
    delay(200);
  } else {
    digitalWrite(ALERT_PIN, LOW);
    digitalWrite(GREEN_LED, HIGH);
    delay(500);
    digitalWrite(GREEN_LED, LOW);
    delay(500);
  }
}
*/
/*
#include <DHT.h>
#include <math.h> // For isnan()

// Pin definitions
#define MQ135_PIN A0
#define MQ7_PIN   A1
#define DHTPIN    2
#define IR_PIN    3
#define TRIG_PIN  9
#define ECHO_PIN  10
#define ALERT_PIN 8    // Red LED + Buzzer combo
#define GREEN_LED 7

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(IR_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(ALERT_PIN, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  // First line for Serial Plotter labels
  Serial.println("Temperature\tHumidity\tDistance\tAirQ\tCO");
}

void loop() {
  // Sensor readings
  int mq135Value = analogRead(MQ135_PIN);
  int mq7Value = analogRead(MQ7_PIN);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int irStatus = digitalRead(IR_PIN);

  // Ultrasonic measurement
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout
  int distance = (duration > 0) ? duration * 0.034 / 2 : -1;

  // === Human-readable output ===
  Serial.println("---- Monitoring Data ----");
  Serial.print("Air quality: "); Serial.println(mq135Value);
  Serial.print("Carbon monoxide: "); Serial.println(mq7Value);
  if (distance > 0) {
    Serial.print("Distance: "); Serial.print(distance); Serial.println(" cm");
  } else {
    Serial.println("Ultrasonic sensor error or out of range.");
  }

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT read failed!");
  } else {
    Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" °C");
    Serial.print("Humidity: "); Serial.print(humidity); Serial.println(" %");
  }

  Serial.print("Motion: ");
  if (irStatus == LOW) {
    Serial.println("Triggered");
  } else {
    Serial.println("Normal");
  }
  Serial.println("--------------------------");

  // === Serial Plotter line (must be printed every loop) ===
  if (!isnan(temperature) && !isnan(humidity) && distance > 0) {
    Serial.print(temperature); Serial.print("\t");
    Serial.print(humidity); Serial.print("\t");
    Serial.print(distance); Serial.print("\t");
    Serial.print(mq135Value); Serial.print("\t");
    Serial.println(mq7Value);
  } else {
    Serial.println("0\t0\t0\t0\t0");
  }

  // === Hazard detection ===
  bool hazard = false;
  if (mq135Value > 300) hazard = true;
  if (mq7Value > 250) hazard = true;
  if (distance > 0 && distance < 30) hazard = true;
  if (!isnan(temperature) && (temperature > 45 || temperature < 0)) hazard = true;
  if (!isnan(humidity) && (humidity > 80 || humidity < 20)) hazard = true;

  // === LED and buzzer alert system ===
  if (hazard) {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(ALERT_PIN, HIGH);
    delay(200);
    digitalWrite(ALERT_PIN, LOW);
    delay(200);
  } else {
    digitalWrite(ALERT_PIN, LOW);
    digitalWrite(GREEN_LED, HIGH);
    delay(500);
    digitalWrite(GREEN_LED, LOW);
    delay(500);
  }
}
*/
/*
#include <DHT.h>
#define MQ135_PIN A0
#define MQ7_PIN   A1
#define DHTPIN    2
#define IR_PIN    3
#define TRIG_PIN  9
#define ECHO_PIN  10
#define ALERT_PIN 8
#define GREEN_LED 7
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

bool showLogs = true;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(IR_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(ALERT_PIN, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  delay(200);
  Serial.println("Temperature\tHumidity\tDistance\tAirQuality\tCO");
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int mq135Value = analogRead(MQ135_PIN);
  int mq7Value = analogRead(MQ7_PIN);
  int irStatus = digitalRead(IR_PIN);

  // Handle invalid values
  if (isnan(temperature)) temperature = 0;
  if (isnan(humidity)) humidity = 0;

  // Ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  int distance = (duration > 0) ? duration * 0.034 / 2 : 0;

  // Serial Plotter data (must be tab-separated in same order as header)
  Serial.print(temperature); Serial.print("\t");
  Serial.print(humidity); Serial.print("\t");
  Serial.print(distance); Serial.print("\t");
  Serial.print(mq135Value); Serial.print("\t");
  Serial.println(mq7Value);

  // Serial Monitor log
  if (showLogs) {
    Serial.println("--------------------------");
    Serial.print("Air Quality: "); Serial.println(mq135Value);
    Serial.print("Carbon Monoxide: "); Serial.println(mq7Value);
    Serial.print("Distance: "); Serial.print(distance); Serial.println(" cm");
    Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" °C");
    Serial.print("Humidity: "); Serial.print(humidity); Serial.println(" %");
    Serial.print("Motion: ");
    Serial.println((irStatus == LOW) ? "Triggered" : "Normal");
    Serial.println("--------------------------");
  }

  // Hazard detection
  bool hazard = false;
  if (mq135Value > 300) hazard = true;
  if (mq7Value > 250) hazard = true;
  if (distance > 0 && distance < 30) hazard = true;
  if (temperature > 45 || temperature < 0) hazard = true;
  if (humidity > 80 || humidity < 20) hazard = true;

  // LED/Buzzer logic
  if (hazard) {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(ALERT_PIN, HIGH);
    delay(200);
    digitalWrite(ALERT_PIN, LOW);
    delay(200);
  } else {
    digitalWrite(ALERT_PIN, LOW);
    digitalWrite(GREEN_LED, HIGH);
    delay(500);
    digitalWrite(GREEN_LED, LOW);
    delay(500);
  }
}
*/
/*
#include <DHT.h>
#include <WiFiS3.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>

#define MQ135_PIN A0
#define MQ7_PIN   A1
#define DHTPIN    2
#define IR_PIN    3
#define TRIG_PIN  9
#define ECHO_PIN  10
#define ALERT_PIN 8
#define GREEN_LED 7
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// WiFi credentials
const char* ssid     = "Amit";
const char* password = "9741112942";

// ThingSpeak settings
WiFiClient client;
unsigned long channelID = 3010670;            // Replace with your channel ID
const char* writeAPIKey = "6XZH4ZDL1UUEMTE7";       // Replace with your Write API Key

bool showLogs = true;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(IR_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(ALERT_PIN, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  delay(200);
  Serial.println("Temperature\tHumidity\tDistance\tAirQuality\tCO");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int mq135Value = analogRead(MQ135_PIN);
  int mq7Value = analogRead(MQ7_PIN);
  int irStatus = digitalRead(IR_PIN);

  if (isnan(temperature)) temperature = 0;
  if (isnan(humidity)) humidity = 0;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  int distance = (duration > 0) ? duration * 0.034 / 2 : 0;

  // Serial Plotter data
  Serial.print(temperature); Serial.print("\t");
  Serial.print(humidity); Serial.print("\t");
  Serial.print(distance); Serial.print("\t");
  Serial.print(mq135Value); Serial.print("\t");
  Serial.println(mq7Value);

  // Serial Monitor log
  if (showLogs) {
    Serial.println("--------------------------");
    Serial.print("Air Quality: "); Serial.println(mq135Value);
    Serial.print("Carbon Monoxide: "); Serial.println(mq7Value);
    Serial.print("Distance: "); Serial.print(distance); Serial.println(" cm");
    Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" °C");
    Serial.print("Humidity: "); Serial.print(humidity); Serial.println(" %");
    Serial.print("Motion: ");
    Serial.println((irStatus == LOW) ? "Triggered" : "Normal");
    Serial.println("--------------------------");
  }

  // ThingSpeak upload
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  ThingSpeak.setField(3, distance);
  ThingSpeak.setField(4, mq135Value);
  ThingSpeak.setField(5, mq7Value);

  int status = ThingSpeak.writeFields(channelID, writeAPIKey);
  if (status == 200) {
    Serial.println("Data sent to ThingSpeak successfully.");
  } else {
    Serial.print("Error sending data to ThingSpeak. HTTP code: ");
    Serial.println(status);
  }

  // Hazard detection
  bool hazard = false;
  if (mq135Value > 300) hazard = true;
  if (mq7Value > 250) hazard = true;
  if (distance > 0 && distance < 30) hazard = true;
  if (temperature > 45 || temperature < 0) hazard = true;
  if (humidity > 80 || humidity < 20) hazard = true;

  // LED/Buzzer logic
  if (hazard) {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(ALERT_PIN, HIGH);
    delay(200);
    digitalWrite(ALERT_PIN, LOW);
    delay(200);
  } else {
    digitalWrite(ALERT_PIN, LOW);
    digitalWrite(GREEN_LED, HIGH);
    delay(500);
    digitalWrite(GREEN_LED, LOW);
    delay(500);
  }
  delay(15000);
}
*/
/*
#include <DHT.h>
#include <WiFiS3.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>

#define MQ135_PIN A0
#define MQ7_PIN   A1
#define DHTPIN    2
#define IR_PIN    3
#define TRIG_PIN  9
#define ECHO_PIN  10
#define ALERT_PIN 8
#define GREEN_LED 7
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// WiFi credentials
const char* ssid     = "Amit";
const char* password = "9741112942";

// ThingSpeak settings
WiFiClient client;
unsigned long channelID = 3010670;            // Replace with your channel ID
const char* writeAPIKey = "6XZH4ZDL1UUEMTE7";       // Replace with your Write API Key

bool showLogs = true;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(IR_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(ALERT_PIN, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  delay(200);
  Serial.println("Temperature\tHumidity\tDistance\tAirQuality\tCO");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int mq135Value = analogRead(MQ135_PIN);
  int mq7Value = analogRead(MQ7_PIN);
  int irStatus = digitalRead(IR_PIN);

  if (isnan(temperature)) temperature = 0;
  if (isnan(humidity)) humidity = 0;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  int distance = (duration > 0) ? duration * 0.034 / 2 : 0;

  // Serial Plotter data
  Serial.print(temperature); Serial.print("\t");
  Serial.print(humidity); Serial.print("\t");
  Serial.print(distance); Serial.print("\t");
  Serial.print(mq135Value); Serial.print("\t");
  Serial.println(mq7Value);

  // Serial Monitor log
  if (showLogs) {
    Serial.println("--------------------------");
    Serial.print("Air Quality: "); Serial.println(mq135Value);
    Serial.print("Carbon Monoxide: "); Serial.println(mq7Value);
    Serial.print("Distance: "); Serial.print(distance); Serial.println(" cm");
    Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" °C");
    Serial.print("Humidity: "); Serial.print(humidity); Serial.println(" %");
    Serial.print("Motion: ");
    Serial.println((irStatus == LOW) ? "Triggered" : "Normal");
    Serial.println("--------------------------");
  }

  // ThingSpeak upload
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  ThingSpeak.setField(3, distance);
  ThingSpeak.setField(4, mq135Value);
  ThingSpeak.setField(5, mq7Value);

  int status = ThingSpeak.writeFields(channelID, writeAPIKey);
  if (status == 200) {
    Serial.println("Data sent to ThingSpeak successfully.");
  } else {
    Serial.print("Error sending data to ThingSpeak. HTTP code: ");
    Serial.println(status);
  }

  // Hazard detection
  bool hazard = false;
  if (mq135Value > 300) hazard = true;
  if (mq7Value > 250) hazard = true;
  if (distance > 0 && distance < 30) hazard = true;
  if (temperature > 45 || temperature < 0) hazard = true;
  if (humidity > 80 || humidity < 20) hazard = true;

  // LED/Buzzer logic
  if (hazard) {
    Serial.println("Hazard detected. Red LED blinking.");
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(ALERT_PIN, HIGH);
    delay(200);
    digitalWrite(ALERT_PIN, LOW);
    delay(200);
  } else {
    Serial.println("All conditions safe. Green LED blinking.");
    digitalWrite(ALERT_PIN, LOW);
    digitalWrite(GREEN_LED, HIGH);
    delay(500);
    digitalWrite(GREEN_LED, LOW);
    delay(500);
  }
  delay(1000);
}
*/
#include <DHT.h>
#include <WiFiS3.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>

#define MQ135_PIN A0
#define MQ7_PIN   A1
#define DHTPIN    2
#define IR_PIN    3
#define TRIG_PIN  9
#define ECHO_PIN  10
#define ALERT_PIN 8
#define GREEN_LED 7
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// WiFi credentials
const char* ssid     = "Galaxy M218EB9";
const char* password = "qxwf4041";

// ThingSpeak settings
WiFiClient client;
unsigned long channelID = 3010670;
const char* writeAPIKey = "6XZH4ZDL1UUEMTE7";

bool showLogs = true;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(IR_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(ALERT_PIN, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  delay(200);
  Serial.println("Temperature\tHumidity\tDistance\tAirQuality\tCO");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int mq135Value = analogRead(MQ135_PIN);
  int mq7Value = analogRead(MQ7_PIN);
  int irStatus = digitalRead(IR_PIN);

  if (isnan(temperature)) temperature = 0;
  if (isnan(humidity)) humidity = 0;

  // Ultrasonic sensor with timeout handling
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 24000); // 30ms timeout
  int distance = (duration > 0) ? duration * 0.034 / 2 : -1;

  // Serial Plotter data
  Serial.print(temperature); Serial.print("\t");
  Serial.print(humidity); Serial.print("\t");
  Serial.print((distance == -1) ? 0 : distance); Serial.print("\t"); // Use 0 for plotting if out of range
  Serial.print(mq135Value); Serial.print("\t");
  Serial.println(mq7Value);

  // Serial Monitor log
  if (showLogs) {
    Serial.println("--------------------------");
    Serial.print("Air Quality: "); Serial.println(mq135Value);
    Serial.print("Carbon Monoxide: "); Serial.println(mq7Value);

    Serial.print("Distance: ");
    if (distance == -1) Serial.println("Out of range");
    else Serial.print(distance), Serial.println(" cm");

    Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" °C");
    Serial.print("Humidity: "); Serial.print(humidity); Serial.println(" %");
    Serial.print("Motion: ");
    Serial.println((irStatus == LOW) ? "Triggered" : "Normal");
    Serial.println("--------------------------");
  }

  // ThingSpeak upload (use -1 if distance is out of range)
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  ThingSpeak.setField(3, (distance == -1) ? -1 : distance);
  ThingSpeak.setField(4, mq135Value);
  ThingSpeak.setField(5, mq7Value);

  int status = ThingSpeak.writeFields(channelID, writeAPIKey);
  if (status == 200) {
    Serial.println("Data sent to ThingSpeak successfully.");
  } else {
    Serial.print("Error sending data to ThingSpeak. HTTP code: ");
    Serial.println(status);
  }

  // Hazard detection
  bool hazard = false;
  if (mq135Value > 300) hazard = true;
  if (mq7Value > 250) hazard = true;
  if (distance != -1 && distance < 30) hazard = true;
  if (temperature > 45 || temperature < 0) hazard = true;
  if (humidity > 80 || humidity < 20) hazard = true;

  // LED/Buzzer logic
  if (hazard) {
    Serial.println("Hazard detected. Red LED blinking.");
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(ALERT_PIN, HIGH);
    delay(200);
    digitalWrite(ALERT_PIN, LOW);
    delay(200);
  } else {
    Serial.println("All conditions safe. Green LED blinking.");
    digitalWrite(ALERT_PIN, LOW);
    digitalWrite(GREEN_LED, HIGH);
    delay(500);
    digitalWrite(GREEN_LED, LOW);
    delay(500);
  }

  delay(15000);
}


