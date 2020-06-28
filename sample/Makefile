
include /home/topeet/Desktop/itop4412/TOP_CONFIG.cfg

TARGET := sample

SRC_DIR ?= $(shell pwd)

INC_DIR :=  -I$(SAMPLE_DIR)/common/include/			\
			-I$(SAMPLE_DIR)/usr_led/include/		\
			-I$(SAMPLE_DIR)/usr_test/include/		\
			-I$(SAMPLE_DIR)/ring_buffer/include/

SRCFILE := $(wildcard $(SAMPLE_DIR)/main.c)
SRCFILE += $(wildcard $(SAMPLE_DIR)/common/*.c)
SRCFILE += $(wildcard $(SAMPLE_DIR)/usr_led/*.c)
SRCFILE += $(wildcard $(SAMPLE_DIR)/usr_test/*.c)
SRCFILE += $(wildcard $(SAMPLE_DIR)/ring_buffer/*.c)

all:
	arm-none-linux-gnueabi-gcc $(SRCFILE) $(INC_DIR) -o $(TARGET) -static
	mv $(TARGET) $(OUT_DIR)
		
#make clean执行的操作是删除后缀为o的文件
clean:
	rm -rf  $(OUT_DIR)/$(TARGET)
