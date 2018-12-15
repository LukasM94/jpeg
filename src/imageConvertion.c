/*
  Name: imageEditor.c
  Author: Lukas Maar
  Created: 15.12.2018

  Brief:
    The goal of this file is to get as an input a raw rgb picture (like bmp)
    and convert it to a jpeg file
*/

#include "../include/imageConvertion.h"
#include "../include/discreteCosineTransformation.h"

static float buffer[64];

//-----------------------------------------------------------------------------
void ImageConv_transformCosineBlock(char vector[64])
{
  float* ptr_buffer = buffer;
  char*  ptr_vector = vector;
  for (int i = 0; i < 64; i++)
  {
    *(ptr_buffer++) = *(ptr_vector++);
  }
  for (int i = 0; i < 8; i++)
  {
    FastDct8_transform(&buffer[8 * i]);
  }
}

//-----------------------------------------------------------------------------
void ImageConv_inverseTransformCosineBlock(char vector[64])
{
  float* ptr_buffer = buffer;
  char*  ptr_vector = vector;
  for (int i = 0; i < 8; i++)
  {
    FastDct8_inverseTransform(&buffer[8 * i]);
  }
  for (int i = 0; i < 64; i++)
  {
    *(ptr_vector++) = *(ptr_buffer++);
  }
  // vector[0] = 0xf;
}
