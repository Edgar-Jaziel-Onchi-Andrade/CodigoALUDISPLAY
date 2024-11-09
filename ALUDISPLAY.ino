int displayPins[] = {1, 2, 3, 4, 5, 6, 7};
int signPin = 0;
int btnA = 8;
int btnB = 9;
int btnOperacion1 = 10;
int btnOperacion2 = 11;
int btnOperacion3 = 12;
int btnOperacion4 = 13;
int A = 0;
int B = 0;
int operacion = 0;

byte numbers[3][7] = {
  {HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH},
  {HIGH, LOW, HIGH, LOW, LOW, LOW, LOW},
  {LOW, HIGH, HIGH, HIGH, LOW, HIGH, HIGH}
};

byte undefinedPattern[7] = {LOW, HIGH, LOW, LOW, LOW, LOW, LOW};

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(displayPins[i], OUTPUT);
  }
  pinMode(signPin, OUTPUT);
  pinMode(btnA, INPUT);
  pinMode(btnB, INPUT);
  pinMode(btnOperacion1, INPUT);
  pinMode(btnOperacion2, INPUT);
  pinMode(btnOperacion3, INPUT);
  pinMode(btnOperacion4, INPUT);
}

void loop() {
  A = digitalRead(btnA);
  B = digitalRead(btnB);
  int estadoOperacion1 = digitalRead(btnOperacion1);
  int estadoOperacion2 = digitalRead(btnOperacion2);
  int estadoOperacion3 = digitalRead(btnOperacion3);
  int estadoOperacion4 = digitalRead(btnOperacion4);

  if (A == 0 && B == 0 && estadoOperacion1 == LOW && estadoOperacion2 == LOW && estadoOperacion3 == LOW && estadoOperacion4 == LOW) {
    apagarDisplays();
    return;
  }

  operacion = (estadoOperacion1 << 3) | (estadoOperacion2 << 2) | (estadoOperacion3 << 1) | estadoOperacion4;

  int resultado = 0;
  bool negativo = false;

  switch (operacion) {
    case 1:
      resultado = A + B;
      break;

    case 2:
      resultado = A - B;
      if (resultado < 0) {
        resultado = -resultado;
        negativo = true;
      }
      break;

    case 3:
      resultado = A * B;
      break;

    case 4:
      if (A == 0 && B == 0) {
        mostrarIndefinido();
        return;
      } else if (A == 1 && B == 0) {
        mostrarInfinito();
        return;
      } else if (B != 0) {
        resultado = A / B;
      }
      break;

    case 5:
      resultado = A & B;
      break;

    case 6:
      resultado = A | B;
      break;

    case 7:
      resultado = !A;
      break;

    case 8:
      resultado = A ^ B;
      break;

    case 9:
      resultado = !(A ^ B);
      break;

    case 10:
      resultado = !(A & B);
      break;

    default:
      resultado = 0;
      break;
  }

  mostrarNumero(resultado, negativo);
  delay(1000);
}

void mostrarNumero(int num, bool negativo) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(displayPins[i], numbers[num][i]);
  }
  digitalWrite(signPin, negativo ? HIGH : LOW);
}

void mostrarIndefinido() {
  apagarDisplays();
  digitalWrite(displayPins[0], HIGH);
}

void mostrarInfinito() {
  apagarDisplays();
  for (int i = 0; i < 7; i++) {
    digitalWrite(displayPins[i], undefinedPattern[i]);
  }
  digitalWrite(signPin, HIGH);
}

void apagarDisplays() {
  for (int i = 0; i < 7; i++) {
    digitalWrite(displayPins[i], LOW);
  }
  digitalWrite(signPin, LOW);
}
