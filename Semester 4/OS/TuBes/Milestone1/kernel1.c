int main () {
  putInMemory(0xB000, 0x8000, 'K');
  putInMemory(0xB000, 0x8001, 0xD);
  putInMemory(0xB000, 0x8002, 'e');
  putInMemory(0xB000, 0x8003, 0xD);
  putInMemory(0xB000, 0x8004, 'r');
  putInMemory(0xB000, 0x8005, 0xD);
  putInMemory(0xB000, 0x8006, 'n');
  putInMemory(0xB000, 0x8007, 0xD);
  putInMemory(0xB000, 0x8008, 'e');
  putInMemory(0xB000, 0x8009, 0xD);
  putInMemory(0xB000, 0x800A, 'l');
  putInMemory(0xB000, 0x800B, 0xD);
  putInMemory(0xB000, 0x800C, '!');
  putInMemory(0xB000, 0x800D, 0xD);
  while (1);
}

void handleInterrupt21 (int AX, int BX, int CX, int DX) {}
