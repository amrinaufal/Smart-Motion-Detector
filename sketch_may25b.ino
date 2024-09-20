#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_TEMPLATE_ID           "TMPL6tkKI3HVl"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "jLf0gU-fdeNeyKLfAcgBbc_ZtsjFJgXc"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "OPPO ANANE";
char pass[] = "tulisenae";

BlynkTimer timer;

// Pin sensor PIR
const int pirPin = 15;
const int LED1 = 2;
const int LED2 = 4;
const int Buzzer = 5;

// Variabel penanda status deteksi gerakan
bool motionDetected = false;

void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);

  pinMode(pirPin, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(Buzzer, OUTPUT);
}

void loop()
{
  Blynk.run();
  timer.run();

  // Membaca nilai sensor PIR
  int pirValue = digitalRead(pirPin);

  if (pirValue == HIGH && !motionDetected) {
    // Gerakan terdeteksi, kirim status ke Blynk
    motionDetected = true;
    Blynk.virtualWrite(V0, 1);
    Serial.println("Gerakan Terdeteksi");

    tone(Buzzer, 800);
    digitalWrite(LED2, LOW);
    blinkLed();

    delay(500);

  } else if (pirValue == LOW && motionDetected) {
    // Tidak ada gerakan, reset status deteksi gerakan
    motionDetected = false;
    Blynk.virtualWrite(V0, 0);
    Serial.println("Tidak ada Gerakan Terdeteksi");
    digitalWrite(LED2, HIGH);
    digitalWrite(Buzzer, LOW);
    noTone(Buzzer);
  }
  delay(100);
}

void myTimerEvent() {
  // Kirim waktu aktif Arduino ke Blynk
  Blynk.virtualWrite(V2, millis() / 1000);
}

void blinkLed() {
  // Blink the LED for 20 seconds
  unsigned long startTime = millis();
  while (millis() - startTime < 20000) {
    digitalWrite(LED1, HIGH);
    delay(500);
    digitalWrite(LED1, LOW);
    delay(500);
  }
}
