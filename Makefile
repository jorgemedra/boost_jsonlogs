
#********************************
# Compile with debug option:
#	make DBGFLG=-g
#********************************

TARGET 	=		sample 
SRC_DIR	= 		./src
OBJ_DIR = 		./obj
BIN_DIR = 		./bin
DBG_DIR = 		./debug
LOG_DIR = 		./logs

OBJ_FLS = 		$(OBJ_DIR)/main.o \
				$(OBJ_DIR)/mythread.o


CC 			= g++
GDB			= gdb
LFLAGS		= -pthread -lboost_log -lboost_thread -lboost_log_setup -lstdc++
CPPFLAGS	= -c -DBOOST_LOG_DYN_LINK -std=c++11 -Wall -MD

ifdef DBGFLG
echo Debug Flag = $(DBGFLG)
override CPPFLAGS += $(DBGFLG)
endif

all: build
	@echo "Cmpile Flags: " $(CPPFLAGS)

help:
	@echo "............................................."
	@echo "Build test: make"
	@echo "Build and activate debug: make DBGFLG=-g"
	@echo "Clean compiled files: make clean"

build: $(OBJ_DIR) $(OBJ_FLS) $(BIN_DIR)
	@echo "Building..."
	$(CC) $(LFLAGS) -o $(BIN_DIR)/$(TARGET) $(OBJ_FLS)
	@echo "Build finished."

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) $< -o $@

-include $(OBJ_DIR)/*.d

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) 

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)


clean:
	@echo "Cleaning..."
	@rm -rf $(OBJ_DIR)
	@rm -rf $(BIN_DIR)
	@rm -f $(SRC_DIR)/*.o
	@rm -f $(SRC_DIR)/*.d
	@rm -f $(LOG_DIR)/*.*
	@echo "Cleaned"