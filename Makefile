
include /home/topeet/Desktop/itop4412/TOP_CONFIG.cfg

all: usr_app drv_ko

usr_app:
	make -C $(USR_DIR)/ all -j1

drv_ko:
	make -C $(DRV_DIR)/ all -j1

clean: usr_app_clean drv_ko_clean
 
usr_app_clean:
	make -C $(USR_DIR)/ clean -j1

drv_ko_clean:
	make -C $(DRV_DIR)/ clean -j1