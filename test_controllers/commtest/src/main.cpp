#include <Arduino.h>
#include <SPI.h>


SPISettings g4SPI(4000000, MSBFIRST, SPI_MODE0);

static uint8_t Stripes[132] = {
  1,
  255, 255, 15, 15, 15, 15, 15, 15,
  15, 15, 15, 15, 15, 15, 15, 15,
  15, 15, 15, 15, 15, 15, 15, 15,
  15, 15, 15, 15, 15, 15, 15, 15,
  1,
  15, 15, 15, 15, 15, 15, 15, 15,
  15, 15, 15, 15, 15, 15, 15, 15,
  15, 15, 15, 15, 15, 15, 15, 15,
  15, 15, 15, 15, 15, 15, 15, 15,
  1,
  15, 15, 15, 15, 15, 15, 15, 15,
  15, 15, 15, 15, 15, 15, 15, 15,
  15, 15, 15, 15, 15, 15, 15, 15,
  15, 15, 15, 15, 15, 15, 15, 15,
  1,
  15, 15, 15, 15, 15, 15, 15, 15,
  15, 15, 15, 15, 15, 15, 15, 15,
  15, 15, 15, 15, 15, 15, 15, 15,
  15, 15, 15, 15, 15, 15, 15, 15
  };

static uint repeat = 50;

elapsedMillis thisFrame;
uint counter = 0;
uint repeatCounter = 0;

byte cipo;

uint8_t dBuf[132];


void setup() {
  pinMode(PIN_SPI_SS, OUTPUT);
  // pinMode(PIN_SPI_SCK, OUTPUT);
  // pinMode(PIN_SPI_MOSI, OUTPUT);
  Serial.begin(115200);
  // while(!Serial);
  Serial.println("Initialization finished");
  SPI.begin();
}

void genBuffer(uint8_t* buf, uint bsize){
  for(uint i = 0; i < bsize; i++){
    buf[i] = Stripes[i];
  }
}

void genPixel(uint col, uint8_t* buf, uint bsize){
  uint pos;
  for(uint i = 0; i < 128; i++){
    pos = (int)i / 32 + i;
    
    buf[pos] = i == col ? 15 : 0;
  }
  buf[0] = 1; buf[33] = 1; buf[66] = 1; buf[99] = 1;
  
}

void genRow(uint row, uint8_t* buf, uint bsize){
  uint pos, color;
  for (uint i = 0; i < 128; i++){
    pos = (uint)i/32 + i + 1;

    color = ((uint)((i % 64)) / 4) == row ? 255 : 0;
    if (row >= 16){
      color = 255;
    }
    buf[pos] = color;
  }
  buf[0] = 1; buf[33] = 1; buf[66] = 1; buf[99] = 1;
}

void loop() {
  thisFrame = 0;
  //genBuffer(dBuf, 132);
  //genColumn(counter, dBuf, 132);
  genRow(counter % 19, dBuf, 132);
  SPI.beginTransaction(g4SPI);
  digitalWrite(PIN_SPI_SS,LOW);
  for (uint i = 0; i<132; i++){    
    cipo = SPI.transfer(dBuf[i]);
    Serial.print(cipo); Serial.print(" ");
  }
  digitalWrite(PIN_SPI_SS,HIGH);
  SPI.endTransaction();
  
  if(repeatCounter < repeat){
    repeatCounter = repeatCounter + 1;
  } else {
    counter = (counter + 1) % 128;
    repeatCounter = 0;
  }
  while (thisFrame < 5){};
  
  
}