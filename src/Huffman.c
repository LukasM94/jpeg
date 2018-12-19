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

#include "../include/Huffman.h"
#include <stdlib.h>


//------------------------------------------------------------------------------
static void addToList(Huffman_t* this, const char element)
{
  if (this->head_of_list_ == NULL)
  {
    this->head_of_list_ = (HuffmanNode_t*)malloc(sizeof(HuffmanNode_t));
    (*this->head_of_list_).left_        = NULL;
    (*this->head_of_list_).right_       = NULL;
    (*this->head_of_list_).child_left_  = NULL;
    (*this->head_of_list_).child_right_ = NULL;
    (*this->head_of_list_).data_        = element;
    (*this->head_of_list_).count_       = 1;
    return;
  }

  HuffmanNode_t* list_element = this->head_of_list_;
  HuffmanNode_t* tail;

  // Search for the same element in the list
  while (list_element != NULL)
  {
    if ((*list_element).data_ == element)
    {
      (*list_element).count_++;
      return;
    }
    tail         = list_element;
    list_element = list_element->right_;
  }

  // Add the element to the end of the list
  list_element = (HuffmanNode_t*)malloc(sizeof(HuffmanNode_t));
  tail->right_ = list_element;
  (*list_element).left_        = tail;
  (*list_element).right_       = NULL;
  (*list_element).child_left_  = NULL;
  (*list_element).child_right_ = NULL;
  (*list_element).data_        = element;
  (*list_element).count_       = 1;
}

//------------------------------------------------------------------------------
void HuffM_ctor(Huffman_t* this)
{
  this->head_of_list_ = NULL;
}

//------------------------------------------------------------------------------
void HuffM_dtor(Huffman_t* this)
{
  HuffmanNode_t* next_element    = this->head_of_list_;
  HuffmanNode_t* current_element = next_element;
  while (next_element != NULL)
  {
    current_element = next_element;
    next_element    = next_element->right_;
    free(current_element);
  }
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
  head_sorted->right_ = NULL;

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
      free(inserted_element);
      continue;
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
  if (this->print == NULL)
  {
    return;
  }

  HuffmanNode_t* printed_element = this->head_of_list_;
  while (printed_element != NULL)
  {
    this->print("(count = %d, data = %d), ", printed_element->count_, printed_element->data_);
    // printf("(count = %d, data = %d), ", printed_element->count_, printed_element->data_);
    printed_element = printed_element->right_;
  }
  this->print("\n\n");
  // printf("\n\n");
}

//------------------------------------------------------------------------------
static void printTree(Huffman_t* this, HuffmanNode_t* root)
{
  if (root->child_left_ != NULL)
  {
    printTree(this, root->child_left_);
  }

  if (root->child_right_ != NULL)
  {
    printTree(this, root->child_right_);
  }

  (this->print)("(count = %d, data = %d), ", root->count_, root->data_);
}

//------------------------------------------------------------------------------
void HuffM_printTree(Huffman_t* this)
{
  printTree(this, this->head_of_list_);
}

//------------------------------------------------------------------------------
void HuffM_addHuffmanList(Huffman_t* this, Huffman_t* other)
{
  HuffmanNode_t* head_of_this             = this->head_of_list_;
  HuffmanNode_t* current_element_of_other = other->head_of_list_;

  while (current_element_of_other != NULL)
  {
    HuffmanNode_t* inserted_element = current_element_of_other;
    current_element_of_other = current_element_of_other->right_;

    // Delete the element from the first list
    if (inserted_element->right_ != NULL)
    {
      inserted_element->right_->left_ = NULL;
      inserted_element->right_        = NULL;
    }

    // First insert to the head of this
    if (this->head_of_list_ == NULL)
    {
      this->head_of_list_ = inserted_element;
      head_of_this        = inserted_element;
      continue;
    }

    // Find the position of the element in second list
    HuffmanNode_t* current_element_of_this;
    HuffmanNode_t* next_element_of_this = head_of_this;
    int comparison = SMALLER_EQUAL_COUNT;
    while (next_element_of_this != NULL)
    {
      current_element_of_this = next_element_of_this;
      comparison = this->compare(current_element_of_this,
                                 inserted_element);
      if (comparison == EQUAL_DATA)
      {
        break;
      }
      next_element_of_this = next_element_of_this->right_;
    }

    // if this data already exists, add the count
    if (comparison == EQUAL_DATA)
    {
      current_element_of_this->count_ += inserted_element->count_;
      free(inserted_element);
      continue;
    }

    // Insert the element at the tail
    current_element_of_this->right_ = inserted_element;
    inserted_element->left_         = current_element_of_this;
  }
  other->head_of_list_ = NULL;
}

//------------------------------------------------------------------------------
int HuffM_compare(HuffmanNode_t* left, HuffmanNode_t* right)
{
  if (left->data_ == right->data_)
  {
    return EQUAL_DATA;
  }
  if (left->count_ <= right->count_)
  {
    return SMALLER_EQUAL_COUNT;
  }
  else
  {
    return GREATER_COUNT;
  }
}
