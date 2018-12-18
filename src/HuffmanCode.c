/*
  Name: huffman.c
  Author: Lukas Maar
  Created: 16.12.2018

  Brief:
    The goal of this file is to get all the data of the picture in a huffman
    tree.
      - first:  get all the elements and the count
      - second: sort the elements count up/down
      - third:  create the tree
*/

#include "../include/HuffmanCode.h"

//------------------------------------------------------------------------------
void HuffMCode_ctor(HuffmanCode_t* this)
{
  HuffM_ctor(&this->huffman_main_);
  HuffM_ctor(&this->huffman_temp_);
}

//------------------------------------------------------------------------------
void HuffMCode_dtor(HuffmanCode_t* this)
{
  HuffM_dtor(&this->huffman_main_);
  HuffM_dtor(&this->huffman_temp_);
}

//------------------------------------------------------------------------------
void HuffMCode_createList(HuffmanCode_t* this,
                          const char*    vectors,
                          int            count_vectors)
{
  const char* vector = vectors;
  while (count_vectors-- != 0)
  {
    (this->huffman_temp_.addList)(&this->huffman_temp_, vector);
    (this->huffman_main_.addHuffmanList)(&this->huffman_main_,
                                         &this->huffman_temp_);
    vector = vector + 64;
  }
  (this->huffman_main_.sortList)(&this->huffman_main_);
}

//------------------------------------------------------------------------------
void HuffMCode_printList(HuffmanCode_t* this)
{
  (this->huffman_main_.printList)(&this->huffman_main_);
}

//------------------------------------------------------------------------------
void HuffMCode_printTree(HuffmanCode_t* this)
{

}
