
all:
	make -C drv_led/ leds_ko
	make -C drv_test/ test_ko
	make -C drv_module_param/ module_param_ko
	make -C drv_request_cdev_num/ request_cdev_num_ko
	make -C drv_request_ascdev_num/ request_ascdev_num_ko
	make -C drv_register_cdev/ register_cdev_ko
	make -C drv_create_cnode/ create_cnode_ko
	make -C drv_cnode_fops/ cnode_fops_ko
	make -C drv_chr_driver_leds/ chr_driver_leds_ko
	
clean:
	make -C drv_led/ leds_clean
	make -C drv_test/ test_clean
	make -C drv_module_param/ module_param_clean
	make -C drv_request_cdev_num/ request_cdev_num_clean
	make -C drv_request_ascdev_num/ request_ascdev_num_clean
	make -C drv_register_cdev/ register_cdev_clean
	make -C drv_create_cnode/ create_cnode_clean
	make -C drv_cnode_fops/ cnode_fops_clean
	make -C drv_chr_driver_leds/ chr_driver_leds_clean