#include <SPI.h>
#include <elapsedMillis.h>

typedef unsigned int uint;


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

void genRow(uint row, uint8_t dur, uint8_t* buf, uint bsize){
  uint pos, color;
  // for each pixel
  for (uint i = 0; i < 128; i++){
    pos = (uint)i/32 + i + 1; // find index in buffer

    // set only pixels within row to be ON (255), otherwise OFF (0)
    color = ((uint)((i % 64)) / 4) == row ? 255 : 0;
    // if row >= 16, set all pixels ON
    if (row >= 16){
      color = 255;
    }
    buf[pos] = color;
  }
  // display time
  uint8_t header = 1 | (dur << 1);
  buf[0] = header; buf[33] = header; buf[66] = header; buf[99] = header;
}

void genBlank(uint8_t dur, uint8_t* buf, uint bsize){
  // Generate all-zero frame
  uint pos, color;
  // for each pixel
  for (uint i = 0; i < 128; i++) {
    pos = (uint)i/32 + i + 1; // find index in buffer
    color = 0;
    buf[pos] = color;
  }
  // display time
  uint8_t header = 1 | (dur << 1);
  buf[0] = header; buf[33] = header; buf[66] = header; buf[99] = header;
}

void loop() {
  thisFrame = 0;
  uint8_t duration = 0; // ** Adjust this to vary duration
  genRow(counter % 19, duration, dBuf, 132); // ** generate drifting bars & all-on
  //genBlank(duration, dBuf, 132);  // ** generate all-off
  //genRow(19, duration, dBuf, 132);  // ** generate all-on
  SPI.beginTransaction(g4SPI);
  digitalWrite(PIN_SPI_SS,LOW);
  for (uint i = 0; i<132; i++){
    cipo = SPI.transfer(dBuf[i]);
    // Serial.print(cipo); Serial.print(" ");
  }
  // Serial.println("");
  digitalWrite(PIN_SPI_SS,HIGH);
  SPI.endTransaction();

  // increment counter every repeatCounter loops
  // counter resets to 0 after value 127
  if(repeatCounter < repeat){
    repeatCounter = repeatCounter + 1;
  } else {
    counter = (counter + 1) % 128;
    repeatCounter = 0;
  }

  // Wait until 5 ms from start of loop
  // (ensure each loop takes 5 ms)
  while (thisFrame < 5 ){}; // ** Change frame duration here
}
