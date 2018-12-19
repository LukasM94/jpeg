#include "../include/HuffmanCode.h"
#include <stdio.h>
#include <stdlib.h>

static const char vector1[64] =
{
  13, 4, 5, 8, 1, 0, 0, 0,
   5, 6, 2, 1, 0, 0, 0, 0,
   5, 3, 4, 0, 1, 0, 0, 0,
   3, 2, 1, 0, 0, 0, 0, 0,
   1, 5, 0, 0, 0, 0, 0, 0,
   6, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0
};

static const char vector2[64] =
{
  11,14, 5, 7, 2, 1, 0, 0,
   9, 7, 2, 3, 1, 0, 0, 0,
  10, 3, 5,-1,-1, 0, 0, 0,
  -3, 2, 0, 0, 0, 0, 0, 0,
  -1, 4, 0, 0, 0, 0, 0, 0,
   3, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0
};

void copyToVector(char* dst, const char* src)
{
  int i = 64;
  while (i--)
  {
    *dst = *src;
    dst++;
    src++;
  }
}

int main()
{
  // Create a 1d vector which contains all the 8x8 pixel
  // In this example there are only 2 test 8x8 pixels
  char* vectors = (char*)malloc(128);

  copyToVector(vectors, vector1);
  copyToVector((char*)(vectors + 64), vector2);

  HuffmanCode_t huffmancode;
  HuffMCode_ctor(&huffmancode);
  HuffMCode_init(&huffmancode);
  HuffMCode_initPrint(&huffmancode, (void*)printf);
  huffmancode.createList(&huffmancode, vectors, 2);
  huffmancode.printList(&huffmancode);
  huffmancode.convertToTree(&huffmancode);
  huffmancode.printTree(&huffmancode);
  HuffMCode_dtor(&huffmancode);

  free(vectors);

  return 0;
}
