#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <cmath>
#include <assert.h>
#include "image.h"

#define M_PI 3.14159265358979323846

// HW1 #2.1
// Image& im: image to L1-normalize
void l1_normalize(Image& im)
{
  float imageSum = 0.0;
  for (int w = 0; w < im.w; w++)
    for (int h = 0; h < im.h; h++)
      for (int c = 0; c < im.c; c++)
        imageSum += im(w, h, c);

  for (int w = 0; w < im.w; w++)
    for (int h = 0; h < im.h; h++)
      for (int c = 0; c < im.c; c++)
      {
        if (imageSum == 0)
          im(w, h, c) = 1.0 / (im.w * im.h);
        else
          im(w, h, c) /= imageSum;
      }
}

// HW1 #2.1
// int w: size of filter
// returns the filter Image of size WxW
Image make_box_filter(int w)
{
  assert(w%2); // w needs to be odd
  Image im = Image(w, w, 1);
  for (int i = 0 ; i < w; i++)
    for (int j = 0 ; j < w; j++)
      im(i, j, 0) = 1.0;

  l1_normalize(im);
  return im;
}

// HW1 #2.2
// const Image&im: input image
// const Image& filter: filter to convolve with
// bool preserve: whether to preserve number of channels
// returns the convolved image
Image convolve_image(const Image& im, const Image& filter, bool preserve)
{
  assert(filter.c==1);
  int newc = 1;
  if (preserve)
    newc = im.c;
  Image ret = Image(im.w, im.h, newc);
  
  for (int w = 0; w < im.w; w++)
    for (int h = 0; h < im.h; h++)
    {
      float channelSum = 0;
      for (int c = 0; c < im.c; c++)
      {
        float q = 0;
        for (int f1 = 0; f1 < filter.w; f1++)
          for (int f2 = 0; f2 < filter.h; f2++)
          {
            int imX = w + f1 - (filter.w/2);
            int imY = h + f2 - (filter.h/2);
            q += filter.clamped_pixel(f1, f2, 0) * im.clamped_pixel(imX, imY, c);
          }
        if (preserve)
          ret(w, h, c) = q;
        else
          channelSum += q; 
      }
      if (!preserve)
        ret(w, h, 0) = channelSum;
    }
  return ret;
}

// HW1 #2.3
// returns basic 3x3 high-pass filter
Image make_highpass_filter()
{
  Image im = Image(3, 3, 1);
  im(0, 0, 0) = 0;
  im(0, 1, 0) = -1;
  im(0, 2, 0) = 0;
  im(1, 0, 0) = -1;
  im(1, 1, 0) = 4;
  im(1, 2, 0) = -1;
  im(2, 0, 0) = 0;
  im(2, 1, 0) = -1;
  im(2, 2, 0) = 0;
  return im;
}

// HW1 #2.3
// returns basic 3x3 sharpen filter
Image make_sharpen_filter()
{
  Image im = Image(3, 3, 1);
  im(0, 0, 0) = 0;
  im(0, 1, 0) = -1;
  im(0, 2, 0) = 0;
  im(1, 0, 0) = -1;
  im(1, 1, 0) = 5;
  im(1, 2, 0) = -1;
  im(2, 0, 0) = 0;
  im(2, 1, 0) = -1;
  im(2, 2, 0) = 0;
  return im;
}

// HW1 #2.3
// returns basic 3x3 emboss filter
Image make_emboss_filter()
{
  Image im = Image(3, 3, 1);
  im(0, 0, 0) = -2;
  im(0, 1, 0) = -1;
  im(0, 2, 0) = 0;
  im(1, 0, 0) = -1;
  im(1, 1, 0) = 1;
  im(1, 2, 0) = 1;
  im(2, 0, 0) = 0;
  im(2, 1, 0) = 1;
  im(2, 2, 0) = 2;
  return im;
}

// HW1 #2.4
// float sigma: sigma for the gaussian filter
// returns basic gaussian filter
Image make_gaussian_filter(float sigma)
{
  int dimension = round(6*sigma);
  if (dimension % 2 == 0)
    dimension++;
  Image im = Image(dimension, dimension, 1);

  float multiplier = 1.0 / (2.0*M_PI*pow(sigma, 2));
  for (int x = 0 ; x < dimension; x++)
    for (int y = 0 ; y < dimension; y++)
    {
      float newx = x - (dimension/2);
      float newy = y - (dimension/2);
      float exponent = -1.0 * (pow(newx, 2)+pow(newy, 2)) / (2*pow(sigma, 2));
      im(x, y, 0) = multiplier * exp(exponent);
    }   
  return im;
}

// HW1 #3
// const Image& a: input image
// const Image& b: input image
// returns their sum
Image add_image(const Image& a, const Image& b)
{
  assert(a.w==b.w && a.h==b.h && a.c==b.c); // assure images are the same size
  Image im = Image(a.w, a.h, a.c);
  for (int w = 0; w < im.w; w++)
    for (int h = 0; h < im.h; h++)
      for (int c = 0; c < im.c; c++)
        im(w, h, c) = a(w, h, c) + b(w, h, c);
  
  return im;
}

// HW1 #3
// const Image& a: input image
// const Image& b: input image
// returns their difference res=a-b
Image sub_image(const Image& a, const Image& b)
{
  assert(a.w==b.w && a.h==b.h && a.c==b.c); // assure images are the same size
  Image im = Image(a.w, a.h, a.c);
  for (int w = 0; w < im.w; w++)
    for (int h = 0; h < im.h; h++)
      for (int c = 0; c < im.c; c++)
        im(w, h, c) = a(w, h, c) - b(w, h, c);
  
  return im;
}

// HW1 #4.1
// returns basic GX filter
Image make_gx_filter()
{
  Image im = Image(3, 3, 1);
  im(0, 0, 0) = -1;
  im(0, 1, 0) = -2;
  im(0, 2, 0) = -1;
  im(1, 0, 0) = 0;
  im(1, 1, 0) = 0;
  im(1, 2, 0) = 0;
  im(2, 0, 0) = 1;
  im(2, 1, 0) = 2;
  im(2, 2, 0) = 1;
  return im;
}

// HW1 #4.1
// returns basic GY filter
Image make_gy_filter()
{
  Image im = Image(3, 3, 1);
  im(0, 0, 0) = -1;
  im(0, 1, 0) = 0;
  im(0, 2, 0) = 1;
  im(1, 0, 0) = -2;
  im(1, 1, 0) = 0;
  im(1, 2, 0) = 2;
  im(2, 0, 0) = -1;
  im(2, 1, 0) = 0;
  im(2, 2, 0) = 1;
  return im;
}

// HW1 #4.2
// Image& im: input image
void feature_normalize(Image& im)
{
  assert(im.w*im.h); // assure we have non-empty image

  for (int c = 0; c < im.c; c++)
  {
    float min = INFINITY;
    float max = -INFINITY;
    for (int w = 0; w < im.w; w++)
      for (int h = 0; h < im.h; h++)
      {
        float val = im(w, h, c);
        if (val < min)
          min = val;
        if (val > max)
          max = val;
      }

    float range = max - min;
    for (int w = 0; w < im.w; w++)
      for (int h = 0; h < im.h; h++)
      {
        if (range == 0)
          im(w, h, c) = 0;
        else
          im(w, h, c) = (im(w, h, c)-min) / range;
      }
  }
}

// Normalizes features across all channels
void feature_normalize_total(Image& im)
{
  assert(im.w*im.h*im.c); // assure we have non-empty image
  
  int nc=im.c;
  im.c=1;im.w*=nc;
  
  feature_normalize(im);
  
  im.w/=nc;im.c=nc;
  
}

// HW1 #4.3
// Image& im: input image
// return a pair of images of the same size
pair<Image,Image> sobel_image(const Image& im)
{
  Image Gx = convolve_image(im, make_gx_filter(), false);
  Image Gy = convolve_image(im, make_gy_filter(), false);
  Image mag = Image(im.w, im.h, 1);
  Image phase = Image(im.w, im.h, 1);
  for (int w = 0; w < im.w; w++)
    for (int h = 0; h < im.h; h++)
    {
      mag(w, h, 0) = sqrt(pow(Gx(w, h, 0), 2) + pow(Gy(w, h, 0), 2));
      phase(w, h, 0) = atan2(Gy(w, h, 0), Gx(w, h, 0));
    }
  return {mag, phase};
}

// HW1 #4.4
// const Image& im: input image
// returns the colorized Sobel image of the same size
Image colorize_sobel(const Image& im)
{
  Image ret = convolve_image(im, make_gaussian_filter(4), true);
  pair<Image, Image> sobel = sobel_image(ret);
  Image mag = sobel.first;
  Image phase = sobel.second;
  feature_normalize(mag);
  feature_normalize(phase);
  for (int w = 0; w < im.w; w++)
    for (int h = 0; h < im.h; h++)
    {
      ret(w, h, 0) = phase(w, h, 0); //H
      ret(w, h, 1) = mag(w, h, 0);   //S
      ret(w, h, 2) = mag(w, h, 0);   //V
    }
  hsv_to_rgb(ret);
  return ret;
}

// HW1 #4.5
// const Image& im: input image
// float sigma1,sigma2: the two sigmas for bilateral filter
// returns the result of applying bilateral filtering to im
Image bilateral_filter(const Image& im, float sigma1, float sigma2)
{
  Image ret = Image(im.w, im.h, im.c);

  //first gaussian values
  Image gaussian1 = make_gaussian_filter(sigma1);
  int k_size = round(6*sigma1);
  if (k_size % 2 == 0)
    k_size++;

  // calculate and apply kernel for each pixel in im
  for (int w = 0; w < im.w; w++)
    for (int h = 0; h < im.h; h++)
      for (int c = 0; c < im.c; c++) {
        //create kernel
        Image filter =  Image(k_size, k_size, 1);

        //calculate and set weights of kernel
        for (int i = 0; i < k_size; i++)
          for (int j = 0; j < k_size; j++)
          {
            float multiplier2 = 1.0 / (sqrt(2.0*M_PI) * sigma2);
            float difference = im.clamped_pixel(w, h, c) - im.clamped_pixel(w+i-(k_size/2), h+j-(k_size/2), c);
            float exponent2 = -1.0 * pow(difference, 2) / (2*pow(sigma2, 2));
            float gaussian2 = multiplier2 * exp(exponent2);

            filter(i, j, 0) = gaussian1(i, j, 0) * gaussian2;
          }
        l1_normalize(filter);

        //pixel convolved over kernel
        float pixel = 0;
        for (int i = 0; i < k_size; i++)
          for (int j = 0; j < k_size; j++)
            pixel += filter.clamped_pixel(i, j, 0) * im.clamped_pixel(w+i-(k_size/2), h+j-(k_size/2), c);
          
        //set the new pixel  
        ret(w, h, c) = pixel;
      }

  return ret;
}

// HELPER MEMBER FXNS
void Image::feature_normalize(void) { ::feature_normalize(*this); }
void Image::feature_normalize_total(void) { ::feature_normalize_total(*this); }
void Image::l1_normalize(void) { ::l1_normalize(*this); }

Image operator-(const Image& a, const Image& b) { return sub_image(a,b); }
Image operator+(const Image& a, const Image& b) { return add_image(a,b); }
