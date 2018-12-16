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

#include "../include/huffman.h"
#include <stdlib.h>
#include <stdio.h>


//------------------------------------------------------------------------------
static void addToList(Huffman_t* this, const char element)
{
  if (this->head_of_list_ == NULL)
  {
    this->head_of_list_ = (HuffmanNode_t*)malloc(sizeof(HuffmanNode_t));
    this->tail_of_list_ = this->head_of_list_;
    (*this->head_of_list_).left_  = NULL;
    (*this->head_of_list_).right_ = NULL;
    (*this->head_of_list_).data_  = element;
    (*this->head_of_list_).count_ = 1;
    return;
  }

  HuffmanNode_t* list_element = this->head_of_list_;
  HuffmanNode_t* tail         = this->tail_of_list_;

  // Search for the same element in the list
  while (list_element != NULL)
  {
    if ((*list_element).data_ == element)
    {
      (*list_element).count_++;
      return;
    }
    list_element = list_element->right_;
  }

  // Add the element to the end of the list
  list_element = (HuffmanNode_t*)malloc(sizeof(HuffmanNode_t));
  tail->right_ = list_element;
  (*list_element).left_  = tail;
  (*list_element).right_ = NULL;
  (*list_element).data_  = element;
  (*list_element).count_ = 1;
  this->tail_of_list_    = list_element;
}

//------------------------------------------------------------------------------
void HuffM_ctor(Huffman_t* this)
{
  this->head_of_tree_ = (HuffmanNode_t*)malloc(sizeof(HuffmanNode_t));
  this->head_of_list_ = NULL;
  this->tail_of_list_ = NULL;
}

//------------------------------------------------------------------------------
void HuffM_addList(Huffman_t* this, const char vector[64])
{
  for (int i = 63; i >= 0; i--)
  {
    addToList(this, vector[i]);
  }
}

//------------------------------------------------------------------------------
void HuffM_sortList(Huffman_t* this)
{
  HuffmanNode_t* head_not_sorted = this->head_of_list_->right_;
  HuffmanNode_t* head_sorted     = this->head_of_list_;

  head_sorted->right_->left_ = NULL;
  head_sorted->right_        = NULL;

  while (head_not_sorted != NULL)
  {
    HuffmanNode_t* inserted_element = head_not_sorted;
    head_not_sorted = head_not_sorted->right_;

    // Delete the element from the first list
    if (inserted_element->right_ != NULL)
    {
      inserted_element->right_->left_ = NULL;
      inserted_element->right_        = NULL;
    }

    // Find the position of the element in second list
    HuffmanNode_t* current_element_new_list;
    HuffmanNode_t* next_element_new_list = head_sorted;
    int comparison;
    while (next_element_new_list != NULL)
    {
      current_element_new_list = next_element_new_list;
      comparison = this->compare(current_element_new_list,
                                 inserted_element);
      if (comparison != GREATER_COUNT)
      {
        break;
      }
      next_element_new_list = next_element_new_list->right_;
    }

    // if this data already exists, add the count
    if (comparison == EQUAL_DATA)
    {
      current_element_new_list->count_ += inserted_element->count_;
    }

    // Insert the element at the tail
    if (next_element_new_list == NULL)
    {
      current_element_new_list->right_ = inserted_element;
      inserted_element->left_          = current_element_new_list;
      continue;
    }
    // Insert the element at the head
    if (current_element_new_list->left_ == NULL)
    {
      current_element_new_list->left_ = inserted_element;
      inserted_element->right_        = current_element_new_list;
      head_sorted                     = inserted_element;
      continue;
    }
    // Insert the element in between
    inserted_element->left_  = current_element_new_list->left_;
    inserted_element->right_ = current_element_new_list;

    current_element_new_list->left_->right_ = inserted_element;
    current_element_new_list->left_         = inserted_element;
  }
}

//------------------------------------------------------------------------------
void HuffM_printList(Huffman_t* this)
{
  HuffmanNode_t* printed_element = this->head_of_list_;
  while (printed_element != NULL)
  {
    printf("(count = %d, data = %d), ", printed_element->count_, printed_element->data_);
    printed_element = printed_element->right_;
  }
  printf("\n");
}

//------------------------------------------------------------------------------
int HuffM_compare(HuffmanNode_t* left, HuffmanNode_t* right)
{
  if (left->count_ <= right->count_)
  {
    if (left->data_ == right->data_)
    {
      return EQUAL_DATA;
    }
    return SMALLER_EQUAL_COUNT;
  }
  else
  {
    return GREATER_COUNT;
  }
}
