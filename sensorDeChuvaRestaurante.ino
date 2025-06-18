/**************Restaurante Sutaki - Controle de Tenda Automatizado*******************/

// Pinos de controle do motor
 int IN1 = 6;  
 int IN2 = 5;  

// Sensor de chuva analógico
 int sensorChuva = A1;

// Sensor de luminosidade - LDR
 int sensorLuz = A3;

//Limite para luz (valores abaixo de 400 indicam luz)
 int valorLuz = 400;

// Limite para detectar chuva (valores abaixo de 512 indicam presença de chuva)
 int valorChuva = 512;

// Estado atual da tenda: true = fechada, false = aberta
bool tendaFechada = false;

// Armazena os valores lidos de Chuva e Luz
int leituraChuva = 0;
int leituraLuz = 0;

void setup() {

  // Configura os pinos do motor como saída
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Inicializa a comunicação serial
  Serial.begin(9600);

  // Motor parado no início
  pararMotor();

  //
  leituraLuz = analogRead(sensorLuz);
  leituraChuva = analogRead(sensorChuva);

  // Verifica o estado inicial da tenda com base na iluminação
  if (leituraLuz < valorLuz) {
    tendaFechada = false;  
    Serial.println("Muita luz - Tenda ABERTA");
  } else {
    tendaFechada = true;
    Serial.println("Pouca Luz- Tenda FECHADA");
  }


}

void loop() {
  //verificação se está chovendo
  leituraChuva = analogRead(sensorChuva); 

  // Detecta chuva: fecha a tenda se estiver aberta
  if (leituraChuva < valorChuva && !tendaFechada) {
    Serial.println("Chuva detectada - Fechando tenda");
    fecharTenda();
    tendaFechada = true;
  }

  // Sem chuva: abre a tenda se estiver fechada
  if (leituraChuva >= valorChuva && tendaFechada) {
    Serial.println("Sem chuva - Abrindo tenda");
    abrirTenda();
    tendaFechada = false;
  }

  delay(1000); // Aguarda 1 segundo antes da próxima leitura
}

// Abre a tenda (motor gira no sentido anti-horário)
void abrirTenda() {
  analogWrite(IN1, 80);
  analogWrite(IN2, 0);
  delay(2800);
  pararMotor();
  delay(3000);
}

// Fecha a tenda (motor gira no sentido horário)
void fecharTenda() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 80);
  delay(2800); 
  pararMotor();
  delay(3000);
}

// Para o motor
void pararMotor() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
}
