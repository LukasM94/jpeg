

PROJECT=jpeg

MAIN=main
TEST_DCT=testDCT

CC=gcc
CFLAGS=-g
CFLAGS+=-std=c99
CFLAGS+=-Wall

SOURCEDIR=src
INCLUDEDIR=include
BUILDDIR=build

SOURCES=$(shell find $(SOURCEDIR) -type f)

OBJECTS=$(addprefix $(BUILDDIR)/, $(notdir $(SOURCES:%.c=%.o)))

$(MAIN): $(OBJECTS) $(BUILDDIR)/$(MAIN).o
	$(CC) $(CFLAGS) $(OBJECTS) $(BUILDDIR)/$(MAIN).o -o $(PROJECT)

$(TEST_DCT): $(OBJECTS) $(BUILDDIR)/$(TEST_DCT).o
	$(CC) $(CFLAGS) $(OBJECTS) $(BUILDDIR)/$(TEST_DCT).o -o $(PROJECT)

$(BUILDDIR)/$(TEST_DCT).o: $(TEST_DCT).c
	$(CC) $(CFLAGS) -c $(TEST_DCT).c -o $(BUILDDIR)/$(TEST_DCT).o

$(BUILDDIR)/$(MAIN).o: $(MAIN).c
	$(CC) $(CFLAGS) -c $(MAIN).c -o $(BUILDDIR)/$(MAIN).o

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: $(OBJECTS)
	rm $(BUILDDIR)/*.o
