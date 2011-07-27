#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "frame.h"




/***************opend_dcant****************************/
int opend_dcant(char *filename, fb_info fb_inf)
{
    
    fb_info jpeg_inf;
     int yres ;
     int xres1 ;
      int xres2;
     int  iloop;
      int jloop;

   
     
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
 
 for(jloop = 0;jloop < fb_inf.h;jloop++)
  {
    for(iloop = 0;iloop < fb_inf.w;iloop++)
      {
      
       yres = jloop +iloop*(((float)fb_inf.h)/fb_inf.w);
   
        xres1 = iloop;
         xres2 = fb_inf.w -iloop-1;
         if(yres <fb_inf.h)
          {
	    fb_pixel(fb_inf, xres1, yres, buf32[xres1 + (yres * fb_inf.w)]); 
          fb_pixel(fb_inf, xres2,(fb_inf.h- yres-1), buf32[xres2 + (fb_inf.h- yres-1) * fb_inf.w]); 



              fb_pixel(fb_inf, xres2, yres, buf32[xres2 + (yres * fb_inf.w)]); 
          fb_pixel(fb_inf, xres1,(fb_inf.h- yres-1), buf32[xres1 + (fb_inf.h- yres-1) * fb_inf.w]); 
            }

      }
     usleep(10);
    
}
     free(buf24);
    free(scale_buf);
    free(buf32);
   return 0;
}  


/************close_open***************/

int close_open(char *filename, fb_info fb_inf) 

{  fb_info jpeg_inf;
    int xres;
     int yres;
     int iloop;

      
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
 
     
 for(iloop =0;iloop < fb_inf.w/2;iloop++)   
{
      
               for(xres = iloop/2; xres < fb_inf.h - iloop/2;  ++xres)
                   {     
                   for (yres =iloop; yres<10+iloop;++yres)
                     {    if(fb_inf.w/2 >= yres)
    		           {fb_pixel(fb_inf, yres, xres, buf32[yres + (xres * fb_inf.w)]);
                             fb_pixel(fb_inf, fb_inf.w-yres-1, xres, buf32[(fb_inf.w-1-yres) + (xres * fb_inf.w)]);
                             }

                        }      
                         
                  } 
                  usleep(10);      
  }

for(yres =fb_inf.w/2;yres >=0; yres--)
{   for(xres =fb_inf.h/2;xres>=0;xres--)

{fb_pixel(fb_inf, yres, xres, buf32[yres + (xres * fb_inf.w)]);
 fb_pixel(fb_inf, fb_inf.w -1 -yres, xres, buf32[(fb_inf.w -1 -yres) + (xres * fb_inf.w)]);
    
fb_pixel(fb_inf, yres, fb_inf.h - 1 -xres, buf32[yres + ((fb_inf.h -1 -xres) * fb_inf.w)]);
fb_pixel(fb_inf, fb_inf.w -1 -yres, fb_inf.h - 1 -xres, buf32[(fb_inf.w -1 -yres) + ((fb_inf.h -1 -xres) * fb_inf.w)]);  

}
 usleep(10);
}


   free(buf24);
    free(scale_buf);
    free(buf32);
  return 0;
}
/************opend_cant1***********/

int opend_cant1(char *filename, fb_info fb_inf) 
{
    int yres ;
     int xres1 ;
      int xres2;
  int xres;
     int  iloop;
      int jloop;
     float x1 = 512.00;
      float y1 = 384.00;
     float k ;
 fb_info jpeg_inf;

    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
 for(jloop = 0;jloop < fb_inf.h/2;jloop++)
  {
    for(iloop =fb_inf.w/2;iloop < fb_inf.w;iloop++)
      {
          k = (iloop -x1)/(y1 -jloop);
   
        yres = k*(iloop - fb_inf.w/2);
        xres1 = iloop;
         xres2 = fb_inf.w -iloop-1;
         if(yres <fb_inf.h)
          {
	    fb_pixel(fb_inf, xres1, yres, buf32[xres1 + (yres * fb_inf.w)]); 
          fb_pixel(fb_inf, xres2,(fb_inf.h- yres-1), buf32[xres2 + (fb_inf.h- yres-1) * fb_inf.w]); 
            }

      }
     usleep(10);
    
}
for(yres =fb_inf.w/2;yres >= 0;yres--)
{
  for(xres = 0;xres < fb_inf.h;xres++)
 {
   fb_pixel(fb_inf, yres, xres, buf32[yres + (xres * fb_inf.w)]); 
   fb_pixel(fb_inf, fb_inf.w -1-yres, xres, buf32[(fb_inf.w -1 -yres) + (xres * fb_inf.w)]); 

}
  usleep(10);
 }   
    free(buf24);
    free(scale_buf);
    free(buf32);
  usleep(10);
   return 0;
}  





/****************four_corner*****************/
int four_corner(char *filename, fb_info fb_inf) 
{
    int yres ;
     int xres1 ;
      int xres2;
     int  iloop;
      int jloop;
  
  fb_info jpeg_inf;

    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
  
  for(jloop = fb_inf.h -1;jloop >=0;jloop--)
  {
    for(iloop = fb_inf.w -1 ;iloop >= 0;iloop--)
      {
          
       

       yres = jloop +iloop*(((float)fb_inf.h)/fb_inf.w);
   
   
         xres1 = iloop;
         xres2 = fb_inf.w -xres1-1;
        
         if(yres <fb_inf.h)
          {
	    fb_pixel(fb_inf, xres1, yres, buf32[xres1 + (yres * fb_inf.w)]); 
          fb_pixel(fb_inf, xres2,(fb_inf.h- yres-1), buf32[xres2 + (fb_inf.h- yres-1) * fb_inf.w]); 
            
           fb_pixel(fb_inf, xres2, yres, buf32[xres2 + (yres * fb_inf.w)]); 
          fb_pixel(fb_inf, xres1,(fb_inf.h- yres-1), buf32[xres1 + (fb_inf.h- yres-1) * fb_inf.w]); 
         }

      
     }
  usleep(10);


}
   free(buf24);
    free(scale_buf);
    free(buf32);
   return 0;
} 

