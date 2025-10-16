const byte addrPins[11] = {2,3,4,5,6,7,8,9,10,11,12};
const byte dataPins[8]  = {A0,A1,A2,A3,A4,A5,A6,A7};

const byte pinCE = A8;
const byte pinOE = A9;
const byte pinWE = A10;

void setup() {
  Serial.begin(115200);
  Serial.println("Start");

  for (byte i = 0; i < 11; i++)
    pinMode(addrPins[i], OUTPUT);

  for (byte i = 0; i < 8; i++)
    pinMode(dataPins[i], INPUT);

  pinMode(pinCE, OUTPUT);
  pinMode(pinOE, OUTPUT);
  pinMode(pinWE, OUTPUT);

  digitalWrite(pinCE, LOW);
  digitalWrite(pinOE, HIGH);
  digitalWrite(pinWE, HIGH);

  eepromWrite(0, 0);


    uint16_t a1 = 0b00000000000;
    uint16_t b1 = 0b00011111111;

    uint16_t a2 = 0b00100000000;
    uint16_t b2 = 0b00111111111;

    uint16_t a3 = 0b01100000000;
    uint16_t b3 = 0b01111111111;

    for (uint16_t adr = a3; adr <= b3; adr++) {

    uint16_t num = getNum(adr);
    byte data = numberToDisplay(num);
    eepromWrite(adr, data);

    delay(10);

    byte verify = eepromRead(adr);
    //printStuff(adr, data, verify, num);
  }



  Serial.println("End");
}

void loop() {}


uint16_t getNum(uint16_t adr){

  uint16_t num = adr & 0b00011111111;

  if(adr >= 0b00000000000 && adr <= 0b00011111111){
    return num % 10;
  }

  else if (adr >= 0b00100000000 && adr <= 0b00111111111){
    return (num % 100) / 10;
  }

  else if (adr >= 0b01000000000 && adr <= 0b01111111111){
    return num / 100;
  }

  else if (adr >= 0b10000000000 && adr <= 0b11111111111){
    return 0;
  }

  return 0;



  return 0;
}

void printStuff(uint16_t adr, byte data, byte verify, uint16_t num){
    Serial.println("--------");

    Serial.print("adr - ");
    Serial.print(adr, BIN);
    Serial.print(" (");
    Serial.print(adr);
    Serial.println(")");

    Serial.print("num - ");
    Serial.println(num);

    Serial.print("write - ");
    Serial.println(data, BIN);

    Serial.print("read ");
    Serial.println(verify, BIN);



}

void setAddress(uint16_t address) {
  for (byte i = 0; i < 11; i++)
    digitalWrite(addrPins[i], (address >> i) & 1);
}

void clearDataBus() {
  for (byte i = 0; i < 8; i++) {
    pinMode(dataPins[i], OUTPUT);
    digitalWrite(dataPins[i], LOW);
  }
}

void setDataPinsOutput() {
  for (byte i = 0; i < 8; i++)
    pinMode(dataPins[i], OUTPUT);
}

void setDataPinsInput() {
  for (byte i = 0; i < 8; i++)
    pinMode(dataPins[i], INPUT);
}

void writeDataBus(byte data) {
  for (byte i = 0; i < 8; i++)
    digitalWrite(dataPins[i], (data >> i) & 1);
}

void eepromWrite(uint16_t address, byte data) {
  setAddress(address);

  clearDataBus();           // ensure bus starts clean
  writeDataBus(data);       // drive new data
  setDataPinsOutput();

  delayMicroseconds(10);    // let address/data settle

  digitalWrite(pinOE, HIGH);
  digitalWrite(pinWE, LOW);
  delayMicroseconds(20);    // write pulse width (safe)
  digitalWrite(pinWE, HIGH);

  delay(20);                // internal write cycle time
}

byte eepromRead(uint16_t address) {
  setAddress(address);
  setDataPinsInput();

  delayMicroseconds(10);
  digitalWrite(pinWE, HIGH);
  digitalWrite(pinOE, LOW);
  delayMicroseconds(20);

  byte data = 0;
  for (byte i = 0; i < 8; i++)
    data |= (digitalRead(dataPins[i]) << i);

  digitalWrite(pinOE, HIGH);
  return data;
}

byte numberToDisplay(int n) {
  switch (n) {
    case 0: return 0b00111111;
    case 1: return 0b00000110;
    case 2: return 0b01011011;
    case 3: return 0b01001111;
    case 4: return 0b01100110;
    case 5: return 0b01101101;
    case 6: return 0b01111101;
    case 7: return 0b00000111;
    case 8: return 0b01111111;
    case 9: return 0b01101111;
    default: return 0b00000000;
  }
}
