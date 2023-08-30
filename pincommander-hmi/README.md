The PinCommander HMI component is built with the Arduino IDE using the esp-idf 4.2.X SDK. The build is specific for the [Elecrow 5" esp32 based display](https://www.elecrow.com/esp32-display-5-inch-hmi-display-rgb-tft-lcd-touch-screen-support-lvgl.html) and it may work on other models but that hasn't been tested. All the required Arduino libraries are installed in the library directory.

## Arduino Libraries
- GFX Library for Arduino
- TAMC_GT911
- lvgl

The UI is built using [Square Line Studio](https://squareline.io/) which provides visual way to build UI interfaces using the LVGL UI library.  

## Flash a release
```
esptool -p COM12 -b 460800 --chip esp32s3 write_flash --flash_mode dio --flash_freq 80m --flash_size 4MB 0x0 pincomander-hmi-merged.bin
```
