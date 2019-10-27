#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void main(int argc, char **argv) {
   FILE *ofp;

   uint8_t odata[4096];
   int address;
   int i,j;
   int tileidx;

   if (argc < 2) {
      printf("Usage: %s [tilemap file] [load address]\n", argv[0]);
      return;
   }

   ofp = fopen(argv[1], "w");
   if (ofp == NULL) {
      printf("Error opening %s for writing\n", argv[2]);
      return;
   }

   // start 12-bit with default address
   if (argc >= 4) {
      sscanf(argv[2],"%x",&address);
   } else {
      // set default load address to 0x4000
      address = 0x4000;
   }
   odata[0] = (uint8_t) (address & 0x00FF);
   odata[1] = (uint8_t) ((address & 0xFF00) >> 8);
   fwrite(odata,1,2,ofp);

   tileidx = 1;
   for (i=0;i<32;i++) {
      for (j=0;j<64;j++) {
         if ((j < 8) || (j>31) || (i < 5) || (i > 24)) {
            odata[(i*64+j)*2] = 0x00;
            odata[(i*64+j)*2+1] = 0x00;
         } else {
            odata[(i*64+j)*2] = tileidx & 0xff;
            odata[(i*64+j)*2+1] = (tileidx >> 8) & 0x03;
            tileidx++;
         }
      }
   }


   fwrite(odata,1,4096,ofp);

   fclose(ofp);
}
