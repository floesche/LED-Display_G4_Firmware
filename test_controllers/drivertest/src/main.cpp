#include <Arduino.h>
#include <SPI.h>

SPISettings g4SPI(4000000, MSBFIRST, SPI_MODE0);

uint8_t dBuf[132];
byte cipo;

void genRow(uint8_t row, uint8_t* buf, uint8_t bsize){
  uint8_t pos, color;
  for (uint8_t i = 0; i < 128; i++){
    pos = (uint8_t)i/32 + i + 1;

    color = ((uint8_t)((i % 64)) / 4) == row ? 255 : 0;
    if (row >= 16){
      color = 255;
    }
    buf[pos] = color;
  }
  uint8_t prm  = 0b00000001;
  // uint prm  = 0b01111111;
  //  uint prm  = 1 | (stretchcounter << 1);
     
  buf[0] = prm; buf[33] = prm; buf[66] = prm; buf[99] = prm;
}

void setup() {
  pinMode(PIN_SPI_SS, OUTPUT);
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Initialization finished");
  SPI.begin();
}

void loop() {
  genRow(1 % 19, dBuf, 132);
  SPI.beginTransaction(g4SPI);
  digitalWrite(PIN_SPI_SS,LOW);
  for (uint8_t i = 1; i<33; i++){    
    cipo = SPI.transfer(dBuf[i]);
    Serial.print(cipo); Serial.print(" ");
  }
  digitalWrite(PIN_SPI_SS,HIGH);
  SPI.endTransaction();
}