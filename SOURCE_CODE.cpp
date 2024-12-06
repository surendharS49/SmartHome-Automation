#include <LiquidCrystal.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Pin Definitions
#define Light 7
#define machine 6
#define Fan 5

// LCD setup
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

// Blynk Authentication Token and WiFi credentials
#define BLYNK_TEMPLATE_ID "TMPL32-RAo_rP"
#define BLYNK_TEMPLATE_NAME "Home Automation"
#define BLYNK_AUTH_TOKEN "k9a63h01j22qPs063IZF-blsrzvXhuek"
#define BLYNK_PRINT Serial
char ssid[] = "projectiot2023";
char pass[] = "";

// Setup function
void setup()
{
  // Initialize Serial and LCD
  Serial.begin(9600);
  lcd.begin(16, 2);

  // Set pin modes for devices
  pinMode(Light, OUTPUT);
  pinMode(machine, OUTPUT);
  pinMode(Fan, OUTPUT);

  // Initialize Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Display Initial Message on LCD
  lcd.setCursor(0, 0);
  lcd.print("IOT BASED HOME");
  lcd.setCursor(0, 1);
  lcd.print("AUTOMATION SYS");
  delay(2000);
  lcd.clear();
}

// Blynk control for light (V0)
BLYNK_WRITE(V0)
{
  int value = param.asInt();
  if (value == 1) {
    Serial.print('A');  // Turn Light ON
  } else {
    Serial.print('a');  // Turn Light OFF
  }
}

// Blynk control for machine (V1)
BLYNK_WRITE(V1)
{
  int value = param.asInt();
  if (value == 1) {
    Serial.print('B');  // Turn Machine ON
  } else {
    Serial.print('b');  // Turn Machine OFF
  }
}

// Blynk control for fan (V2)
BLYNK_WRITE(V2)
{
  int value = param.asInt();
  if (value == 1) {
    Serial.print('C');  // Turn Fan ON
  } else {
    Serial.print('c');  // Turn Fan OFF
  }
}

// Synchronize virtual pins when connected to Blynk
BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V0);
  Blynk.syncVirtual(V1);
  Blynk.syncVirtual(V2);
}

// Main loop function
void loop()
{
  Blynk.run();

  if (Serial.available() > 0) {
    char Y = Serial.read();

    // Control Light
    if (Y == 'A') {
      digitalWrite(Light, HIGH);
      lcd.setCursor(0, 0);
      lcd.print("Light-ON ");
    } else if (Y == 'a') {
      digitalWrite(Light, LOW);
      lcd.setCursor(0, 0);
      lcd.print("Light-OFF");
    }

    // Control Machine
    else if (Y == 'B') {
      digitalWrite(machine, HIGH);
      lcd.setCursor(0, 1);
      lcd.print("Machine-ON ");
    } else if (Y == 'b') {
      digitalWrite(machine, LOW);
      lcd.setCursor(0, 1);
      lcd.print("Machine-OFF");
    }

    // Control Fan
    else if (Y == 'C') {
      digitalWrite(Fan, HIGH);
      lcd.setCursor(10, 0);
      lcd.print("Fan-ON");
    } else if (Y == 'c') {
      digitalWrite(Fan, LOW);
      lcd.setCursor(10, 0);
      lcd.print("Fan-OFF");
    }
  }
}
