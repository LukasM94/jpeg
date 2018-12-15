

PROJECT=jpeg

MAIN=main

TESTDIR=tests
TEST_DCT=testDCT
TEST_64BYTE=test64ByteToCosineAndBack

CC=gcc
CFLAGS=-g
CFLAGS+=-std=c99
CFLAGS+=-Wall

SOURCEDIR=src
INCLUDEDIR=include
BUILDDIR=build

SOURCES=$(shell find $(SOURCEDIR) -type f)

OBJECTS=$(addprefix $(BUILDDIR)/, $(notdir $(SOURCES:%.c=%.o)))


#
# Main
$(MAIN): $(OBJECTS) $(BUILDDIR)/$(MAIN).o
	$(CC) $(CFLAGS) $(OBJECTS) $(BUILDDIR)/$(MAIN).o -o $(PROJECT)


#
# Tests
$(TEST_DCT): $(OBJECTS) $(TESTDIR)/$(TEST_DCT).c
	$(CC) $(CFLAGS) -c $(TESTDIR)/$(TEST_DCT).c -o $(BUILDDIR)/$(TEST_DCT).o
	$(CC) $(CFLAGS) $(OBJECTS) $(BUILDDIR)/$(TEST_DCT).o -o $(PROJECT)

$(TEST_64BYTE): $(OBJECTS) $(TESTDIR)/$(TEST_64BYTE).c
	$(CC) $(CFLAGS) -c $(TESTDIR)/$(TEST_64BYTE).c -o $(BUILDDIR)/$(TEST_64BYTE).o
	$(CC) $(CFLAGS) $(OBJECTS) $(BUILDDIR)/$(TEST_64BYTE).o -o $(PROJECT)


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
