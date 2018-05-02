# Makefile for the LP I Project "Bares"

# Creators:
# - Felipe Andrade
# - Felipe Ramos

# Makefile conventions
SHELL = /bin/sh

# Dir
incdir = ./include
srcdir = ./src
objdir = ./obj
bindir = ./bin
datadir = ./data

# Macros
CC = g++
CFLAGS = -Wall -g -ggdb -std=c++11 -I. -I$(incdir)
RM = -rm
TARGET = bares

HEADERS := $(wildcard $(incdir)/*)
SOURCES := $(wildcard $(srcdir)/*.cpp)
OBJECTS := $(SOURCES:$(srcdir)/%.cpp=$(objdir)/%.o)

all: project

project: $(OBJECTS) $(HEADERS) | $(bindir)
	@echo "Linking " $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $(bindir)/$(TARGET)
	@echo "Creating symlink..."
	@ln -sfv $(bindir)/$(TARGET) $(TARGET)	


$(OBJECTS): $(objdir)/%.o : $(srcdir)/%.cpp $(HEADERS) | $(objdir)
	$(CC) $(CFLAGS) -c $< -o $@

$(objdir): 
	@mkdir -p $(objdir)

$(bindir):
	@mkdir -p $(bindir)

# Clean phony
.PHONY: clean clean_txt clean_docs clean_proj

clean: clean_proj # clean_txt clean_docs

clean_proj:
	@echo "Removing obj files..."
	@$(RM) -f $(objdir)/*		# Remove obj files
	@echo "Removing bin files..."
	@$(RM) -f $(bindir)/*		# Remove bin files
	@echo "Removing symlink file..."
	@$(RM) -f $(TARGET)			# Remove symlink
	@echo "Cleanup is done!"
