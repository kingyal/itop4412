
include /home/topeet/Desktop/itop4412/TOP_CONFIG.cfg

TARGET := sample

SRC_DIR ?= $(shell pwd)

INC_DIR :=  -I$(USR_DIR)/common/include/

SRCFILE := $(wildcard $(SRC_DIR)/*.c)
SRCFILE += $(wildcard $(USR_DIR)/common/*.c)

all:
	arm-none-linux-gnueabi-gcc $(SRCFILE) $(INC_DIR) -o $(TARGET) -static
	mv $(TARGET) $(OUT_DIR)
		
#make clean执行的操作是删除后缀为o的文件
clean:
	rm -rf  $(OUT_DIR)/$(TARGET)
