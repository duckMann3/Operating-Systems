# Compiler
CXX := g++
CC  := gcc

# Folder
EXEDIR := exe

# Flags
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O0 -g 
CGLAGs   ?= -std=c11   -Wall -Wextra -O0 -g
LDFLAGS  ?=
LDLIBS   ?=

# Discover Sources in This Folder
CPP_SRCS := $(wildcard *.cpp)
C_SRCS   := $(wildcard *.c)

# Clips "rtos.cpp" to "rtos"
CPP_PROGS := $(basename $(CPP_SRCS))
C_PROGS   := $(basename $(C_SRCS))

PROGS := $(sort $(CPP_PROGS) $(C_PROGS))
EXES  := $(addprefix $(EXEDIR)/, $(PROGS))

# Default target: build everything
.PHONY: all
all: $(EXES)

# Ensure exe/ exits
$(EXEDIR):
	mkdir -p $(EXEDIR)

# Build C++ single-file programs: exe/name from name.cpp
$(EXEDIR)/%: %.cpp | $(EXEDIR)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS) $(LDLIBS)

# Build C single-file programs: exe/name from name.c
$(EXEDIR)/%: %.c | $(EXEDIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS) $(LDLIBS)
	
# Convenience: "make rtos" builds exe/rtos
.PHONY: $(PROGS)
$(PROGS): %: $(EXEDIR)/%

# Optional: run like "make run-rtos"
.PHONY: run-%
run-%: $(EXEDIR)/%
	./$<

.PHONY: clean
clean:
	rm -rf $(EXEDIR)
