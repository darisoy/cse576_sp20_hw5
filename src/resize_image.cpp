#include <cmath>
#include "image.h"

using namespace std;

// HW1 #1
// float x,y: inexact coordinates
// int c: channel
// returns the nearest neibor to pixel (x,y,c)
float Image::pixel_nearest(float x, float y, int c) const
{
  int intx = round(x);
  int inty = round(y);
  return clamped_pixel(intx, inty, c);
}

// HW1 #1
// float x,y: inexact coordinates
// int c: channel
// returns the bilinearly interpolated pixel (x,y,c)
float Image::pixel_bilinear(float x, float y, int c) const
{
  int x1 = floor(x);
  int x2 = x1 + 1;
  int y1 = floor(y);
  int y2 = y1 + 1;
  float V1 = clamped_pixel(x1, y2, c);
  float V2 = clamped_pixel(x2, y2, c);
  float V3 = clamped_pixel(x1, y1, c);
  float V4 = clamped_pixel(x2, y1, c);
  float A1 = (x2-x) * (y-y1);
  float A2 = (x-x1) * (y-y1);
  float A3 = (x2-x) * (y2-y);
  float A4 = (x-x1) * (y2-y);
  return V1*A1 + V2*A2 + V3*A3 + V4*A4;
}

// HW1 #1
// int w,h: size of new image
// const Image& im: input image
// return new Image of size (w,h,im.c)
Image nearest_resize(const Image& im, int w, int h)
{
  Image ret = Image(w, h, im.c);
  float w_scale = im.w * 1.0 / w;
  float h_scale = im.h * 1.0 / h;
  for (int i = 0; i < w; i++)
    for (int j = 0; j < h; j++)
      for (int k = 0; k < im.c; k++)
      {
        float x = -0.5 + w_scale*(i+0.5);
        float y = -0.5 + h_scale*(j+0.5);
        ret(i, j, k) = im.pixel_nearest(x, y, k);
      }
  return ret;
}

// HW1 #1
// int w,h: size of new image
// const Image& im: input image
// return new Image of size (w,h,im.c)
Image bilinear_resize(const Image& im, int w, int h)
{
  Image ret = Image(w, h, im.c);
  float w_scale = im.w * 1.0 / w;
  float h_scale = im.h * 1.0 / h;
  for (int i = 0; i < w; i++)
    for (int j = 0; j < h; j++)
      for (int k = 0; k < im.c; k++)
      {
        float x = -0.5 + w_scale*(i+0.5);
        float y = -0.5 + h_scale*(j+0.5);
        ret(i, j, k) = im.pixel_bilinear(x, y, k);
      }
  return ret;
}