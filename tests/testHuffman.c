#include "../include/huffman.h"
#include <stdio.h>

Huffman_t huffman;

static const char vector[64] =
{
  13, 4, 5, 8, 1, 0, 0, 0,
   5, 6, 2, 1, 0, 0, 0, 0,
   5, 3, 4, 0, 1, 0, 0, 0,
   3, 2, 1, 0, 0, 0, 0, 0,
   1, 5, 0, 0, 0, 0, 0, 0,
   6, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0
};

int main()
{
  // Inits the huffman "class"
  HuffM_init(&huffman);

  // Constructs a new instant
  HuffM_ctor(&huffman);

  (huffman.addList)(&huffman, vector);
  (huffman.printList)(&huffman);
  (huffman.sortList)(&huffman);
  (huffman.printList)(&huffman);
  return 0;
}
