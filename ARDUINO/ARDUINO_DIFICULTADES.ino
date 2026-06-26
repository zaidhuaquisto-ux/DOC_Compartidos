#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// 📌 Configuración de Pines Estabilizada
const int ledVerde = 5;
const int ledRojo = 13;
const int btnVerde = 4;   
const int btnRojo = 12;   
const int buzzer = 9;

// 🔊 SONIDO INICIO DE ETAPA
void soundStart() {
  tone(buzzer, 800); delay(100);
  noTone(buzzer); delay(30);
  tone(buzzer, 1200); delay(120);
  noTone(buzzer);
}

// 🔊 SONIDO DE ACIERTO
void soundSuccess() {
  tone(buzzer, 600); delay(100);
  tone(buzzer, 800); delay(100);
  tone(buzzer, 1000); delay(200);
  noTone(buzzer);
}

// 🔊 SONIDO DE ERROR / DISTRACCIÓN
void soundError() {
  tone(buzzer, 300); delay(300);
  tone(buzzer, 150); delay(400);
  noTone(buzzer);
}

// 🔊 DESTELLO CORTO DE UN LED
void destellarLED(int pinLED) {
  digitalWrite(pinLED, HIGH);
  tone(buzzer, 1500); 
  delay(150);
  digitalWrite(pinLED, LOW);
  noTone(buzzer);
}

// 📜 FUNCIÓN CON TU NUEVO TEXTO MODIFICADO
int ejecutarFaseDeLectura() {
  // 📝 Tu nuevo mensaje integrado de forma exacta (con espacios iniciales y finales para el efecto visual)
  String mensaje = "   EL CEREBRO HUMANO PROCESA MILES DE DATOS VISUALES POR SEGUNDO PERO EL ENTORNO PUEDE ATRAPAR TU ATENCION, DESVIANDO TU ENFOQUE Y LIMITANDO TU PERCEPCION CONSCIENTE...   ";
  
  int conteoVerde = 0;
  int conteoRojo = 0;
  
  lcd.clear();
  soundStart();
  delay(200);

  for (int i = 0; i < mensaje.length() - 16; i++) {
    String fragmento = mensaje.substring(i, i + 16);
    
    // 📺 Fila superior: Texto en movimiento
    lcd.setCursor(0, 0);
    lcd.print(fragmento);
    
    // 📺 Fila inferior: Limpia
    lcd.setCursor(0, 1);
    lcd.print("                "); 
    
    // 🚦 NUEVA DISTRIBUCIÓN MATEMÁTICA DE DESTELLOS
    // Verde parpadea 6 veces
    if (i == 22 || i == 44 || i == 66 || i == 88 || i == 110 || i == 132) { 
      destellarLED(ledVerde);
      conteoVerde++;
    }
    // Rojo parpadea 4 veces
    if (i == 31 || i == 62 || i == 93 || i == 124) { 
      destellarLED(ledRojo);
      conteoRojo++;
    }

    delay(300); 
  }
  
  return (conteoVerde > conteoRojo) ? btnVerde : btnRojo;
}

// 📜 FUNCIÓN AUXILIAR PARA EL SCROLL CON EL DIAGNÓSTICO
void mostrarExplicacionScroll(String explicacion) {
  for (int i = 0; i < explicacion.length() - 16; i++) {
    lcd.setCursor(0, 0);
    lcd.print(explicacion.substring(i, i + 16));
    lcd.setCursor(0, 1);
    lcd.print("                "); 
    delay(280); 
  }
}

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  pinMode(btnVerde, INPUT);        
  pinMode(btnRojo, INPUT_PULLUP);  

  lcd.setCursor(0, 0);
  lcd.print("TEST PSICOLOGICO");
  lcd.setCursor(0, 1);
  lcd.print("PULSA CUALQUIERA");

  while (digitalRead(btnVerde) == LOW && digitalRead(btnRojo) == HIGH) { delay(10); }
  delay(200); 
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("    LEE CON     ");
  lcd.setCursor(0, 1);
  lcd.print("   ATENCION!    ");
  delay(2000); 

  int botonGanador = ejecutarFaseDeLectura();
  
  lcd.clear();
  lcd.print("TERMINO EL TEXTO");
  delay(1500);
  
  // Pregunta en dos filas sin los nombres de los botones abajo
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("QUE LUZ BRILLO ");
  lcd.setCursor(0, 1);
  lcd.print("   MAS VECES?   ");
  
  int botonPresionado = 0;

  // Bucle infinito sin tiempo límite hasta que se pulse un botón
  while (true) {
    if (digitalRead(btnVerde) == HIGH) { 
      botonPresionado = btnVerde;
      break;
    }
    if (digitalRead(btnRojo) == LOW) { 
      botonPresionado = btnRojo;
      break;
    }
    delay(10);
  }

  // RESPUESTA FINAL PERSONALIZADA EN SCROLL
  lcd.clear();
  if (botonPresionado == botonGanador) {
    // 1. Mensaje grande por 2 segundos
    lcd.setCursor(0, 0);
    lcd.print("   CORRECTO!    ");
    digitalWrite(ledVerde, HIGH);
    soundSuccess();
    delay(2000); 
    digitalWrite(ledVerde, LOW);
    
    // 2. Scroll con la frase exacta solicitada
    String msgCorrecto = "   Eres independiente de entorno.      ";
    mostrarExplicacionScroll(msgCorrecto);
  } 
  else {
    // 1. Mensaje grande por 2 segundos
    lcd.setCursor(0, 0);
    lcd.print("  INCORRECTO!   ");
    digitalWrite(ledRojo, HIGH);
    soundError();
    delay(2000); 
    digitalWrite(ledRojo, LOW);
    
    // 2. Scroll con la frase exacta solicitada
    String msgIncorrecto = "   Eres dependiente de entorno.      ";
    mostrarExplicacionScroll(msgIncorrecto);
  }

  // Pantalla de Espera para Reinicio
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TEST COMPLETADO");
  lcd.setCursor(0, 1);
  lcd.print("PULSA P/ REINICIO");

  while (digitalRead(btnVerde) == HIGH || digitalRead(btnRojo) == LOW) { delay(10); }
  while (digitalRead(btnVerde) == LOW && digitalRead(btnRojo) == HIGH) { delay(10); }
  delay(200); 
  
  return; 
}
