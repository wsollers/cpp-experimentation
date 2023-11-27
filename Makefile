getDependencies:
	@echo "Getting dependencies..."
	sudo apt install vulkan-tools
	sudo apt install libvulkan-dev
	sudo apt install vulkan-validationlayers-dev
	sudo apt install libglfw3-dev
	sudo apt install libglm-dev
	# TODO: Need google glslc compiler tools for vulkan
	sudo apt install libxxf86vm-dev libxi-dev
