CFLAGS=-std=c++17 -O2

LDFLAGS=-ggdb -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

GCC=g++
CLANG=clang++

CURRENT_COMPILER=$(CLANG)

VulkanTest: #main.cpp
	@echo "Compiling main.cpp"
	@echo "Compiling with $(CURRENT_COMPILER)"
	@echo "CFLAGS: $(CFLAGS)"
	$(CURRENT_COMPILER) $(CFLAGS) -o VulkanTest main.cpp $(LDFLAGS)

vulkan-example: #vulkan-example.cpp
	@echo "Compiling vulkan-example.cpp"
	@echo "Compiling with $(CURRENT_COMPILER)"
	@echo "CFLAGS: $(CFLAGS)"
	$(CURRENT_COMPILER) $(CFLAGS) -o vulkan-example vulkan-example.cpp $(LDFLAGS)

.PHONY: test clean

test: VulkanTest
	@echo "Running VulkanTest"
	./VulkanTest
	./vulkan-example

clean:
	rm -f VulkanTest vulkan-example

build: VulkanTest vulkan-example

