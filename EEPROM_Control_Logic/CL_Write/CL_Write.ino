uint16_t A_In = 0b0000000000000001;
uint16_t A_Out = 0b0000000000000010;
uint16_t B_In = 0b0000000000000100;
uint16_t Flags_In = 0b0000000000001000;
uint16_t Alu_Sub = 0b0000000000010000;
uint16_t Alu_Out = 0b0000000000100000;
uint16_t Counter_En = 0b0000000001000000;
uint16_t Counter_Out = 0b0000000010000000;
uint16_t Counter_Jump = 0b0000000100000000;
uint16_t Instruction_In = 0b0000001000000000;
uint16_t Instruction_Out = 0b0000010000000000;
uint16_t Ram_Adr_In = 0b0000100000000000;
uint16_t Ram_Data_In = 0b0001000000000000;
uint16_t Ram_Data_Out = 0b0010000000000000;
uint16_t Output_In = 0b0100000000000000;
uint16_t Hlt = 0b1000000000000000;

const byte addrPins[11] = {2,3,4,5,6,7,8,9,10,11,12};
const byte dataPins[8]  = {A0,A1,A2,A3,A4,A5,A6,A7};

const byte pinCE = A8;
const byte pinOE = A9;
const byte pinWE = A10;

uint16_t fetch(byte micro){
  uint16_t ans = 0;

  if(micro == 0b000)
    ans = Counter_Out + Ram_Adr_In;

  else if(micro == 0b001)
    ans = Ram_Data_Out + Instruction_In + Counter_En;

  return ans;
}

uint16_t NOP(byte micro, byte flags){
  uint16_t ans = 0;
  return ans;
}

uint16_t LDA(byte micro, byte flags){
  uint16_t ans = 0;

  if(micro == 0b010)
    ans = Instruction_Out + Ram_Adr_In;
  

  else if(micro == 0b011)
    ans = Ram_Data_Out + A_In;
  
  return ans;
}

uint16_t ADD(byte micro, byte flags){
  int16_t ans = 0;

  if(micro == 0b010)
    ans = Instruction_Out+Ram_Adr_In;

  else if(micro == 0b011)
    ans = Ram_Data_Out + B_In;

  else if(micro == 0b100)
    ans = Alu_Out + A_In + Flags_In;

  return ans;
}

uint16_t SUB(byte micro, byte flags){
  uint16_t ans = 0;

  if(micro == 0b010)
    ans = Instruction_Out + Ram_Adr_In;

  else if(micro == 0b011)
    ans = Ram_Data_Out + B_In;

  else if(micro == 0b100)
    ans = Alu_Sub + Alu_Out + A_In + Flags_In;

  return ans;
}

uint16_t STA(byte micro, byte flags){
  uint16_t ans = 0;

  if(micro == 0b010)
    ans = Instruction_Out + Ram_Adr_In;

  else if(micro == 0b011)
    ans = A_Out + Ram_Data_In;
  return ans;
}

uint16_t LDI(byte micro, byte flags){
  uint16_t ans = 0;

  if(micro == 0b010)
    ans = Instruction_Out + A_In;

  return ans;
}

uint16_t JMP(byte micro, byte flags){
  uint16_t ans = 0;

  if(micro == 0b010)
    ans = Instruction_Out + Counter_Jump;

  return ans;
}

uint16_t JMC(byte micro, byte flags){
  uint16_t ans = 0;

  if (micro == 0b010 && (flags == 0b10 || flags == 0b11))
    ans = Instruction_Out + Counter_Jump;

  return ans;
}

uint16_t JMZ(byte micro, byte flags){
  uint16_t ans = 0;

  if (micro == 0b010 && (flags == 0b01 || flags == 0b11))
    ans = Instruction_Out + Counter_Jump;

  return ans;
}

uint16_t OUT(byte micro, byte flags){
  uint16_t ans = 0;

  if(micro == 0b010)
    ans = A_Out + Output_In;

  return ans;
}

uint16_t HLT(byte micro, byte flags){
  uint16_t ans = 0;

  if(micro == 0b010)
    ans = Hlt;

  return ans;
}


uint16_t finalInstruction(byte inst, byte micro, byte flags){
  if(micro == 0b000 || micro == 0b001) return fetch(micro);

  switch(inst){
    case 0b0000: return NOP(micro, flags);
    case 0b0001: return LDA(micro, flags);
    case 0b0010: return ADD(micro, flags);
    case 0b0011: return SUB(micro, flags);
    case 0b0100: return STA(micro, flags);
    case 0b0101: return LDI(micro, flags);
    case 0b0110: return JMP(micro, flags);
    case 0b0111: return JMC(micro, flags);
    case 0b1000: return JMZ(micro, flags);
    case 0b1001: return 0;
    case 0b1010: return 0;
    case 0b1011: return 0;
    case 0b1100: return 0;
    case 0b1101: return 0;
    case 0b1110: return OUT(micro, flags);
    case 0b1111: return HLT(micro, flags);
  }

  return 0;
}

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

    for (byte flags = 0b00; flags <= 0b11; flags++) {
      for(byte micro = 0b000; micro <= 0b111; micro++){

        uint16_t instr = 0b0001;

        uint16_t data = ADD(micro, flags);
        byte d1 = (byte)(data >> 8);
        byte d2 = (byte)data;

        uint16_t adr1 = instr<<5;
        uint16_t adr2 = micro<<2;
        uint16_t adr3 = flags;

        uint16_t adr = adr1 + adr2 + adr3;
      
      byte d = d1;

      eepromWrite(adr, d);

      delay(10);

      byte verify = eepromRead(adr);

      printStuff(adr, d, verify, data);
      }
  }

  Serial.println("End");
}



void loop() {
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

  clearDataBus();
  writeDataBus(data);
  setDataPinsOutput();

  delayMicroseconds(10); 

  digitalWrite(pinOE, HIGH);
  digitalWrite(pinWE, LOW);
  delayMicroseconds(20);
  digitalWrite(pinWE, HIGH);

  delay(20);
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


void printStuff(uint16_t adr, byte data, byte verify, uint16_t wholeData){
    Serial.println("--------");

    Serial.print("Whole Data - ");
    Serial.println(wholeData, BIN);

    Serial.print("adr - ");
    Serial.print(adr, BIN);
    Serial.print(" (");
    Serial.print(adr);
    Serial.println(")");

    Serial.print("write - ");
    Serial.println(data, BIN);

    Serial.print("read ");
    Serial.println(verify, BIN);
}
