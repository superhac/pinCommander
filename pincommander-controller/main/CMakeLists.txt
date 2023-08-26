#set(EXTRA_COMPONENT_DIRS $ENV{IDF_PATH}/components)

idf_component_register(SRCS "udp_server.c" "main.c" "usb.c" "accel.c" "udp_server.c"
                    INCLUDE_DIRS "."
                    REQUIRES driver led_strip esp_wifi nvs_flash
                    PRIV_REQUIRES mpu6050 espressif__esp_tinyusb freertos )
