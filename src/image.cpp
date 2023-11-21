#include "image.h"
#include <ostream>
#include <filesystem>

Image::Image(string path)
{
    main_image = imread(path, IMREAD_COLOR);
}

void Image::read(string path)
{
    Mat img = imread(path, IMREAD_COLOR);
    main_image = img;
    if(img.empty())
    {
        cout << "Image is empty, cant open" << endl;
    }
    imshow("Image",img);
    char quit_key = waitKey(0);
}

Mat Image::convertToGray(string path)
{
    Mat curr_img = imread(path, IMREAD_COLOR);
    Mat gray_img;
    cvtColor(curr_img, gray_img,  COLOR_BGR2GRAY);
    // imshow("gray image", gray_img);
    // waitKey(0);
    return gray_img;
}

void Image::recognizeFaces(Mat grayImg)
{
    Mat img = main_image;
    CascadeClassifier faceCascade;
    if(!faceCascade.load("/usr/local/share/opencv4/haarcascades/haarcascade_frontalface_default.xml"))
    {
        cout << "Cant load a face cascade file" << endl;
    }
    vector<Rect>faces;//        for first image - 1.1,2 ;  second - 1.1,7, 50/50; third - 1.1,20
    faceCascade.detectMultiScale(grayImg, faces, 1.1, 20, 0, Size(50,50)); //2 - eto sosedi. 1.3 - scale factor

    for(const auto &face : faces)
    {
        list_faces.push_back(face);
        rectangle(img, face, Scalar(255,0,255), 2);
    }
    save_image(main_image);
    imshow("Faces on image", img);
    waitKey(0);
}

void Image::clear_dir(string &path) 
{
    for(const auto &it : filesystem::directory_iterator(path))
    {
        if (filesystem::is_regular_file(it)) 
        {
            filesystem::remove(it.path());
        }
    }
}

void Image::save_image(Mat new_image)
{
    string filename = "img_3";
    imwrite("../detect_faces/" + filename + ".jpg",new_image);
    int counter = 1;
    // check if dirs is exist - delete all from this dir else : create new dir
    string dir_path = "../detect_faces/" + filename;
    filesystem::path curr_dir{dir_path};
    bool dir_exist = filesystem::is_directory(curr_dir);
    if(dir_exist)
        clear_dir(dir_path);
    else
        filesystem::create_directory("../detect_faces/" + filename);

    for(const auto &it : list_faces)
    {
        Mat face_part = new_image(it);
        ostringstream os; 
        os << "../detect_faces/" << filename << "/face_" << counter << ".jpg";
        imwrite(os.str(), face_part);
        counter++;
    }
}

