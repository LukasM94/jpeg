/*
  Name: huffman.h
  Author: Lukas Maar
  Created: 16.12.2018

  Brief:
    See huffman.c
*/

#include "Huffman.h"

typedef struct HuffmanCode
{
  // Member variables
  Huffman_t huffman_main_;
  Huffman_t huffman_temp_;

  // Methods
  void (*createList)(struct HuffmanCode* this,
                     const char*         vectors,
                     int                 count_vectors);
  void (*convertToTree)(struct HuffmanCode* this);
  void (*printList)(struct HuffmanCode* this);
  void (*printTree)(struct HuffmanCode* this);

  // Used as function pointers
  void (*print)(const char* format, ...);
} HuffmanCode_t;

/*
 * Constructor
 */
void HuffMCode_ctor(HuffmanCode_t* this);

/*
 * Desturctor
 */
void HuffMCode_dtor(HuffmanCode_t* this);

/*
 * Create the sorted huffman list
 *
 * @param: this
 * @param: a list of a 64 byte vector
 *         this vector represent a 8x8 pixel part of the image
 *         the list is the complete image
 * @param: the amount of 8x8 parts
 */
void HuffMCode_createList(HuffmanCode_t* this,
                          const char*    vectors,
                          int            count_vectors);

/*
 * Converts the list to the tree
 * Importtan: you have to createList first
 *
 * @param: this
 */
void HuffMCode_convertToTree(HuffmanCode_t* this);

/*
 * Prints the list
 */
void HuffMCode_printList(HuffmanCode_t* this);

/*
 * Prints the tree
 */
void HuffMCode_printTree(HuffmanCode_t* this);

/*
 * Initialize the HuffmanCode
 */
static void HuffMCode_init(HuffmanCode_t* this)
{
  HuffM_init(&this->huffman_main_);
  HuffM_init(&this->huffman_temp_);
  this->createList = &HuffMCode_createList;
  this->convertToTree = &HuffMCode_convertToTree;
  this->printList  = &HuffMCode_printList;
  this->printTree  = &HuffMCode_printTree;
}

/*
 * Initialize the interface
 */
static void HuffMCode_initPrint(HuffmanCode_t* this,
                                void (*print_function)(const char* format, ...))
{
  HuffM_initPrint(&this->huffman_main_, print_function);
  this->print = print_function;
}
