uint16_t fetch(byte micro){
  return 0;
}

uint16_t NOP(byte micro, byte flags){
  return 0;
}

uint16_t LDA(byte micro, byte flags){
  return 0;
}

uint16_t ADD(byte micro, byte flags){
  return 0;
}

uint16_t SUB(byte micro, byte flags){
  return 0;
}

uint16_t STA(byte micro, byte flags){
  return 0;
}

uint16_t LDI(byte micro, byte flags){
  return 0;
}

uint16_t JMP(byte micro, byte flags){
  return 0;
}

uint16_t JMC(byte micro, byte flags){
  return 0;
}

uint16_t JMZ(byte micro, byte flags){
  return 0;
}

uint16_t OUT(byte micro, byte flags){
  return 0;
}

uint16_t HLT(byte micro, byte flags){
  return 0;
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
