#include "../include/Huffman.h"
#include <stdio.h>

Huffman_t huffman_main;
Huffman_t huffman_pixel_array;

static const char vector1[64] =
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

static const char vector2[64] =
{
  11,14, 5, 7, 2, 1, 0, 0,
   9, 7, 2, 3, 1, 0, 0, 0,
  10, 3, 5,-1,-1, 0, 0, 0,
  -3, 2, 0, 0, 0, 0, 0, 0,
  -1, 4, 0, 0, 0, 0, 0, 0,
   3, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0
};

int main()
{
  // Inits the huffman "class"
  HuffM_init(&huffman_main);
  HuffM_init(&huffman_pixel_array);

  // Constructs a new instant
  HuffM_ctor(&huffman_main);
  HuffM_ctor(&huffman_pixel_array);

  (huffman_pixel_array.addList)(&huffman_pixel_array, vector1);
  (huffman_pixel_array.printList)(&huffman_pixel_array);
  // (huffman_pixel_array.sortList)(&huffman_pixel_array);
  // (huffman_pixel_array.printList)(&huffman_pixel_array);

  (huffman_main.addHuffmanList)(&huffman_main, &huffman_pixel_array);
  (huffman_main.printList)(&huffman_main);

  (huffman_pixel_array.addList)(&huffman_pixel_array, vector2);
  (huffman_pixel_array.printList)(&huffman_pixel_array);
  // (huffman_pixel_array.sortList)(&huffman_pixel_array);
  // (huffman_pixel_array.printList)(&huffman_pixel_array);

  (huffman_main.addHuffmanList)(&huffman_main, &huffman_pixel_array);
  (huffman_main.printList)(&huffman_main);

  HuffM_dtor(&huffman_pixel_array);
  HuffM_dtor(&huffman_main);
  return 0;
}
