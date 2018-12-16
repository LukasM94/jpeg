/*
  Name: huffman.h
  Author: Lukas Maar
  Created: 16.12.2018

  Brief:
    See huffman.c
*/

typedef struct HuffmanNode
{
  int count_;
  int data_;
  struct HuffmanNode* left_;
  struct HuffmanNode* right_;
} HuffmanNode_t;

typedef struct Huffman
{
  // Member variables
  HuffmanNode_t* head_of_tree_;
  HuffmanNode_t* head_of_list_;
  HuffmanNode_t* tail_of_list_;

  // Methods
  void (*addList)(struct Huffman* this, const char vector[64]);
  void (*sortList)(struct Huffman* this);
} Huffman_t;

void HuffM_ctor(Huffman_t* this);
void HuffM_dtor(Huffman_t* this);

void HuffM_addList(Huffman_t* this, const char vector[64]);
void HuffM_sortList(Huffman_t* this);

static void HuffM_init(Huffman_t* this)
{
  this->addList = &HuffM_addList;
  this->sortList = &HuffM_sortList;
}
