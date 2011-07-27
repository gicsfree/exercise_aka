/* display special effect .c*/
#include<stdlib.h>
#include<string.h>
#include<stdlib.h>

#include"frame.h"

/* from up to down by roll. */
int display_shutters5(char *filename, fb_info fb_inf)
{
 
    int iloop = 0;
    int jloop = 0;
    int n = 0;
    int k = 0;
    fb_info jpeg_inf;
    u32_t buf321[fb_inf.w * fb_inf.h];
  
   
   
    
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

    for(iloop = 0; iloop < (fb_inf.w *fb_inf.h); ++iloop)              //shi tu pian bian niang 
     {
        *((u8_t *)&buf321[iloop] + 2) = 0.5 * (*((u8_t *)&buf32[iloop] + 2)) + 0.5 * 0x00;
        *((u8_t *)&buf321[iloop] + 1) = 0.5 * (*((u8_t *)&buf32[iloop] + 1)) + 0.5 * 0x00;
        *((u8_t *)&buf321[iloop] + 0) = 0.5 * (*((u8_t *)&buf32[iloop] + 0)) + 0.5 * 0x00;
        *((u8_t *)&buf321[iloop] + 3) = 0x00;
       }

    while ( n < 1000)
     {
        for (jloop = 0 ; jloop < (fb_inf.h); jloop++)
          {
             for(iloop = 0 ; iloop < (fb_inf.w); iloop++)
                {
                     if( jloop >= n && jloop <= n + 5)
                         {
                              fb_pixel(fb_inf, iloop, jloop, buf32[iloop + jloop * fb_inf.w]);
                                   
                               if ((jloop + 100) < 768)
                                  for (k = 1; k <= 50; k++)
                                      fb_pixel(fb_inf, iloop, jloop + k, buf321[iloop + ((jloop + 100) - k) * fb_inf.w]);
                               
                          }        
                 }
            }
          usleep(80000);
          n += 5;

      }
	return 0;
}


/* from middle to left and right by roll*/
int display_shutters6(char *filename, fb_info fb_inf)
{
 
    int iloop = 0;
    int jloop = 0;
    int n = 0;
    int k = 0;
    fb_info jpeg_inf;
    u32_t buf321[fb_inf.w * fb_inf.h];
  
   
   
    
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

    for(iloop = 0; iloop < (fb_inf.w *fb_inf.h); ++iloop)              //shi tu pian bian niang 
     {
        *((u8_t *)&buf321[iloop] + 2) = 0.8 * (*((u8_t *)&buf32[iloop] + 2)) + 0.2 * 0x00;
        *((u8_t *)&buf321[iloop] + 1) = 0.8 * (*((u8_t *)&buf32[iloop] + 1)) + 0.2 * 0x00;
        *((u8_t *)&buf321[iloop] + 0) = 0.8 * (*((u8_t *)&buf32[iloop] + 0)) + 0.2 * 0x00;
        *((u8_t *)&buf321[iloop] + 3) = 0x00;
       }

    while ( n < 1000)
     {
        for (iloop = 0 ; iloop <= 512; iloop++)
          {
             for(jloop = 0 ; jloop < (fb_inf.h); jloop++)
                {
                     if((iloop >= n && iloop <= n + 5))
                         {   
                               // fb_pixel(fb_inf, 512 - iloop, jloop, buf32[(512 - iloop) + jloop * fb_inf.w]);
                                for (k = 1; k < 30; k++)
                                     fb_pixel(fb_inf, 512 - iloop + k - 1, jloop,
                                              buf32[((512 - iloop) + 60 - k)+ jloop * fb_inf.w]);
                     
                                //fb_pixel(fb_inf, 512 + iloop, jloop, buf32[(512 + iloop) + jloop * fb_inf.w]);
                                 for (k = 1; k < 30; k++)
                                     fb_pixel(fb_inf, 512 + iloop - k, jloop,
                                              buf32[((512 + iloop) - 60 + k)+ jloop * fb_inf.w]);
   
                          }        
                 }
            }
          usleep(60000);
              n += 5;

      }
	return 0;
}


/* display from up to down by all picture. */
int display_shutters7(char *filename, fb_info fb_inf)
{
    int iloop = 0;
    int jloop = 0;
    fb_info jpeg_inf;
   
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);


     for (jloop = 0; jloop < (fb_inf.h); jloop++)
      {
	   for(iloop = 0; iloop < (fb_inf.w); iloop++)
             {       
                 fb_pixel(fb_inf, iloop, 0, buf32[iloop + (768 - jloop) * fb_inf.w]);
                 
              }
          if (jloop < 767)
          memmove((fb_inf.fbmem + fb_inf.w * 4), fb_inf.fbmem, (jloop + 1)* fb_inf.w * 4);
       
           //usleep(500);
      }
     
    free(buf24);
    free(scale_buf);
    free(buf32);
    return 0;
}


/* display from a cornor to the other corner by all picture. */
/*int display_shutters8(char *filename, fb_info fb_inf)
{
    int iloop = 0;
    int jloop = 0;
    int n = 0;
    fb_info jpeg_inf;
   
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

     while (n < 256)
      { 
         for (jloop = 0; jloop < 3 * (n + 1); jloop++)
           {
	       for(iloop = 0; iloop < 4 * (n + 1); iloop++)
                    if ((iloop < 4 && jloop < 3 * (n + 1)) || (jloop < 3 && iloop < 4 * (n + 1)))
                       {                             
                         fb_pixel(fb_inf, iloop , jloop, buf32[(fb_inf.w - 4 * n + iloop) + (fb_inf.h - 3 * n + jloop) * fb_inf.w]);
                         }
     
           }
         usleep(800);
          
         if (n < 255)
            memmove((fb_inf.fbmem + (3 * fb_inf.w  + 4)* 4), fb_inf.fbmem, (3 * (n + 1)) * fb_inf.w * 4);
     
         n++;
      }

    free(buf24);
    free(scale_buf);
    free(buf32);
    return 0;
}

*/


/* display from a corner to the other corner by all picture.*/
int display_shutters8(char *filename, fb_info fb_inf)
{
 
    int iloop = 0;
    int jloop = 0;
    int n = 0;
    fb_info jpeg_inf;
   
   
    
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    while (n < 256)
     {
   
        for (iloop = 0 ; iloop < (fb_inf.w); iloop++)
         {
	     for(jloop = 0 ; jloop < (fb_inf.h); jloop++)
              {
                  if (iloop < 4 * (n + 1) && jloop < 3 * (n + 1))
                     fb_pixel(fb_inf, iloop , jloop, buf32[(fb_inf.w - 4 * n + iloop)  + (fb_inf.h  - 3 * n + jloop) * fb_inf.w]);    
               }

          }
    
         n += 1;
     }
    free(buf24);
    free(scale_buf);
    free(buf32);
    return 0;
}


/* from middle to bsides by roll like waterwave.*/
int display_shutters9(char *filename, fb_info fb_inf)
{
  //  int width = 128;
    int iloop = 0;
    int jloop = 0;
    int x0 = fb_inf.w / 2, y0 = fb_inf.h / 2;
    float r0 = 0, r1 = 0, r2 = 0, r3 = 0, r4 = 0, r5 = 0, r6 = 0, r7 = 0, r8 = 0, r9 = 0;
    fb_info jpeg_inf;
    u32_t buf321[fb_inf.h * fb_inf.w];
   
   
    
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

    for(iloop = 0; iloop < (fb_inf.w *fb_inf.h); ++iloop)              //shi tu pian bian niang 
     {
        *((u8_t *)&buf321[iloop] + 2) = 0.8 * (*((u8_t *)&buf32[iloop] + 2)) + 0.2 * 0x4F;
        *((u8_t *)&buf321[iloop] + 1) = 0.8 * (*((u8_t *)&buf32[iloop] + 1)) + 0.2 * 0x4F;
        *((u8_t *)&buf321[iloop] + 0) = 0.8 * (*((u8_t *)&buf32[iloop] + 0)) + 0.2 * 0x4F;
        *((u8_t *)&buf321[iloop] + 3) = 0x00;
       }
    
  while (r9 < 650){
   
    for (iloop = 0; iloop < (fb_inf.w); iloop++)
    {
	for(jloop = 0; jloop < (fb_inf.h); jloop++)
        {
            if(((iloop - x0) * (iloop - x0) + (jloop - y0) * (jloop - y0) <= (r0 + 10)*(r0 + 10))
              && ((iloop - x0) * (iloop - x0) + (jloop - y0) * (jloop - y0) >= r0 * r0))
              {
                  fb_pixel(fb_inf, iloop, jloop, buf321[iloop + jloop * fb_inf.w]);
               }     
          }
     }

   for (iloop = 0; iloop < (fb_inf.w); iloop++)
    {
	for(jloop = 0; jloop < (fb_inf.h); jloop++)
        {
            if(((iloop - x0) * (iloop - x0) + (jloop - y0) * (jloop - y0) <= (r1 + 9.6)*(r1 + 9.6))
              && ((iloop - x0) * (iloop - x0) + (jloop - y0) * (jloop - y0) >= r1 * r1))
              {
                  fb_pixel(fb_inf, iloop, jloop, buf32[iloop + jloop * fb_inf.w]);
              }     
         }
     }
   for (iloop = 0; iloop < (fb_inf.w); iloop++)
    {
	for(jloop = 0; jloop < (fb_inf.h); jloop++)
        {
            if(((iloop - x0) * (iloop - x0) + (jloop - y0) * (jloop - y0) <= (r2 + 9.0)*(r2 + 9.0))
              && ((iloop - x0) * (iloop - x0) + (jloop - y0) * (jloop - y0) >= r2 * r2))
              {
                  fb_pixel(fb_inf, iloop, jloop, buf321[iloop + jloop * fb_inf.w]);
              }     
         }
     }
   for (iloop = 0; iloop < (fb_inf.w); iloop++)
    {
	for(jloop = 0; jloop < (fb_inf.h); jloop++)
        {
            if(((iloop - x0) * (iloop - x0) + (jloop - y0) * (jloop - y0) <= (r3 + 8.2)*(r3 + 8.2))
              && ((iloop - x0) * (iloop - x0) + (jloop - y0) * (jloop - y0) >= r3 * r3))
              {
                  fb_pixel(fb_inf, iloop, jloop, buf32[iloop + jloop * fb_inf.w]);
              }     
         }
     }
    for (iloop = 0; iloop < (fb_inf.w); iloop++)
    {
	for(jloop = 0; jloop < (fb_inf.h); jloop++)
        {
            if(((iloop - x0) * (iloop - x0) + (jloop - y0) * (jloop - y0) <= (r4 + 7.2)*(r4 + 7.2))
              && ((iloop - x0) * (iloop - x0) + (jloop - y0) * (jloop - y0) >= r4 * r4))
              {
                  fb_pixel(fb_inf, iloop, jloop, buf321[iloop + jloop * fb_inf.w]);
              }     
         }
     }
   for (iloop = 0; iloop < (fb_inf.w); iloop++)
    {
	for(jloop = 0; jloop < (fb_inf.h); jloop++)
        {
            if(((iloop - x0) * (iloop - x0) + (jloop - y0) * (jloop - y0) <= (r5 + 6.0)*(r5 + 6.0))
              && ((iloop - x0) * (iloop - x0) + (jloop - y0) * (jloop - y0) >= r5 * r5))
              {
                  fb_pixel(fb_inf, iloop, jloop, buf32[iloop + jloop * fb_inf.w]);
              }     
         }
     }
    for (iloop = 0; iloop < (fb_inf.w); iloop++)
     {
	for(jloop = 0; jloop < (fb_inf.h); jloop++)
        {
            if(((iloop - x0) * (iloop - x0) + (jloop - y0) * (jloop - y0) <= (r6 + 5.0)*(r6 + 5.0))
              && ((iloop - x0) * (iloop - x0) + (jloop - y0) * (jloop - y0) >= r6 * r6))
              {
                  fb_pixel(fb_inf, iloop, jloop, buf321[iloop + jloop * fb_inf.w]);
              }     
         }
     }
   for (iloop = 0; iloop < (fb_inf.w); iloop++)
    {
       for(jloop = 0; jloop < (fb_inf.h); jloop++)
        {
            if(((iloop - x0) * (iloop - x0) + (jloop - y0) * (jloop - y0) <= (r7 + 4.2)*(r7 + 4.2))
              && ((iloop - x0) * (iloop - x0) + (jloop - y0) * (jloop - y0) >= r7 * r7))
              {
                  fb_pixel(fb_inf, iloop, jloop, buf32[iloop + jloop * fb_inf.w]);
              }     
         }
     }
   for (iloop = 0; iloop < (fb_inf.w); iloop++)
    {
	for(jloop = 0; jloop < (fb_inf.h); jloop++)
        {
            if(((iloop - x0) * (iloop - x0) + (jloop - y0) * (jloop - y0) <= (r8 + 3.6)*(r8 + 3.6))
              && ((iloop - x0) * (iloop - x0) + (jloop - y0) * (jloop - y0) >= r8 * r8))
              {
                  fb_pixel(fb_inf, iloop, jloop, buf321[iloop + jloop * fb_inf.w]);
              }     
         }
     }
   for (iloop = 0; iloop < (fb_inf.w); iloop++)
    {
	for(jloop = 0; jloop < (fb_inf.h); jloop++)
        {
            if(((iloop - x0) * (iloop - x0) + (jloop - y0) * (jloop - y0) <= (r9 + 3.2)*(r9 + 3.2))
              && ((iloop - x0) * (iloop - x0) + (jloop - y0) * (jloop - y0) >= r9 * r9))
              {
                  fb_pixel(fb_inf, iloop, jloop, buf32[iloop + jloop * fb_inf.w]);
              }     
         }
     }
  r0 += 10; r1 += 9.6; r2 += 9; r3 += 8.2; r4 += 7.2; r5 += 6; r6 += 5; r7 += 4.2; r8 += 3.6; r9 += 3.2;
  }
    free(buf24);
    free(scale_buf);
    free(buf32);
    return 0;
}


/* display from center to four besides. */
int display_shutters10(char *filename, fb_info fb_inf)
{
    int iloop = 0;
    int jloop = 0;
    int k = 0;
    int n = 0;
    fb_info jpeg_inf;
   
   
    
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
     
    while ( k < 600)
    {
        for (iloop = 0; iloop < (fb_inf.w); iloop++)
          {
	      for(jloop = 0; jloop < (fb_inf.h); jloop++)
               {
                  if (jloop <= fb_inf.h / 2 && iloop <= (fb_inf.w / 2 - k) && (iloop >= fb_inf.w / 2 - k - 4))
                      fb_pixel(fb_inf, iloop, jloop, buf32[iloop + jloop * fb_inf.w]);
                  if (iloop >= fb_inf.w / 2 && jloop <= (fb_inf.h / 2 - n) && jloop >= (fb_inf.h / 2 - n - 3))   
                      fb_pixel(fb_inf, iloop, jloop, buf32[iloop + jloop * fb_inf.w]);
                  if (jloop >= fb_inf.h / 2 && iloop <= (fb_inf.w / 2 + k + 4) && iloop >= (fb_inf.w / 2 + k))  
                      fb_pixel(fb_inf, iloop, jloop, buf32[iloop + jloop * fb_inf.w]);
                  if (iloop <= fb_inf.w / 2 && jloop <= (fb_inf.h / 2 + n + 3) && jloop >= (fb_inf.h / 2 + n))   
                      fb_pixel(fb_inf, iloop, jloop, buf32[iloop + jloop * fb_inf.w]);  
               }

          }
         k += 4;
         n += 3;
    }

    free(buf24);
    free(scale_buf);
    free(buf32);
    return 0;
}


/* display from up to down by all picture. 刷下来 */
int display_shutters11(char *filename, fb_info fb_inf)
{
 
    int iloop = 0;
    int jloop = 0;
    int n = 0;
    int k = 0;
    fb_info jpeg_inf;
    u32_t buf321[fb_inf.w * fb_inf.h];
  
   
   
    
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);

    for(iloop = 0; iloop < (fb_inf.w *fb_inf.h); ++iloop)              //shi tu pian bian niang 
     {
        *((u8_t *)&buf321[iloop] + 2) = 0.3 * (*((u8_t *)&buf32[iloop] + 2)) + 0.7 * 0xFF;
        *((u8_t *)&buf321[iloop] + 1) = 0.3 * (*((u8_t *)&buf32[iloop] + 1)) + 0.7 * 0xFF;
        *((u8_t *)&buf321[iloop] + 0) = 0.3 * (*((u8_t *)&buf32[iloop] + 0)) + 0.7 * 0xFF;
        *((u8_t *)&buf321[iloop] + 3) = 0x00;
       }

    while ( n < 800)
     {
        for (jloop = 0 ; jloop < (fb_inf.h); jloop++)
          {
             for(iloop = 0 ; iloop < (fb_inf.w); iloop++)
                {
                     if( jloop >= n && jloop <= n + 5)
                         {
                              fb_pixel(fb_inf, iloop, jloop, buf32[iloop + jloop * fb_inf.w]);
                                       
                              if (fb_inf.h - jloop > 2)
                                  for (k = 1; k <= 2 ; k++)
                                      fb_pixel(fb_inf, iloop, jloop + k, buf321[iloop + (jloop + k) * fb_inf.w]);
                              if (fb_inf.h - jloop > 7)
                                  for (k = 3; k <= 7 ; k++)
                                      fb_pixel(fb_inf, iloop, jloop + k, buf32[iloop + (jloop + k) * fb_inf.w]);
                              if (fb_inf.h - jloop > 11)
                                  for (k = 8; k <= 11; k++)
                                      fb_pixel(fb_inf, iloop, jloop + k, buf321[iloop + (jloop + k) * fb_inf.w]);
                              if (fb_inf.h - jloop > 17)
                                  for (k = 12; k <= 17; k++)
                                      fb_pixel(fb_inf, iloop, jloop + k, buf32[iloop + (jloop + k) * fb_inf.w]);
                              if (fb_inf.h - jloop > 22)
                                  for (k = 18; k <= 22; k++)
                                      fb_pixel(fb_inf, iloop, jloop + k, buf321[iloop + (jloop + k) * fb_inf.w]);
                              if (fb_inf.h - jloop > 28)
                                  for (k = 23; k <= 28; k++)
                                      fb_pixel(fb_inf, iloop, jloop + k, buf32[iloop + (jloop + k) * fb_inf.w]);
                              if (fb_inf.h - jloop > 37)
                                  for (k = 29; k <= 37; k++)
                                      fb_pixel(fb_inf, iloop, jloop + k, buf321[iloop + (jloop + k) * fb_inf.w]);
                              if (fb_inf.h - jloop > 40)
                                  for (k = 37; k <= 40; k++)
                                      fb_pixel(fb_inf, iloop, jloop + k, buf32[iloop + (jloop + k) * fb_inf.w]);
                              if (fb_inf.h - jloop > 47)
                                  for (k = 41; k <= 47; k++)
                                      fb_pixel(fb_inf, iloop, jloop + k, buf321[iloop + (jloop + k) * fb_inf.w]);
                              if (fb_inf.h - jloop > 50)
                                  for (k = 47; k <= 50; k++)
                                      fb_pixel(fb_inf, iloop, jloop + k, buf32[iloop + (jloop + k) * fb_inf.w]);
                          }        
                 }
            }
          usleep(800);
          n += 5;

      }
	return 0;
}

/* display from a corner to the contrast corner */
int display_shutters12(char *filename, fb_info fb_inf)
{
 
    int iloop = 0;
    int jloop = 0;
    int n = 0;
    fb_info jpeg_inf;
   
   
    
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    while (n < 256)
     {
   
        for (iloop = 0 ; iloop < (fb_inf.w); iloop++)
         {
	     for(jloop = 0 ; jloop < (fb_inf.h); jloop++)
              {
                   if ((iloop >= 4 * n && iloop <= 4 * (n + 1) && jloop < 3 * (n + 1)) || (iloop < 4 * (n + 1) && jloop <= 3 * (n + 1) && jloop >= 3 * n))                  
                       fb_pixel(fb_inf, iloop , jloop, buf32[iloop  + jloop * fb_inf.w]);  
               }

          }
    
         n += 1;
     }
    free(buf24);
    free(scale_buf);
    free(buf32);
    return 0;
}

/* display by a section and a section .*/
int display_shutters13(char *filename, fb_info fb_inf)
{
 
    int iloop = 0;
    int jloop = 0;
    int flag_x;
    int flag_y;
    fb_info jpeg_inf;
   
   
    
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    
    for(jloop = 0; jloop < fb_inf.h; jloop++)
     {
        for (iloop = 0; iloop < fb_inf.w; iloop++)
         {
		flag_x = (iloop/16)%2;
		flag_y = (jloop/15)%2;

		if( ((flag_x == 0) && (flag_y == 0)) || ((flag_x == 1) && (flag_y == 1)) )
		 {
    		    fb_pixel(fb_inf, iloop, jloop, buf32[iloop + jloop * fb_inf.w]);		          
		 }
	 }
	usleep(2000);
     }

	usleep(6000);

    for(iloop = 0; iloop < fb_inf.w; iloop++)
     {
        for (jloop = 0; jloop < fb_inf.h; jloop++)
         {
		flag_x = (iloop/16)%2;
		flag_y = (jloop/15)%2;

		if( ((flag_x == 1) && (flag_y == 0)) || ((flag_x == 0) && (flag_y == 1)) )
		{
    		    fb_pixel(fb_inf, iloop, jloop, buf32[iloop + jloop * fb_inf.w]);		          
		}
	 }
	usleep(2000);
     }
    free(buf24);
    free(scale_buf);
    free(buf32);
    return 0;
}


/* display from foure besides to centrer. */
int display_shutters14(char *filename, fb_info fb_inf)
{
    int iloop = 0;
    int jloop = 0;
    int k = 0;
    int n = 0;
    fb_info jpeg_inf;
   
   
    
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
     
    while ( k < 550)
    {
        for (iloop = 0; iloop < (fb_inf.w); iloop++)
          {
	      for(jloop = 0; jloop < (fb_inf.h); jloop++)
               {
                  if (iloop <= fb_inf.w / 2 && jloop >= n && jloop <= n + 3   )
                      fb_pixel(fb_inf, iloop, jloop, buf32[iloop + jloop * fb_inf.w]);
                  if (jloop <= fb_inf.h / 2 && iloop <= (fb_inf.w - k) && iloop >= (fb_inf.w  - k - 4))   
                      fb_pixel(fb_inf, iloop, jloop, buf32[iloop + jloop * fb_inf.w]);
                  if (iloop >= fb_inf.w  / 2 && jloop <= (fb_inf.h - n) && jloop >= (fb_inf.h - n - 3))  
                      fb_pixel(fb_inf, iloop, jloop, buf32[iloop + jloop * fb_inf.w]);
                  if (jloop >= fb_inf.h / 2 && iloop <= k + 4  && iloop >= k)   
                      fb_pixel(fb_inf, iloop, jloop, buf32[iloop + jloop * fb_inf.w]);  
               }

          }
         k += 4;
         n += 3;
    }

    free(buf24);
    free(scale_buf);
    free(buf32);
    return 0;
}


/* ahead display weight, then display height. */
int display_shutters15(char *filename, fb_info fb_inf)
{
 
    int iloop = 0;
    int jloop = 0;
    int n = 0;
    int k = 0;
    fb_info jpeg_inf;
   
   
    
    u8_t *buf24 = decode_jpeg(filename, &jpeg_inf);
    u8_t *scale_buf = scale24(buf24, fb_inf, jpeg_inf);
    u32_t *buf32 = rgb24to32(scale_buf, fb_inf);
    while (k < 64)
     {
          for (iloop = 0; iloop < fb_inf.w; iloop++)
            {
                 for (jloop = 0; jloop < fb_inf.h; jloop++)
                    {
                         if(iloop < (fb_inf.w / 2 + n + 4) && iloop > (fb_inf.w / 2 - n - 4)
                             && jloop < (fb_inf.h / 2 + k + 3) && jloop > (fb_inf.h / 2 -k - 3))
                                 fb_pixel(fb_inf, iloop, jloop, buf32[iloop + jloop * fb_inf.w]); 
                     }

              }
           k += 3;
           n += 4;
      }
     while ( n < fb_inf.w / 2)
      {
          for (iloop = 0; iloop < fb_inf.w; iloop++)
            {
                 for (jloop = 0; jloop < fb_inf.h; jloop++)
                    {
                         if(iloop < (fb_inf.w / 2 + n + 4) && iloop > (fb_inf.w / 2 - n - 4)
                             && jloop < (fb_inf.h / 2 + k + 3) && jloop > (fb_inf.h / 2 -k - 3))
                                 fb_pixel(fb_inf, iloop, jloop, buf32[iloop + jloop * fb_inf.w]); 
                     }

              }
          // k += 3;
           n += 4;
      }

    for (jloop = 0; jloop < 320; jloop++)
     {
         for (iloop = 0; iloop < fb_inf.w; iloop++)
             {
                        
                fb_pixel(fb_inf, iloop, fb_inf.h / 2 - 64 - jloop, buf32[iloop + (fb_inf.h / 2 - 64 - jloop) * fb_inf.w]);
                fb_pixel(fb_inf, iloop, fb_inf.h / 2 + 64 + jloop, buf32[iloop + (fb_inf.h / 2 + 64 + jloop) * fb_inf.w]);       
                     }
           usleep(8000);

              }
      
    free(buf24);
    free(scale_buf);
    free(buf32);
    return 0;
}

