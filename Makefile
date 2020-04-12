
include /home/topeet/Desktop/itop4412/TOP_CONFIG.cfg

all: sample_app usr_app drv_ko copy_to_share

sample_app:
	echo "sample_app is $(SAMPLE_DIR)"
	make -C $(SAMPLE_DIR)/ all -j1

usr_app:
#	make -C $(USR_DIR)/ all -j1

drv_ko:
	make -C $(DRV_DIR)/ all -j1

copy_to_share:
	cp $(OUT_DIR)/* /home/share/

clean: sample_app_clean usr_app_clean drv_ko_clean copy_to_share_clean
 
sample_app_clean:
	make -C $(USR_DIR)/ clean -j1
	
usr_app_clean:
	make -C $(USR_DIR)/ clean -j1

drv_ko_clean:
	make -C $(DRV_DIR)/ clean -j1

copy_to_share_clean:
	rm -rf /home/share/*