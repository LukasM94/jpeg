#include "../include/imageConvertion.h"
#include <stdio.h>

char vector[64] =
{
   1,127, 3, 4, 5, 6, 7, 8,
  11,12,13,14,15,16,17,18,
  21,22,23,24,25,26,27,28,
  31,32,33,34,35,36,37,38,
  41,42,43,44,45,46,47,48,
  51,52,53,54,55,56,57,58,
  61,62,63,64,65,66,67,68,
  71,72,73,74,75,76, 7,78
};

static void printVector()
{
  printf("Vector:\n");
  for (int i = 0; i < 64; i++)
  {
    printf("%x\t", vector[i]);
    if (i % 8 == 7)
    {
      printf("\n");
    }
  }
  printf("\n\n");
}

int main()
{
  printVector();
  ImageConv_transformCosineBlock(vector);
  ImageConv_quantize();
  ImageConv_dequantize();
  ImageConv_inverseTransformCosineBlock(vector);
  printVector();
  return 0;
}
