EXE = lab_gdb2

OBJS_DIR = .objs

OBJS_STUDENT = main.o skipList.o
OBJS_PROVIDED = png.o rgbapixel.o skipNode.o skipList_given.o

CXX = clang++
LD = clang++
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++1y -stdlib=libc++ -g -O0 $(WARNINGS) -MMD -MP -c
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

EXAMPLEFLAGS = $(WARNINGS) -std=c++1y -stdlib=libc++ -g -O0 -MMD -MP

all: $(EXE) $(EXE)-asan examples

examples: list playground recurse swap switch loop

loop: gdb-examples/loop.cpp
	$(CXX) $(EXAMPLEFLAGS) $(LDFLAGS) gdb-examples/loop.cpp -o loop

list: gdb-examples/list.cpp
	$(CXX) $(EXAMPLEFLAGS) $(LDFLAGS) gdb-examples/list.cpp -o list

playground: gdb-examples/playground.cpp
	$(CXX) $(EXAMPLEFLAGS) $(LDFLAGS) gdb-examples/playground.cpp -o playground
	
recurse: gdb-examples/recurse.cpp
	$(CXX) $(EXAMPLEFLAGS) $(LDFLAGS) gdb-examples/recurse.cpp -o recurse

swap: gdb-examples/swap.cpp
	$(CXX) $(EXAMPLEFLAGS) $(LDFLAGS) gdb-examples/swap.cpp -o swap

switch: gdb-examples/switch.cpp
	$(CXX) $(EXAMPLEFLAGS) $(LDFLAGS) gdb-examples/switch.cpp -o switch



# Pattern rules for object files
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@
$(OBJS_DIR)/%-asan.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $< -o $@

# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# Rules for executables... we can use a pattern for the -asan versions, but, unfortunately, we can't use a pattern for the normal executables
$(EXE):
	$(LD) $^ $(LDFLAGS) -o $@
%-asan:
	$(LD) $^ $(LDFLAGS) $(ASANFLAGS) -o $@


# Executable dependencies
$(EXE):      $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_PROVIDED))
$(EXE)-asan: $(patsubst %.o, $(OBJS_DIR)/%-asan.o, $(OBJS_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_PROVIDED))

# Include automatically generated dependencies
-include $(OBJS_DIR)/*.d

clean:
	rm -rf $(EXE) $(EXE)-asan $(OBJS_DIR) list swap switch recurse list playground loop

tidy: clean
	rm -rf out-degenerate.png out-structure.png

.PHONY: all tidy clean
