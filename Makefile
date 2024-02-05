#
# These are the libraries that are needed to work with Vulkan 
#
getDependencies:
	@echo "Getting dependencies..."
	sudo apt install vulkan-tools
	sudo apt install libvulkan-dev
	sudo apt install vulkan-validationlayers-dev
	sudo apt install libglfw3-dev
	sudo apt install libglm-dev
	# TODO: Need google glslc compiler tools for vulkan
	sudo apt install libxxf86vm-dev libxi-dev

clean:
	echo "Cleaning..."
	cd VulkanTest && make clean 

build: clean
	echo "Building..."
	cd VulkanTest && make

build-codeql: clean
	echo "Building CodeQL..."
	cd VulkanTest && make build

check:
	echo "Checking..."

distcheck:
	echo "Dist Checking..."
