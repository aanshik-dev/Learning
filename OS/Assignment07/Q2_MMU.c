#include <stdio.h>

int main() {
  unsigned int virtualAddress;

  printf("Enter virtual address (in HEX) : 0x");
  scanf("%x", &virtualAddress);

  unsigned int dirIndex = (virtualAddress >> 22) & 0x3FF;
  unsigned int tableIndex = (virtualAddress >> 12) & 0x3FF;
  unsigned int offset = virtualAddress & 0xFFF;

  printf("\n--- Address Breakdown ---\n");
  printf("Directory Index: %u\n", dirIndex);
  printf("Table Index: %u\n", tableIndex);
  printf("Offset: %u\n", offset);

  int pageDirectory[1024];
  int pageTable[1024];

  for (int i = 0; i < 1024; i++) {
    pageDirectory[i] = i;
    pageTable[i] = i + 100;
  }

  int frameNumber = pageTable[tableIndex];

  unsigned int physicalAddress = (frameNumber << 12) | offset;

  printf("\n--- Result ---\n");
  printf("Frame Number: %d\n", frameNumber);
  printf("Physical Address: 0x%X\n", physicalAddress);

  return 0;
}