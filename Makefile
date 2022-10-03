CXX = clang++
CXXFLAGS = -O2 -std=c++20

claire: StreamTitleGeneratorForSisterClaire.cpp
	$(CXX) $(CXXFLAGS) -o claire StreamTitleGeneratorForSisterClaire.cpp

zange: zange.patch StreamTitleGeneratorForSisterClaire.cpp
	patch StreamTitleGeneratorForSisterClaire.cpp zange.patch
	$(CXX) $(CXXFLAGS) -o zange StreamTitleGeneratorForSisterClaire.cpp
	patch -R StreamTitleGeneratorForSisterClaire.cpp zange.patch

all: claire zange

clean:
	rm -f claire zange
