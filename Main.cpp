// Main.cpp

#include<opencv2/opencv.hpp>

#include<iostream>
#include<conio.h>     // may have to modify this line if not using Windows

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {

    // declare a VideoCapture object and attempt to open the video file
    cv::VideoCapture videoCapture;       
    videoCapture.open("input_vid1.mp4");
    //videoCapture.open("cars_passing_input.mp4");

    // if unable to open video file, show error message and exit program
    if (!videoCapture.isOpened()) {
        std::cout << "error reading video file" << "\n\n";
        _getch();                   // it may be necessary to change or remove this line if not using Windows
        return(0);
    }

    int intCodecType = static_cast<int>(videoCapture.get(CV_CAP_PROP_FOURCC));

    char charArrayCodecType[] = { (char)(intCodecType & 0XFF) , (char)((intCodecType & 0XFF00) >> 8),(char)((intCodecType & 0XFF0000) >> 16),(char)((intCodecType & 0XFF000000) >> 24), 0 };



    //cv::VideoWriter videoWriter("output_video.avi", videoCapture.get(CV_CAP_PROP_FOURCC), videoCapture.get(CV_CAP_PROP_FPS), cv::Size(videoCapture.get(CV_CAP_PROP_FRAME_WIDTH), videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT)));
    //cv::VideoWriter videoWriter("output_video.mp4", videoCapture.get(CV_CAP_PROP_FOURCC), videoCapture.get(CV_CAP_PROP_FPS), cv::Size(videoCapture.get(CV_CAP_PROP_FRAME_WIDTH), videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT)));
    cv::VideoWriter videoWriter("output_vid.mp4", CV_FOURCC('M','P','4','V'), videoCapture.get(CV_CAP_PROP_FPS), cv::Size(videoCapture.get(CV_CAP_PROP_FRAME_WIDTH), videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT)));
    //cv::VideoWriter videoWriter("output_video.avi", CV_FOURCC('X','V','I','D'), videoCapture.get(CV_CAP_PROP_FPS), cv::Size(videoCapture.get(CV_CAP_PROP_FRAME_WIDTH), videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT)));
    //cv::VideoWriter videoWriter("output_video.avi", CV_FOURCC('A', 'V', 'C', '1'), 25, cv::Size(videoCapture.get(CV_CAP_PROP_FRAME_WIDTH), videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT)));
    //cv::VideoWriter videoWriter("output_video.mp4", CV_FOURCC('m', 'p', '4', 'v'), videoCapture.get(CV_CAP_PROP_FPS), cv::Size(videoCapture.get(CV_CAP_PROP_FRAME_WIDTH), videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT)));
    //cv::VideoWriter videoWriter("output_video.mp4", CV_FOURCC('M', 'J', 'P', 'G'), videoCapture.get(CV_CAP_PROP_FPS), cv::Size(videoCapture.get(CV_CAP_PROP_FRAME_WIDTH), videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT)));
    //cv::VideoWriter videoWriter("output_video.avi", CV_FOURCC('M', 'J', 'P', 'G'), videoCapture.get(CV_CAP_PROP_FPS), cv::Size(videoCapture.get(CV_CAP_PROP_FRAME_WIDTH), videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT)));
   
    if (!videoWriter.isOpened()) {
        std::cout << "error instantiating VideoWriter" << "\n\n";
        _getch();                   // it may be necessary to change or remove this line if not using Windows
        return(0);
    }


    cv::Mat imgScene;
    videoCapture.read(imgScene);

    char chCheckForEscKey = 0;

    while (videoCapture.isOpened() && chCheckForEscKey != 27) {

        // show the current frame
        cv::imshow("imgScene", imgScene);

        /*
        // convert to grayscale
        cv::Mat imgGrayscale;
        cv::cvtColor(imgScene, imgGrayscale, CV_BGR2GRAY);

        // get an Otsu thresh value to use for Canny low/high params
        cv::Mat imgDummy;
        double otsuThreshVal = cv::threshold(imgGrayscale, imgDummy, 0.0, 255.0, CV_THRESH_BINARY | CV_THRESH_OTSU);

        // find canny edges
        cv::Mat imgCanny;
        cv::Canny(imgGrayscale, imgCanny, otsuThreshVal / 2.0, otsuThreshVal);
        cv::imshow("imgCanny", imgCanny);

        chCheckForEscKey = cv::waitKey(1);
        */

        cv::Mat imgOutput;
        cv::flip(imgScene, imgOutput, 1);
        cv::imshow("imgOutput", imgOutput);

        // write the Canny edge frame to the output video
        videoWriter.write(imgOutput);

        // if there is another frame get it, else show end of video message and bail
        if ((videoCapture.get(CV_CAP_PROP_POS_FRAMES) + 1) < videoCapture.get(CV_CAP_PROP_FRAME_COUNT)) {
            videoCapture.read(imgScene);
        }
        else {
            std::cout << "end of video\n";
            break;
        }

        chCheckForEscKey = cv::waitKey(1);

    }

    //if the user did not press esc (i.e. we reached the end of the video) hold the windows open to allow the "end of video" message to show
    if (chCheckForEscKey != 27) {
        cv::waitKey(0);
    }
    // note that if the user did press esc, we don't need to hold the windows open, we can simply let the program end which will close the windows

    videoCapture.release();
    videoWriter.release();

    return(0);
}














