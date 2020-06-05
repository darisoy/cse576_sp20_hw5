#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>

#include "image.h"

using namespace std;

// HW0 #3
// const Image& im: input image
// return the corresponding grayscale image
Image rgb_to_grayscale(const Image& im)
{
  assert(im.c == 3); // only accept RGB images
  Image gray(im.w,im.h,1); // create a new grayscale image (note: 1 channel)
  
  for (int i = 0; i < im.w; i++)
    for (int j = 0; j < im.h; j++)
    {
      float r = im(i, j, 0);
      float g = im(i, j, 1);
      float b = im(i, j, 2);
      gray(i, j, 0) = 0.299*r + 0.587*g + 0.114*b;
    }

  return gray;
}

// Example function that changes the color of a grayscale image
Image grayscale_to_rgb(const Image& im, float r, float g, float b)
{
  assert(im.c == 1);
  Image rgb(im.w,im.h,3);
  
  for(int q2=0;q2<im.h;q2++)for(int q1=0;q1<im.w;q1++)
  {
    rgb(q1,q2,0)=r*im(q1,q2);
    rgb(q1,q2,1)=g*im(q1,q2);
    rgb(q1,q2,2)=b*im(q1,q2);
  }
  return rgb;
}

// HW0 #4
// Image& im: input image to be modified in-place
// int c: which channel to shift
// float v: how much to shift
void shift_image(Image& im, int c, float v)
{
  assert(c>=0 && c<im.c); // needs to be a valid channel
  for (int w = 0; w < im.w; w++)
    for (int h = 0; h < im.h; h++)
      im(w, h, c) += v;
}

// HW0 #8
// Image& im: input image to be modified in-place
// int c: which channel to scale
// float v: how much to scale
void scale_image(Image& im, int c, float v)
{
  assert(c>=0 && c<im.c); // needs to be a valid channel
  for (int w = 0; w < im.w; w++)
    for (int h = 0; h < im.h; h++)
      im(w, h, c) *= v;
}

// HW0 #5
// Image& im: input image to be modified in-place
void clamp_image(Image& im)
{
  for (int c = 0; c < im.c; c++)
    for (int w = 0; w < im.w; w++)
      for (int h = 0; h < im.h; h++)
      {
        float newVal = im(w, h, c);
        if (newVal > 1)
          newVal = 1;
        else if (newVal < 0)
          newVal = 0;
        im(w, h, c) = newVal;
      }
}

// These might be handy
float max(float a, float b, float c)
{
  return max({a,b,c});
}

float min(float a, float b, float c)
{
  return min({a,b,c});
}

// HW0 #6
// Image& im: input image to be modified in-place
void rgb_to_hsv(Image& im)
{
  assert(im.c==3 && "only works for 3-channels images");
  
  for (int w = 0; w < im.w; w++)
    for (int h = 0; h < im.h; h++)
    {
      float R = im(w, h, 0);
      float G = im(w, h, 1);
      float B = im(w, h, 2);
      float V = max(R,G,B);
      float C = V - min(R,G,B);
      float S;
      if (V == 0)
        S = 0;
      else
        S = C / V;
      
      float Hp;
      if (C == 0)
        Hp = 0;
      else if (V == R)
        Hp = (G-B)/C;
      else if (V == G)
        Hp = ((B-R)/C) + 2;
      else if (V == B)
        Hp = ((R-G)/C) + 4;

      float H;
      if (Hp < 0)
        H = (Hp/6) + 1;
      else
        H = (Hp/6);

      im(w, h, 0) = H;
      im(w, h, 1) = S;
      im(w, h, 2) = V;
    }
}

// HW0 #7
// Image& im: input image to be modified in-place
void hsv_to_rgb(Image& im)
{
  assert(im.c==3 && "only works for 3-channels images");
  
  for (int w = 0; w < im.w; w++)
    for (int h = 0; h < im.h; h++)
    {
      float H = im(w, h, 0);
      float S = im(w, h, 1);
      float V = im(w, h, 2);
      float C = V * S;
      float X = C * (1.0 - abs(fmod(6.0*H, 2.0) - 1.0));
      float m = V - C;

      float Rp, Gp, Bp;
      if (H >= 0 && H < (1.0/6.0)) 
      {
        Rp = C;
        Gp = X;
        Bp = 0;
      } 
      else if (H >= (1.0/6.0) && H < (2.0/6.0)) 
      {
        Rp = X;
        Gp = C;
        Bp = 0;
      } 
      else if (H >= (2.0/6.0) && H < (3.0/6.0)) 
      {
        Rp = 0;
        Gp = C;
        Bp = X;
      } 
      else if (H >= (3.0/6.0) && H < (4.0/6.0)) 
      {
        Rp = 0;
        Gp = X;
        Bp = C;
      } 
      else if (H >= (4.0/6.0) && H < (5.0/6.0)) 
      {
        Rp = X;
        Gp = 0;
        Bp = C;
      } 
      else if (H >= (5.0/6.0) && H < 1) 
      {
        Rp = C;
        Gp = 0;
        Bp = X;
      }
      
      im(w, h, 0) = Rp + m;
      im(w, h, 1) = Gp + m;
      im(w, h, 2) = Bp + m;
    }
  
}

float rgb_to_xyz_helper(float value)
{
  return ((value > 0.04045) ? pow((value+0.055) / 1.055, 2.4) : (value/12.92)) * 100.0;
}

float xyz_to_lab_helper(float value)
{
  return (value > 0.008856) ? cbrt(value) : (7.787*value + 16.0 / 116.0);
}

// HW0 #9
// Image& im: input image to be modified in-place
void rgb_to_lch(Image& im)
{
  assert(im.c==3 && "only works for 3-channels images");
    
  for (int w = 0; w < im.w; w++)
    for (int h = 0; h < im.h; h++)
    {        
      //rgb to xyz
      float R = rgb_to_xyz_helper(im(w, h, 0));
		  float G = rgb_to_xyz_helper(im(w, h, 1));
		  float B = rgb_to_xyz_helper(im(w, h, 2));

		  float X = R*0.4124564 + G*0.3575761 + B*0.1804375;
		  float Y = R*0.2126729 + G*0.7151522 + B*0.0721750;
		  float Z = R*0.0193339 + G*0.1191920 + B*0.9503041;

      //xyz to lab
      X = xyz_to_lab_helper(X/95.047);
		  Y = xyz_to_lab_helper(Y/100.0);
		  Z = xyz_to_lab_helper(Z/108.883);

      float L = (116.0*Y) - 16.0;
      float a = 500.0 * (X-Y);
      float b = 200.0 * (Y-Z);

      //lab to lch
      float C = sqrt( pow(a, 2) + pow(b, 2));
      float H = atan2(b, a) * 180.0 / M_PI;
      if (H < 0)
        H += 360;

      im(w, h, 0) = L;
      im(w, h, 1) = C;
      im(w, h, 2) = H;
    }
}

float xyz_to_rgb_helper(float value)
{
  return ((value > 0.0031308) ? (1.055 * pow(value, 1.0/2.4) - 0.055) : (12.92*value));
}

// HW0 #9
// Image& im: input image to be modified in-place
void lch_to_rgb(Image& im)
{
  assert(im.c==3 && "only works for 3-channels images");
  
  for (int w = 0; w < im.w; w++)
    for (int h = 0; h < im.h; h++)
    {
      float L = im(w, h, 0);
      float C = im(w, h, 1);
      float H = im(w, h, 2);

      //lch to lab
      H = H * M_PI / 180.0;
      float a = cos(H) * C;
      float b = sin(H) * C;

      //lab to xyz
      float Y = (L + 16.0) / 116.0;
		  float X = a / 500.0 + Y;
		  float Z = Y - b / 200.0;

		  float X3 = pow(X, 3);
		  float Y3 = pow(Y, 3);
		  float Z3 = pow(Z, 3);

		  X = ((X3 > 0.008856) ? X3 : ((X - 16.0 / 116.0) / 7.787)) * 95.047;
		  Y = ((Y3 > 0.008856) ? Y3 : ((Y - 16.0 / 116.0) / 7.787)) * 100.0;
		  Z = ((Z3 > 0.008856) ? Z3 : ((Z - 16.0 / 116.0) / 7.787)) * 108.883;

      //xyz to rgb
      X = X / 100.0;
      Y = Y / 100.0;
      Z = Z / 100.0;

      float R = xyz_to_rgb_helper(X * 3.2404542 + Y * -1.5371385 + Z * -0.4985314);
      float G = xyz_to_rgb_helper(X * -0.9692660 + Y * 1.8760108 + Z * 0.0415560);
      float B = xyz_to_rgb_helper(X * 0.0556434 + Y * -0.2040259 + Z * 1.0572252);

      im(w, h, 0) = R;
      im(w, h, 1) = G;
      im(w, h, 2) = B;
    }
}

// Implementation of member functions
void Image::clamp(void) { clamp_image(*this); }
void Image::shift(int c, float v) { shift_image(*this,c,v); }
void Image::scale(int c, float v) { scale_image(*this,c,v); }

void Image::HSVtoRGB(void) { hsv_to_rgb(*this); }
void Image::RGBtoHSV(void) { rgb_to_hsv(*this); }
void Image::LCHtoRGB(void) { lch_to_rgb(*this); }
void Image::RGBtoLCH(void) { rgb_to_lch(*this); }
