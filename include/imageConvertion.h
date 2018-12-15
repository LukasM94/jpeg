/*
  Name: imageEditor.h
  Author: Lukas Maar
  Created: 15.12.2018

  Brief:
    See imageEditor.c
*/

/*
 * Transform 64 byte block(cast before) to a 64 float block
 *
 * @param: block
 */
void ImageConv_transformCosineBlock(char vector[64]);

/*
 * Transform 64 float block(cast before) to a 64 byte block
 *
 * @param: block
 */
void ImageConv_inverseTransformCosineBlock(char vector[64]);
