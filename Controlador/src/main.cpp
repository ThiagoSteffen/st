#include <Arduino.h>
#include <HardwareSerial.h>
#include <LovyanGFX.hpp>
#include "SPIFFS.h"

LGFX lcd;  // Objeto do display
HardwareSerial RS485Serial(1); // Configura Serial1 para RS485


// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
Serial.begin(115200);  // Inicia a comunicação serial para depuração
    lcd.init();  // Inicializa o display
    lcd.setRotation(1);  // Rotaciona o display se necessário

    // Inicializa o sistema de arquivos SPIFFS
    if (!SPIFFS.begin(true)) {
        Serial.println("Falha ao montar o SPIFFS");
        return;

         // Carrega e exibe a imagem
    if (lcd.drawBmpFile(SPIFFS, "/IMAGEM/fundo.bmp", 0, 0)) {
        Serial.println("Imagem carregada com sucesso!");
    } else {
        Serial.println("Falha ao carregar a imagem");
    }
  // Inicialização da RS485
    RS485Serial.begin(9600, SERIAL_8N1);  // Configura a comunicação RS485 com baud rate de 9600
    pinMode(2, OUTPUT);  // Configura o pino 2 como saída para controle DE/RE (pode variar conforme sua placa)
    digitalWrite(2, LOW);  // Define o pino 2 inicialmente como recepção
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  // Exemplo de envio de dados via RS485
    digitalWrite(2, HIGH);  // Configura o pino 2 para transmissão
    RS485Serial.write("Hello RS485!");  // Envia dados via RS485
    delay(100);  // Espera a transmissão ser concluída
    digitalWrite(2, LOW);  // Volta o pino para recepção

    // Exemplo de leitura de dados via RS485
    if (RS485Serial.available()) {
        char received = RS485Serial.read();  // Lê os dados recebidos
        Serial.print(received);  // Mostra os dados no monitor serial
    }

    delay(500);  // Intervalo entre envios de dados
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;

 

    
    
}