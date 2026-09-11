#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Configuración OLED
#define ANCHO 128
#define ALTO 64
Adafruit_SSD1306 display(ANCHO, ALTO, &Wire, -1);

// Pines LEDs
int ledRojo = 3;
int ledVerde = 5;

// Variables para controlar LEDs con millis()
unsigned long ultimoCambioLED = 0;
int estadoLED = 0; // 0=verde, 1=rojo, 2=apagado

void dibujarCorazon() {
  display.clearDisplay();
  display.fillCircle(40, 20, 15, SSD1306_WHITE);  // círculo izquierdo
  display.fillCircle(80, 20, 15, SSD1306_WHITE);  // círculo derecho
  display.fillTriangle(25, 25, 95, 25, 60, 60, SSD1306_WHITE); // triángulo abajo
  display.display();
}

void animarBPM(int tiempo_ms) {
  unsigned long start = millis();
  int x = 0;

  while (millis() - start < tiempo_ms) {
    display.clearDisplay();

    // Línea base
    display.drawLine(0, 40, ANCHO, 40, SSD1306_WHITE);

    // Dibujar varios picos altos y bajos tipo zig-zag
    for (int i = 0; i < ANCHO; i += 25) {
      int baseX = (x + i) % ANCHO;
      display.drawLine(baseX, 40, baseX+5, 15, SSD1306_WHITE);   // pico alto
      display.drawLine(baseX+5, 15, baseX+10, 60, SSD1306_WHITE); // bajada fuerte
      display.drawLine(baseX+10, 60, baseX+15, 30, SSD1306_WHITE); // rebote medio
      display.drawLine(baseX+15, 30, baseX+25, 40, SSD1306_WHITE); // regreso a base
    }

    display.display();

    // Control de LEDs con millis()
    unsigned long ahora = millis();
    if (estadoLED == 0 && ahora - ultimoCambioLED >= 3000) {
      // Verde estuvo 3s → ahora rojo
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledRojo, HIGH);
      estadoLED = 1;
      ultimoCambioLED = ahora;
    } else if (estadoLED == 1 && ahora - ultimoCambioLED >= 500) {
      // Rojo estuvo 0.5s → ahora apagado
      digitalWrite(ledRojo, LOW);
      estadoLED = 2;
      ultimoCambioLED = ahora;
    } else if (estadoLED == 2 && ahora - ultimoCambioLED >= 3000) {
      // Apagado 3s → ahora verde
      digitalWrite(ledVerde, HIGH);
      estadoLED = 0;
      ultimoCambioLED = ahora;
    }

    delay(50); // velocidad de animación
    x += 4;    // avanzar animación
  }

  // Apagar LEDs al terminar
  digitalWrite(ledRojo, LOW);
  digitalWrite(ledVerde, LOW);
}

void setup() {
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);

  // Inicializar OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for(;;); // si falla, se queda aquí
  }

  randomSeed(analogRead(A0)); // semilla para aleatorios

  // Arrancar con verde encendido
  digitalWrite(ledVerde, HIGH);
  estadoLED = 0;
  ultimoCambioLED = millis();
}

void loop() {
  // Escena 1: Latido BPM animado (10 segundos)
  animarBPM(10000);

  // Escena 2: Corazón grande (2 segundos)
  dibujarCorazon();
  digitalWrite(ledVerde, HIGH);
  delay(2000);
  digitalWrite(ledVerde, LOW);
}
