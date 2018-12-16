

PROJECT=jpeg

MAIN=main

TESTDIR=tests
TEST_DCT=testDCT
TEST_64BYTE=test64ByteToCosineAndBack
TEST_HUFFMAN=testHuffman

CC=gcc
CFLAGS=-g
CFLAGS+=-std=c99
CFLAGS+=-Wall

LFLAGS=-lm

SOURCEDIR=src
INCLUDEDIR=include
BUILDDIR=build

SOURCES=$(shell find $(SOURCEDIR) -type f)

OBJECTS=$(addprefix $(BUILDDIR)/, $(notdir $(SOURCES:%.c=%.o)))


#
# Main
$(MAIN): $(OBJECTS) $(BUILDDIR)/$(MAIN).o
	$(CC) $(CFLAGS) $(OBJECTS) $(BUILDDIR)/$(MAIN).o $(LFLAGS) -o $(PROJECT)


#
# Tests
$(TEST_DCT): $(OBJECTS) $(TESTDIR)/$(TEST_DCT).c
	$(CC) $(CFLAGS) -c $(TESTDIR)/$(TEST_DCT).c -o $(BUILDDIR)/$(TEST_DCT).o
	$(CC) $(CFLAGS) $(OBJECTS) $(BUILDDIR)/$(TEST_DCT).o $(LFLAGS) -o $(PROJECT)

$(TEST_64BYTE): $(OBJECTS) $(TESTDIR)/$(TEST_64BYTE).c
	$(CC) $(CFLAGS) -c $(TESTDIR)/$(TEST_64BYTE).c -o $(BUILDDIR)/$(TEST_64BYTE).o
	$(CC) $(CFLAGS) $(OBJECTS) $(BUILDDIR)/$(TEST_64BYTE).o $(LFLAGS) -o $(PROJECT)

$(TEST_HUFFMAN): $(OBJECTS) $(TESTDIR)/$(TEST_HUFFMAN).c
	$(CC) $(CFLAGS) -c $(TESTDIR)/$(TEST_HUFFMAN).c -o $(BUILDDIR)/$(TEST_HUFFMAN).o
	$(CC) $(CFLAGS) $(OBJECTS) $(BUILDDIR)/$(TEST_HUFFMAN).o $(LFLAGS) -o $(PROJECT)


#
# Main file
$(BUILDDIR)/$(MAIN).o: $(MAIN).c
	$(CC) $(CFLAGS) -c $(MAIN).c -o $(BUILDDIR)/$(MAIN).o


#
# To build all the objects
$(BUILDDIR)/%.o: $(SOURCEDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@


#
# To remove all the objects of the build folder
clean: $(OBJECTS)
	rm $(BUILDDIR)/*.o
