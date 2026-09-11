#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSansBold12pt7b.h>


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
  display.setFont(&FreeSansBold18pt7b);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10,40);
  display.println("Listo!");
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
    display.setFont(&FreeMonoBold24pt7b);
    display.setCursor(50,50);
    display.println("0");
    display.display();
  }

  // Rojo
  if (digitalRead(btnRojo) == LOW) {
    digitalWrite(ledRojo, HIGH);
    tone(buzzer, 1200, 200);   // beep musical 1200 Hz
    delay(2000);
    digitalWrite(ledRojo, LOW);

    display.clearDisplay();
    display.setFont(&FreeMonoBold24pt7b);
    display.setCursor(50,50);
    display.println("1");
    display.display();
  }

  // Amarillo
  if (digitalRead(btnAmarillo) == LOW) {
    digitalWrite(ledAmarillo, HIGH);
    tone(buzzer, 800, 200);    // beep musical 800 Hz
    delay(2000);
    digitalWrite(ledAmarillo, LOW);

    display.clearDisplay();
    display.setFont(&FreeMonoBold24pt7b);
    display.setCursor(50,50);
    display.println("2");
    display.display();
  }

  // Verde
  if (digitalRead(btnVerde) == LOW) {
    digitalWrite(ledVerde, HIGH);
    tone(buzzer, 1500, 200);   // beep musical 1500 Hz
    delay(2000);
    digitalWrite(ledVerde, LOW);

    display.clearDisplay();
    display.setFont(&FreeMonoBold24pt7b);
    display.setCursor(50,50); //50
    display.println("3");
    display.display();
  }
}


/*
🔌 CONEXIONES

LEDs:
- Azul → Pin 2 (ánodo con resistencia a pin, cátodo a GND)
- Rojo → Pin 3
- Amarillo → Pin 4
- Verde → Pin 5

Botones:
- Azul → Pin 6 (pata arriba derecha al pin, pata abajo izquierda a GND)
- Rojo → Pin 7
- Amarillo → Pin 8
- Verde → Pin 9

Buzzer:
- Pin 10 → pata larga (+)
- GND → pata corta (–)

⚙️ FUNCIONAMIENTO
- Cada botón enciende su LED por 2 segundos.
- El buzzer suena un beep corto (~200 ms) al inicio de cada pulsación.
- Al soltar el botón, el LED igual se apaga automáticamente después de 2 segundos.
*/

// 🔌 CONEXIONES
// 1. Pantalla OLED (I2C con pines GND, VDD, SCK, SDA):
//    - GND → GND del Arduino
//    - VDD → 5V del Arduino (o 3.3V si tu OLED solo soporta 3.3V)
//    - SCK → pin A5 del Arduino (SCL en I2C)
//    - SDA → pin A4 del Arduino (SDA en I2C)