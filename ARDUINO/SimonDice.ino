#include <EEPROM.h>

// Buzzer
#define altavoz 10

// LEDs
#define rojo 2
#define verde 3
#define amarillo 4
#define azul 5

// Botones
#define botonrojo 6
#define botonverde 7
#define botonamarillo 8
#define botonazul 9

int aleatorio, dir_lectura, dir_escritura, color_leido, leido, color_pulsado, nivel;
boolean fin_juego;

// --- Funciones auxiliares ---
void retardo(int latencia) {
  latencia = nivel;
  switch (latencia) {
    case 1: delay(300); break;
    case 2: delay(200); break;
    case 3: delay(75); break;
    case 4: delay(5); break;
    default: break;
  }
}

void sonido(int tono) {
  int i, j;
  for (i = 0; i <= 40; i++) {
    for (j = 0; j <= 4; j++) {
      digitalWrite(altavoz, HIGH);
      delayMicroseconds(90 * (6 - tono));
      digitalWrite(altavoz, LOW);
      delayMicroseconds(90 * (6 - tono));
    }
  }
}

void enciende_led(int color) {
  switch (color) {
    case 1: digitalWrite(rojo, HIGH); break;
    case 2: digitalWrite(verde, HIGH); break;
    case 3: digitalWrite(amarillo, HIGH); break;
    case 4: digitalWrite(azul, HIGH); break;
    default: digitalWrite(rojo, HIGH); digitalWrite(verde, HIGH);
             digitalWrite(amarillo, HIGH); digitalWrite(azul, HIGH); break;
  }
}

void apaga_leds() {
  digitalWrite(rojo, LOW);
  digitalWrite(verde, LOW);
  digitalWrite(amarillo, LOW);
  digitalWrite(azul, LOW);
}

void antirebote() {
  delay(30);
  while (digitalRead(botonrojo) != 1 || digitalRead(botonverde) != 1 ||
         digitalRead(botonamarillo) != 1 || digitalRead(botonazul) != 1) { }
  delay(30);
}

void comprueba() {
  leido = EEPROM.read(dir_lectura);
  if (leido != color_pulsado) fin_juego = true;
}

void genera_aleatorio() {
  if (aleatorio == 4) aleatorio = 1;
  else aleatorio++;
}

void guarda_color() {
  EEPROM.write(dir_escritura, aleatorio);
  dir_escritura++;
}

void animacion_inicio() {
  for (int i = 0; i < 3; i++) {
    enciende_led(5);
    sonido(1);
    delay(200);
    apaga_leds();
    delay(200);
  }
}

void feedback_acierto() {
  enciende_led(5);
  sonido(1);
  sonido(2);
  sonido(4);
  delay(150);
  apaga_leds();
}

void has_fallado(int tono) {
  for (int i = 0; i < 3; i++) {
    digitalWrite(rojo, HIGH);
    sonido(tono);
    delay(200);
    digitalWrite(rojo, LOW);
    delay(200);
  }
  apaga_leds();
  delay(1000);
}

void muestra_colores() {
  apaga_leds();
  retardo(nivel);

  for (dir_lectura = 0; dir_lectura < dir_escritura; dir_lectura++) {
    color_leido = EEPROM.read(dir_lectura);
    enciende_led(color_leido);
    sonido(color_leido);
    retardo(nivel);
    apaga_leds();
    retardo(nivel);
  }
}

void pulsa_secuencia() {
  boolean sal;
  dir_lectura = 0;
  aleatorio = 1;

  while ((dir_lectura < dir_escritura) && (!fin_juego)) {
    sal = false;
    while (!sal) {
      genera_aleatorio();
      if (digitalRead(botonrojo) == LOW) { color_pulsado = 1; sal = true; }
      else if (digitalRead(botonverde) == LOW) { color_pulsado = 2; sal = true; }
      else if (digitalRead(botonamarillo) == LOW) { color_pulsado = 3; sal = true; }
      else if (digitalRead(botonazul) == LOW) { color_pulsado = 4; sal = true; }
    }
    comprueba();
    enciende_led(color_pulsado);
    sonido(color_pulsado);
    antirebote();
    apaga_leds();
    dir_lectura++;
  }
}

// --- Setup y Loop ---
void setup() {
  pinMode(botonrojo, INPUT_PULLUP);
  pinMode(botonverde, INPUT_PULLUP);
  pinMode(botonamarillo, INPUT_PULLUP);
  pinMode(botonazul, INPUT_PULLUP);

  pinMode(rojo, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(amarillo, OUTPUT);
  pinMode(azul, OUTPUT);
  pinMode(altavoz, OUTPUT);

  apaga_leds();

  nivel = 1; // arranca directamente en nivel 1
  animacion_inicio(); // animación de bienvenida
}

void loop() {
  dir_escritura = dir_lectura = color_leido = leido = color_pulsado = 0;
  fin_juego = false;
  aleatorio = 1;

  guarda_color();  // primer color aleatorio

  while (!fin_juego) {
    muestra_colores();
    pulsa_secuencia();
    guarda_color();

    if (!fin_juego) {
      feedback_acierto();
      retardo(nivel);
    }
  }

  has_fallado(4);
  delay(1000);
}

/*
🔌 CONEXIONES
- LED rojo → Pin 2
- LED verde → Pin 3
- LED amarillo → Pin 4
- LED azul → Pin 5
- Botón rojo → Pin 6
- Botón verde → Pin 7
- Botón amarillo → Pin 8
- Botón azul → Pin 9
- Buzzer → Pin 10
*/
