/*
  Name: huffman.h
  Author: Lukas Maar
  Created: 16.12.2018

  Brief:
    See huffman.c
*/

#define SMALLER_EQUAL_COUNT -1
#define EQUAL_DATA          0
#define GREATER_COUNT       1

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
  HuffmanNode_t* head_of_list_;
  HuffmanNode_t* tail_of_list_;

  // Methods
  void (*addList)(struct Huffman* this, const char vector[64]);
  void (*sortList)(struct Huffman* this);
  void (*printList)(struct Huffman* this);
  void (*addHuffmanList)(struct Huffman* this, struct Huffman* other);

  // Compare variante
  int (*compare)(struct HuffmanNode* left, struct HuffmanNode* right);
} Huffman_t;

/*
 * Constructor
 */
void HuffM_ctor(Huffman_t* this);

/*
 * Destructor
 */
void HuffM_dtor(Huffman_t* this);

/*
 * Add to list
 *  add all the not equal elements of the vector with the count to the list
 *
 * @param: the vector
 *         has to be 64 bytes long and const
 */
void HuffM_addList(Huffman_t* this, const char vector[64]);

/*
 * Sorts the list
 */
void HuffM_sortList(Huffman_t* this);

/*
 * Pint the list in order or the double linked list
 */
void HuffM_printList(Huffman_t* this);

/*
 * Add the list of an existing huffman instant to this
 *
 * @param: this huffman instant
 * @param: other huffman instant
 */
void HuffM_addHuffmanList(Huffman_t* this, Huffman_t* other);

/*
 * Compares the left and the right node
 *
 * @param: left and right node
 *
 * @return: see define
 */
int HuffM_compare(HuffmanNode_t* left, HuffmanNode_t* right);

/*
 * Initialize the huffman "class"
 */
static void HuffM_init(Huffman_t* this)
{
  this->addList        = &HuffM_addList;
  this->sortList       = &HuffM_sortList;
  this->printList      = &HuffM_printList;
  this->addHuffmanList = &HuffM_addHuffmanList;
  this->compare        = &HuffM_compare;
}
