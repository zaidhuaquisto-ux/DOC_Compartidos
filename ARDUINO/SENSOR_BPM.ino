#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128   // ancho de la pantalla OLED
#define SCREEN_HEIGHT 64   // alto de la pantalla OLED
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define SENSOR_PIN A0      // pin analógico donde conectas el sensor de pulso
#define LED_PIN 13         // pin digital para el LED indicador

#define GRAPH_HEIGHT 40    // altura de la gráfica en la pantalla
#define GRAPH_WIDTH 128    // ancho de la gráfica (igual al ancho de la OLED)

int sensorValue = 0;
int lastSensorValue = 0;
int bpm = 0;
unsigned long lastBeatTime = 0;
unsigned long interval = 0;

// buffer para almacenar los puntos de la gráfica
int graph[GRAPH_WIDTH];

void setup() {
  pinMode(SENSOR_PIN, INPUT);   // configurar pin del sensor como entrada
  pinMode(LED_PIN, OUTPUT);     // configurar pin del LED como salida
  Serial.begin(9600);           // iniciar comunicación serial para depuración

  // inicializar pantalla OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("No se encontró la pantalla OLED"));
    for (;;); // detener si no encuentra la pantalla
  }

  display.clearDisplay();
  display.display();
  Serial.println("Coloca el dedo y espera unos segundos...");
}

void loop() {
  sensorValue = analogRead(SENSOR_PIN);   // leer valor del sensor
  unsigned long currentTime = millis();   // tiempo actual en ms

  // LED sigue la onda del sensor (brillo proporcional a la señal)
  analogWrite(LED_PIN, map(sensorValue, 0, 1023, 0, 255));

  // --- DETECCIÓN DE LATIDOS ---
  // Solo calcular BPM si el dedo está puesto (valores razonables)
  if (sensorValue > 200 && sensorValue < 900) {
    if (sensorValue > lastSensorValue + 10 && (currentTime - lastBeatTime > 600)) {
      interval = currentTime - lastBeatTime;   // tiempo entre latidos
      lastBeatTime = currentTime;
      bpm = 60000 / interval;                  // calcular BPM
      digitalWrite(LED_PIN, HIGH);             // parpadeo fuerte en latido
    }
  } else {
    bpm = 0;                  // 🚨 sin dedo → BPM = 0 forzado
    lastBeatTime = currentTime; // reiniciar tiempo para no arrastrar valores
  }

  lastSensorValue = sensorValue;

  // --- GRÁFICA ---
  // desplazar valores en el buffer
  for (int i = 0; i < GRAPH_WIDTH - 1; i++) {
    graph[i] = graph[i + 1];
  }
  // mapear señal al alto de la gráfica
  graph[GRAPH_WIDTH - 1] = map(sensorValue, 0, 1023, 0, GRAPH_HEIGHT);

  display.clearDisplay();

  // dibujar línea de la gráfica
  for (int x = 0; x < GRAPH_WIDTH - 1; x++) {
    display.drawLine(x, GRAPH_HEIGHT - graph[x], x + 1, GRAPH_HEIGHT - graph[x + 1], SSD1306_WHITE);
  }

  // --- TEXTO DEL BPM ---
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, GRAPH_HEIGHT + 5);
  display.print("BPM:");
  display.setCursor(70, GRAPH_HEIGHT + 5);
  display.print(bpm);

  display.display();

  delay(20); // pequeña pausa para estabilidad
}


// 🔌 CONEXIONES
// 1. Pantalla OLED (I2C con pines GND, VDD, SCK, SDA):
//    - GND → GND del Arduino
//    - VDD → 5V del Arduino (o 3.3V si tu OLED solo soporta 3.3V)
//    - SCK → pin A5 del Arduino (SCL en I2C)
//    - SDA → pin A4 del Arduino (SDA en I2C)
//
// 2. Sensor de pulso (KY-039 o similar):
//    - Salida analógica → pin A0 del Arduino
//    - VCC → 5V del Arduino
//    - GND → GND del Arduino
//
// 3. LED indicador:
//    - Ánodo (+) → pin 13 del Arduino (con resistencia de 220Ω–330Ω en serie)
//    - Cátodo (–) → GND
//
// ⚙️ FUNCIONAMIENTO DEL CÓDIGO
// - La OLED muestra arriba la gráfica de la señal del sensor.
// - Abajo aparece el texto con el BPM calculado.
// - El LED sigue la onda y parpadea fuerte en cada latido detectado.
// - Sin dedo → el BPM se fuerza a 0 y la gráfica se queda plana.
// - Con dedo → la gráfica muestra curvas y el BPM refleja tu pulso real.
//
// 🧪 PRUEBA
// 1. Conecta todo según las indicaciones.
// 2. Sube el código al Arduino.
// 3. Coloca el dedo sobre el sensor → verás curvas en la gráfica y un BPM realista (60–100 aprox en reposo).
// 4. Suelta el dedo → el BPM baja a 0 y la gráfica se aplana.

