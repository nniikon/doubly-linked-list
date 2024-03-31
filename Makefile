include config.mk
 
all:
	@$(MAKE) -C ./source/

run:
	$(BUILD_DIR)/$(EXEC_NAME)
