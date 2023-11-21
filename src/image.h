#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>


using namespace cv;
using namespace std;

class Image
{
public:
    Image(string path);
    void read(string path);
    Mat convertToGray(string path);
    void recognizeFaces(Mat grayImg);
    void save_image(Mat new_image);
    void clear_dir(string &path);
private:
    Mat main_image;
    vector<Rect>list_faces;
};