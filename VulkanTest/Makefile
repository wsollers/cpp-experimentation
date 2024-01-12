CFLAGS=-std=c++17 -O2

LDFLAGS=-ggdb -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

GCC=g++
CLANG=clang++

CURRENT_COMPILER=$(CLANG)

VulkanTest: main.cpp
	$(CURRENT_COMPILER) $(CFLAGS) -o VulkanTest main.cpp $(LDFLAGS)

.PHONY: test clean

test: VulkanTest
	./VulkanTest

clean:
	rm -f VulkanTest
