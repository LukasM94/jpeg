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
#include <stdlib.h>

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
void HuffMCode_convertToTree(HuffmanCode_t* this)
{
  HuffmanNode_t* tail = this->huffman_main_.head_of_list_;
  HuffmanNode_t* root;

  // Get the tails
  while (tail->right_ != NULL)
  {
    tail = tail->right_;
  }

  while (1)
  {
    // Last element of the current list
    HuffmanNode_t* last     = tail;
    // Second last element of the current list
    HuffmanNode_t* sec_last = tail->left_;
    // This element gets inserted in the list
    HuffmanNode_t* combined_element;

    /*
     * Principle:
     *
     * |------|     |----------|     |------|
     * |      |---->| sec_last |---->| last |
     * |------|<----|----------|<----|------|
     *
     * convertes to:
     *
     * |------|     |----------|     |------|
     * |      |---->| combined |---->|      |---->
     * |------|<----|----------|<----|------|<----
     *             /            \
     *            /              \
     *           /                \
     *          /                  \
     *         /                    \
     *        /                      \
     * |----------|                |------|
     * | sec_last |                | last |
     * |----------|                |------|
     *
     * repeats as long as there are more then one elements in the list
     * if there is only one left, this one is root!
     */

    last->left_ = NULL;
    // Important: tail could be NULL
    tail = sec_last->left_;
    sec_last->right_ = NULL;
    if (sec_last->left_ != NULL)
    {
      sec_last->left_->right_ = NULL;
      sec_last->left_         = NULL;
    }

    // Create the tree structure
    combined_element = (HuffmanNode_t*)malloc(sizeof(HuffmanNode_t));
    combined_element->data_        = PARENT;
    combined_element->child_left_  = sec_last;
    combined_element->child_right_ = last;
    combined_element->count_       = last->count_ + sec_last->count_;

    if (tail == NULL)
    {
      // FINISH
      root = combined_element;
      break;
    }

    // INSERT
    // Insert the combined element, so that the list is still sorted
    HuffmanNode_t* inserted_element;
    HuffmanNode_t* left_element = tail;
    while (left_element != NULL)
    {
      if (left_element->count_ > combined_element->count_)
      {
        break;
      }
      inserted_element = left_element;
      left_element     = left_element->left_;
    }

    // Insert at the tail
    if (inserted_element == tail)
    {
      tail                     = combined_element;
      combined_element->right_ = NULL;
      combined_element->left_  = inserted_element;
      inserted_element->right_ = combined_element;
    }

    // Insert at the head
    if (left_element == NULL)
    {
      combined_element->left_  = NULL;
      combined_element->right_ = inserted_element;
      inserted_element->left_  = combined_element;
    }

    // Insert in between
    combined_element->left_         = inserted_element->left_;
    combined_element->right_        = inserted_element;
    inserted_element->left_->right_ = combined_element;
    inserted_element->left_         = combined_element;
  }
}

//------------------------------------------------------------------------------
void HuffMCode_printList(HuffmanCode_t* this)
{
  (this->huffman_main_.printList)(&this->huffman_main_);
}

//------------------------------------------------------------------------------
void HuffMCode_printTree(HuffmanCode_t* this)
{
  (this->huffman_main_.printTree)(&this->huffman_main_);
}
