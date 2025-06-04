/**************Restaurante Sutaki - Controle de Tenda Automatizado*******************/

// Pinos de controle do motor
const int IN1 = 6;  
const int IN2 = 5;  

// Sensor de chuva analógico
const int sensorChuva = A1;

// Limite para detectar chuva (valores abaixo indicam presença de chuva)
const int valorChuva = 512;


// Estado atual da tenda: true = fechada, false = aberta
bool tendaFechada = false;

void setup() {

  // Configura os pinos do motor como saída
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Inicializa a comunicação serial
  Serial.begin(9600);

  // Motor parado no início
  pararMotor();
}

void loop() {
  int leitura = analogRead(sensorChuva);
  
  Serial.print("Valor do sensor: ");
  Serial.println(leitura);


  // Detecta chuva: fecha a tenda se estiver aberta
  if (leitura < valorChuva && !tendaFechada) {
    Serial.println("Chuva detectada - Fechando tenda");
    fecharTenda();
    tendaFechada = true;
  }

  // Sem chuva: abre a tenda se estiver fechada
  if (leitura >= valorChuva && tendaFechada) {
    Serial.println("Sem chuva - Abrindo tenda");
    abrirTenda();
    tendaFechada = false;
  }

  delay(500); // Aguarda meio segundo antes da próxima leitura
}

// Abre a tenda (motor gira no sentido anti-horário)
void abrirTenda() {
  analogWrite(IN1, 80);
  analogWrite(IN2, 0);
  delay(2800);
  pararMotor();
  delay(2000);
}

// Fecha a tenda (motor gira no sentido horário)
void fecharTenda() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 80);
  delay(2800); 
  pararMotor();
  delay(2000);
}

// Para o motor
void pararMotor() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
}
