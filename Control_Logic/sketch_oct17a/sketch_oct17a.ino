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

  if(micro = 0b010)
    ans = Instruction_Out + Counter_Jump;

  return ans;
}

uint16_t JMC(byte micro, byte flags){
  uint16_t ans = 0;

  if(flags == 0b10 || flags == 0b11)
    ans = Instruction_Out + Counter_Jump;

  return ans;
}

uint16_t JMZ(byte micro, byte flags){
  uint16_t ans = 0;

  if(flags == 0b01 || flags == 0b11)
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

}

void loop() {

}
