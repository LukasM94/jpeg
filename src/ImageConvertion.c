/*
  Name: imageEditor.c
  Author: Lukas Maar
  Created: 15.12.2018

  Brief:
    The goal of this file is to get as an input a raw rgb picture (like bmp)
    and convert it to a jpeg file
*/

#include "../include/ImageConvertion.h"
#include "../include/DiscreteCosineTransformation.h"
#include <math.h>

static float buffer_[64];
const static char QUANTIZATION_TABLE[64] =
{
  16, 12, 14, 14, 18, 24, 49, 72,
  11, 12, 13, 17, 22, 35, 64, 92,
  10, 14, 16, 22, 37, 55, 78, 95,
  16, 19, 24, 29, 56, 64, 87, 98,
  24, 26, 40, 51, 68, 81,103,112,
  40, 58, 57, 87,109,104,121,100,
  51, 60, 69, 80,103,113,120,103,
  61, 55, 56, 62, 77, 92,101, 99
};

//-----------------------------------------------------------------------------
void ImageConv_transformCosineBlock(char vector[64])
{
  float* ptr_buffer = buffer_;
  char*  ptr_vector = vector;
  for (int i = 0; i < 64; i++)
  {
    *(ptr_buffer++) = *(ptr_vector++);
  }
  for (int i = 0; i < 8; i++)
  {
    FastDct8_transform(&buffer_[8 * i]);
  }
  ptr_buffer = buffer_;
}

//-----------------------------------------------------------------------------
void ImageConv_inverseTransformCosineBlock(char vector[64])
{
  float* ptr_buffer = buffer_;
  char*  ptr_vector = vector;
  for (int i = 0; i < 8; i++)
  {
    FastDct8_inverseTransform(&buffer_[8 * i]);
  }
  for (int i = 0; i < 64; i++)
  {
    *(ptr_vector++) = *(ptr_buffer++);
  }
}

//-----------------------------------------------------------------------------
void ImageConv_quantize()
{
  float*      ptr_buffer = buffer_;
  const char* ptr_quanti = QUANTIZATION_TABLE;
  for (int i = 0; i < 64; i++)
  {
    *(ptr_buffer) = *(ptr_buffer)/(float)*(ptr_quanti++);
    *(ptr_buffer) = truncf(*(ptr_buffer));
  }
}

//-----------------------------------------------------------------------------
void ImageConv_dequantize()
{
  float*      ptr_buffer = buffer_;
  const char* ptr_quanti = QUANTIZATION_TABLE;
  for (int i = 0; i < 64; i++)
  {
    *(ptr_buffer) = *(ptr_buffer)*(float)*(ptr_quanti++);
  }
}
