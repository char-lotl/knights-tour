CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I ./src/
COMPILECXX = $(CXX) -c $< -o $@
LINKCXX = $(CXX) $^ -o $@

rwildcard = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

SOURCES := $(call rwildcard,src/,*.cpp)
      
OBJ := $(patsubst src/%.cpp,obj/%.o,$(SOURCES))

DEPEND := $(patsubst src/%.cpp,dpnd/%.d,$(SOURCES))

PROGRAMNAME := knights-tour

$(PROGRAMNAME): $(OBJ)
	$(LINKCXX) $(CXXFLAGS)

dpnd/%.d: src/%.cpp
	@set -e; mkdir -p $(@D); rm -f $@; \
         $(CXX) -MM $(CXXFLAGS) $< > $@.1$$$$; \
         sed 's,\($(*F)\)\.o[ :]*,obj/$(*D)/\1.o $@ : ,g' < $@.1$$$$ > $@.2$$$$; \
         sed 's,/\./,/,g' < $@.2$$$$ > $@; \
         rm -f $@.1$$$$ $@.2$$$$;

include $(DEPEND)

obj/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(COMPILECXX) $(CXXFLAGS)

.PHONY: clean cleanobj cleandpnd

clean: cleanobj
	rm -f $(PROGRAMNAME)

cleanobj:
	find . -name '*.o' -delete

cleandpnd:
	find . -name '*.d' -delete