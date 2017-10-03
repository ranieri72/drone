#include <Servo.h>

Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;

const int posMotor1 = 0;
const int posMotor2 = 0;
const int posMotor3 = 0;
const int posMotor4 = 0;

int velInput;
int velMotor;
int numMotor;

char tecla;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial && (millis() < 10000)) ;

  motor1.attach(posMotor1);
  motor2.attach(posMotor2);
  motor3.attach(posMotor3);
  motor4.attach(posMotor4);

  velInput = 50;
  numMotor = 1;
  Serial.println("Digite uma opcao:");
  Serial.println("[1-4] - selecionara um motor");
  Serial.println("W - Acelerar");
  Serial.println("S - Desacelerar");
  Serial.println("P - Parar");
}

void loop() {
  
  // put your main code here, to run repeatedly:
  tecla = Serial.read();
  // TODO procurar codigo de filtragem
  switch (tecla) {
    case 'w':
      velInput = velInput + 10;
      calcularInputVelocidade();
      break;
    case 's':
      velInput = velInput - 10;
      calcularInputVelocidade();
      break;
    case 'p':
      velInput = 0;
      calcularInputVelocidade();
      break;
    case '1':
      numMotor = 1;
      break;
    case '2':
      numMotor = 2;
      break;
    case '3':
      numMotor = 3;
      break;
    case '4':
      numMotor = 4;
      break;
    default:
      //Serial.println("Tecla inválida!");
      break;
  }
}

void calcularInputVelocidade() {
  if (velInput != 0) {

    if (velInput < 50) {
      velInput = 50;
      Serial.println("Velocidade minima permitida!");
      return;
    }
    if (velInput > 100) {
      velInput = 100;
      Serial.println("Velocidade maxima permitida!");
      return;
    }
    
    Serial.println("Velocidade recalculada");
    Serial.print(" - Motor:"); Serial.println(numMotor);
    Serial.print(" - Velocidade:"); Serial.println(velInput);
  } else {
    Serial.println("Motor parado");
  }
  velMotor = map(velInput, 0, 100, 0, 179);
  alterarVelocidade();
}

void alterarVelocidade() {
  switch (numMotor) {
    case 1:
      motor1.write(velMotor);
      break;
    case 2:
      motor2.write(velMotor);
      break;
    case 3:
      motor3.write(velMotor);
      break;
    case 4:
      motor4.write(velMotor);
      break;
  }
}

