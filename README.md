# IDOL BROKE?

## 1st update this pedastool code ##
1. Update this repo, file [src/rfid.cpp](./src/rfid.cpp)
2. Get predefined sticker number from kyle, and lookup in that file:
     e.g. he'll tell you he grabbed 'B2', then look for comment in file for B2 hex, e.g. '04 3D 21 0A 5F 70 81', heres what tripped me last time I did this.
   **YOU ONLY NEED THE first 4 CODES in that LIST**.  so this example, it would be 0x04,0x3D,0x21,0xA

3. Delete the first array entry for idol  location in the file with those 4 hex
   for example of a change [2390774](https://github.com/kevinclement/exitpuzzles-museum-cabinet-pedestal/commit/239077440b90273cc9f05847b7ecf177d098e4ae)


## 2nd update idol scanners ##
1. goto tomb server, and upate the matching rfid scanner for that idol
2. again, should just be 4 hex codes
  Example: [96fee7a5155e479bb74ca48b991dd1e7a02c0f45](https://github.com/kevinclement/exitpuzzles-museum-mausoleum-rfid-3-nano/commit/96fee7a5155e479bb74ca48b991dd1e7a02c0f45)
