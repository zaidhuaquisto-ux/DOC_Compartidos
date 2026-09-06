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
}

void loop() {
  // Azul
  if (digitalRead(btnAzul) == LOW) {
    digitalWrite(ledAzul, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(200);                 // beep corto
    digitalWrite(buzzer, LOW);
    delay(1800);                // resto del tiempo LED encendido
    digitalWrite(ledAzul, LOW);
  }

  // Rojo
  if (digitalRead(btnRojo) == LOW) {
    digitalWrite(ledRojo, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    delay(1800);
    digitalWrite(ledRojo, LOW);
  }

  // Amarillo
  if (digitalRead(btnAmarillo) == LOW) {
    digitalWrite(ledAmarillo, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    delay(1800);
    digitalWrite(ledAmarillo, LOW);
  }

  // Verde
  if (digitalRead(btnVerde) == LOW) {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    delay(1800);
    digitalWrite(ledVerde, LOW);
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
