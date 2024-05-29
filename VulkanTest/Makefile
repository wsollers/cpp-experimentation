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

vulkan-test2: #vulkan-test2.cpp
	@echo "Compiling vulkan-test2.cpp"
	@echo "Compiling with $(CURRENT_COMPILER)"
	@echo "CFLAGS: $(CFLAGS)"
	$(CURRENT_COMPILER) $(CFLAGS) -o vulkan-test2 vulkan-test2.cpp $(LDFLAGS)

hello-triangle: #hello-triangle.cpp
	@echo "Compiling hello-triangle.cpp"
	@echo "Compiling with $(CURRENT_COMPILER)"
	@echo "CFLAGS: $(CFLAGS)"
	$(CURRENT_COMPILER) $(CFLAGS) -o hello-triangle hello-triangle.cpp $(LDFLAGS)

.PHONY: test clean

test: VulkanTest
	@echo "Running VulkanTest"
	./VulkanTest
	./vulkan-example

clean:
	rm -f VulkanTest vulkan-example vulkan-test2 hello-triangle

build: VulkanTest vulkan-example vulkan-test2 hello-triangle

