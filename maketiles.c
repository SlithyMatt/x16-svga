#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define DEFAULT_WIDTH 384

void main(int argc, char **argv) {
   FILE *ifp;
   FILE *ofp;

   uint8_t *idata;
   uint8_t *odata;
   int width;
   int address;
   int i,j,k;

   if (argc < 3) {
      printf("Usage: %s [input raw data] [tile data file] [width] [load address]\n", argv[0]);
      return;
   }

   ifp = fopen(argv[1], "r");
   if (ifp == NULL) {
      printf("Error opening %s for reading\n", argv[1]);
      return;
   }
   ofp = fopen(argv[2], "w");
   if (ofp == NULL) {
      printf("Error opening %s for writing\n", argv[2]);
      return;
   }

   if (argc >=4) {
      width = atoi(argv[3]);
   } else {
      width = DEFAULT_WIDTH;
   }

   idata = malloc(width*16);
   odata = calloc(width,16);

   // start 12-bit with default address
   if (argc >= 5) {
      sscanf(argv[4],"%x",&address);
   } else {
      // set default load address to 0x5000
      address = 0x5000;
   }
   odata[0] = (uint8_t) (address & 0x00FF);
   odata[1] = (uint8_t) ((address & 0xFF00) >> 8);
   fwrite(odata,1,2,ofp);

   // make black tile
   fwrite(&odata[2],256,1,ofp);

   while (!feof(ifp)) {
      if (fread(idata,1,width*16,ifp) >= 6144) {
         for (i=0;i<width/16;i++) {
            for (j=0;j<16;j++) {
               for (k=0;k<16;k++) {
                  odata[i*256+j*16+k] = idata[j*width+i*16+k];
               }
            }
         }
         fwrite(odata,1,width*16,ofp);
      }
   }

   fclose(ifp);
   fclose(ofp);
   free(idata);
   free(odata);
}
