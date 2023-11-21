#include <iostream>
#include "image.h"


int main(int argc, char*argv[])
{
    string path = argv[1];
    Image *img = new Image(path);
    // img->read(x);
    Mat gray_img = img->convertToGray(path);
    img->recognizeFaces(gray_img);
    
    return 0;
}