CFLAGS=-std=c++17 -O2

# Debugging flags
NDEBUG=1

# Logging flags
VERBOSE_LOGGING=1

LDFLAGS=-ggdb -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi -D VERBOSE_LOGGING=$(VERBOSE_LOGGING) 

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

validation-layers: #
	@echo "Compiling 02_validation_layers.cpp"
	@echo "Compiling with $(CURRENT_COMPILER)"
	@echo "CFLAGS: $(CFLAGS)"
	$(CURRENT_COMPILER) $(CFLAGS) -o validation-layers 02_validation_layers.cpp $(LDFLAGS)

.PHONY: test clean

test: VulkanTest
	@echo "Running VulkanTest"
	./VulkanTest
	./vulkan-example

clean:
	rm -f VulkanTest vulkan-example vulkan-test2 hello-triangle validation-layers

build: VulkanTest vulkan-example vulkan-test2 hello-triangle validation-layers

