void setup() {
  pinMode(8, OUTPUT);   // Rojo
  pinMode(7, OUTPUT);   // Amarillo
  pinMode(0, OUTPUT);   // Verde

  // Inicialmente todos apagados
  digitalWrite(8, LOW);
  digitalWrite(7, LOW);
  digitalWrite(0, LOW);
}

void loop() {
  // Rojo encendido 3 segundos
  digitalWrite(8, HIGH);
  delay(3000);

  // Amarillo se suma al rojo (ambos encendidos) por 1 segundo
  digitalWrite(7, HIGH);
  delay(1000);

  // Verde se enciende y los otros se apagan → 3 segundos
  digitalWrite(8, LOW);
  digitalWrite(7, LOW);
  digitalWrite(0, HIGH);
  delay(3000);

  // Apagar verde para reiniciar ciclo
  digitalWrite(0, LOW);
}
