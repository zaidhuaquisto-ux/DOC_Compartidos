#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSans9pt7b.h>   // incluir la fuente pequeña

// Fuentes elegantes
#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>

// Configuración OLED
#define ANCHO 128
#define ALTO 64
Adafruit_SSD1306 display(ANCHO, ALTO, &Wire, -1);

// Pines LEDs
int ledAzul = 2;
int ledRojo = 3;
int ledAmarillo = 4;
int ledVerde = 5;

// Pines Botones
int btnAzul = 6;
int btnRojo = 7;
int btnAmarillo = 8;
int btnVerde = 9;

// Buzzer
int buzzer = 10;

void setup() {
  pinMode(ledAzul, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledVerde, OUTPUT);

  pinMode(btnAzul, INPUT_PULLUP);
  pinMode(btnRojo, INPUT_PULLUP);
  pinMode(btnAmarillo, INPUT_PULLUP);
  pinMode(btnVerde, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);

  // Inicializar OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for(;;); // si falla, se queda aquí
  }
  display.clearDisplay();
  display.setFont(&FreeSans9pt7b);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10,40);
  display.println("A responder!");
  display.display();
  delay(2000);
}

void loop() {
  // Azul
  if (digitalRead(btnAzul) == LOW) {
    digitalWrite(ledAzul, HIGH);
    tone(buzzer, 1000, 200);   // beep musical 1000 Hz, 200 ms
    delay(2000);
    digitalWrite(ledAzul, LOW);

    display.clearDisplay();
    display.setFont(&FreeSans9pt7b);
    display.setCursor(0,20);
    display.println("No estoy          seguro"); //AZUL
    display.display();
  }

  // Rojo
  if (digitalRead(btnRojo) == LOW) {
    digitalWrite(ledRojo, HIGH);
    tone(buzzer, 1200, 200);   // beep musical 1200 Hz
    delay(2000);
    digitalWrite(ledRojo, LOW);

    display.clearDisplay();
    display.setFont(&FreeSans9pt7b);
    display.setCursor(0,20);
    display.println("No lo recuerdo");  //ROJO
    display.display();
  }

  // Amarillo
  if (digitalRead(btnAmarillo) == LOW) {
    digitalWrite(ledAmarillo, HIGH);
    tone(buzzer, 800, 200);    // beep musical 800 Hz
    delay(2000);
    digitalWrite(ledAmarillo, LOW);

    display.clearDisplay();
    display.setFont(&FreeSans9pt7b);
    display.setCursor(0,20);
    display.println("Lo recuerdo un            poco");
    display.display();
  }

  // Verde
  if (digitalRead(btnVerde) == LOW) {
    digitalWrite(ledVerde, HIGH);
    tone(buzzer, 1500, 200);   // beep musical 1500 Hz
    delay(2000);
    digitalWrite(ledVerde, LOW);

    display.clearDisplay();
    display.setFont(&FreeSans9pt7b);
    display.setCursor(0,20);
    display.println("Lo recuerdo      perfectamente"); //VERDE
    display.display();
  }
}
