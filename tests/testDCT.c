#include "../include/DiscreteCosineTransformation.h"
#include <stdio.h>

float vector[8] = {1,2,3,4,5,6,7,8};

static void printVector()
{
  printf("Vector:\n");
  for (int i = 0; i < 8; i++)
  {
    printf("%f\t", vector[i]);
  }
  printf("\n\n");
}

int main()
{
  printVector();
  FastDct8_transform(vector);
  printVector();
  FastDct8_inverseTransform(vector);
  printVector();
  return 0;
}
