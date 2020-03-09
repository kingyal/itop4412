
include /home/topeet/Desktop/itop4412/TOP_CONFIG.cfg

TARGET := led_app

SRC_DIR ?= $(shell pwd)

SRCFILE := $(wildcard $(SRC_DIR)/*.c)

all:
	echo "leds.c is $(SRC_DIR)"
	echo "top is $(TOP_DIR)"
	echo "out is $(OUT_DIR)"
	
	arm-none-linux-gnueabi-gcc $(SRCFILE) -o $(TARGET) -static
	mv $(TARGET) $(OUT_DIR)
		
#make clean执行的操作是删除后缀为o的文件
clean:
	rm -rf  $(OUT_DIR)/$(TARGET)
