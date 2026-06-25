#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <avr/wdt.h>  // Librería para el watchdog

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int led1 = 6;
const int led2 = 7;
const int soundSensorAO = A0; // AO conectado al pin A0
const int buzzer = 9;

const int repeats = 4;
const int durationSeconds = 10;

// Umbrales separados. para calibrar el inicio y el reinicio. Se pueden ajustar según el entorno y la sensibilidad del sensor de sonido.
int umbralInicio = 522;
int umbralReinicio = 520;

// 🔊 SONIDO INICIO
void soundStart() {
  tone(buzzer, 800); delay(120);
  noTone(buzzer); delay(50);
  tone(buzzer, 1000); delay(120);
  noTone(buzzer); delay(50);
  tone(buzzer, 1200); delay(150);
  noTone(buzzer);
}

// 🔊 SONIDO FINAL
void soundEnd() {
  tone(buzzer, 523); delay(150);
  tone(buzzer, 659); delay(150);
  tone(buzzer, 784); delay(200);
  noTone(buzzer);
}

// 👂 DETECTAR APLAUSO (máximo en 200 ms con umbral configurable)
bool detectarAplauso(int umbral) {
  int maxValor = 0;
  unsigned long inicio = millis();

  // lee durante 200 ms y guarda el máximo
  while (millis() - inicio < 200) {
    int valor = analogRead(soundSensorAO);
    if (valor > maxValor) {
      maxValor = valor;
    }
  }

  Serial.print("Max: "); Serial.print(maxValor);
  Serial.print(" / Umbral: "); Serial.println(umbral);

  // ESTA PARTE ES PARA DEBUG, SE PUEDE COMENTAR PARA NO MOSTRAR EN LCD ////


  // lcd.clear();
  // lcd.setCursor(0, 0);
  // lcd.print("Max:");
  // lcd.print(maxValor);
  // lcd.setCursor(0, 1);
  // lcd.print("Umbral:");
  // lcd.print(umbral);

  if (maxValor > umbral) {
    return true;
  }
  return false;
}

// 🔄 REINICIO REAL
void reiniciarArduino() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("REINICIANDO...");
  delay(500);
  wdt_enable(WDTO_15MS); // watchdog en 15 ms
  while (true) {
    // espera a que ocurra el reset
  }
}

// 📊 PROGRESO
void mostrar(String texto, int sec, int total) {
  int percent = (sec * 100) / total;
  int bars = map(sec, 0, total, 0, 16);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(texto);

  lcd.setCursor(10, 0);
  lcd.print(percent);
  lcd.print("%");

  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    if (i < bars) lcd.write(byte(255));
    else lcd.print("-");
  }
}

// ⏱ ETAPA
void etapa(String texto, int led) {
  digitalWrite(led1, led == led1);
  digitalWrite(led2, led == led2);

  soundStart(); // 🔊 suena al empezar cada etapa

  for (int s = 1; s <= durationSeconds; s++) {
    mostrar(texto, s, durationSeconds);

    // 👀 Si detecta aplauso durante la etapa, reinicia el Arduino
    if (detectarAplauso(umbralReinicio)) {
      reiniciarArduino();
    }

    delay(1000);
  }
}

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("APLAUDE");
  lcd.setCursor(0, 1);
  lcd.print("PARA EMPEZAR (:");

  // 🔥 Espera aplauso para iniciar
  while (!detectarAplauso(umbralInicio)) {
    delay(10);
  }
  soundStart();
}

void loop() {
  for (int i = 0; i < repeats; i++) {
    etapa("Estudio", led1);

    if (i == repeats - 1) {
      etapa("Desc largo", led2);
    } else {
      etapa("Desc corto", led2);
    }
  }

  // 🏁 FINAL
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BIEN HECHO");
  lcd.setCursor(0, 1);
  lcd.print("FELICITACIONES");
  soundEnd();
  delay(2500);

  // 🔥 Espera aplauso para reiniciar
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("APLAUDE");
  lcd.setCursor(0, 1);
  lcd.print("PARA REINICIAR");

  while (!detectarAplauso(umbralReinicio)) {
    delay(10);
  }
  reiniciarArduino(); // reinicio total
}
