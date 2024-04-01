include config.mk
 
all:
	@$(MAKE) -C ./source/
	@$(MAKE) -C ./lib/
	@$(GXX) $(CFLAGS) -o $(BUILD_DIR)/$(EXEC_NAME) $(BUILD_DIR)/*.o

run:
	$(BUILD_DIR)/$(EXEC_NAME)
