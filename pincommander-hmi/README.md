## Flash a release
```
esptool -p COM12 -b 460800 --chip esp32s3 write_flash --flash_mode dio --flash_freq 80m --flash_size 4MB 0x0 pincomander-hmi-merged.bin
```
