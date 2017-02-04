EXENAME = testimage
OBJS = png.o rgbapixel.o image.o testimage.o
 
CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread

all: $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

png.o : png.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp

image.o : image.cpp image.h
	$(CXX) $(CXXFLAGS) image.cpp

testimage.o : testimage.cpp
	$(CXX) $(CXXFLAGS) testimage.cpp

clean:
	-rm if *.o $(EXENAME)


