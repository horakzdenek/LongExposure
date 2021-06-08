#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"
#include "MojeCV.hpp"



using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    char key;
    if(!(argc >= 2)) return EXIT_FAILURE;
    string filename = argv[1];

    VideoCapture cap(filename);
    if(!cap.isOpened())
        return -1;

    Mat frame;
    cap >> frame; // obnova framebufferu
    int frame_count = cap.get(CAP_PROP_FRAME_COUNT);
    int iterace = 0;

    MOJECV::preview nahled;
    nahled.hint = "ESC = Save actual frame";
    nahled.frame_count = frame_count;
    MOJECV::sensor s(frame);

    for(;;)
    {
        cap >> frame;
        if(frame.empty())
        {
            break;
        }


        frame.convertTo(frame,CV_32FC3); // ve vyšších verzích to není potřeba
        s.expose(frame);
        s.iterace = iterace;

        nahled.frame = s.Output();
        nahled.iterace = iterace;
        if(iterace == frame_count-5)
        {
            imwrite("result.jpg",s.Output());
        }



        imshow("nahled",nahled.nahled());
        key = waitKeyEx(1);
        if(key == 27)
        {
            imwrite("result.jpg",s.Output());
            break;
        }
        iterace++;
    }

    return 0;
}
