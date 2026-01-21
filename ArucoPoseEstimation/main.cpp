#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <iostream>

static void makeApproxCameraMatrix(){




}


int main() {
    int dictId = cv::aruco::DICT_4X4_50;
    float markerLength = 0.05f; //example for 5cm length, need to adjust after printing

    cv::VideoCapture cap(0);

    if(!cap.isOpened()){

        std::cout << "Unable to start camera\n";
        return 1;
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);

    auto dict = cv::aruco::getPredefinedDictionary(dictId);
    auto params = cv::aruco::DetectorParameters::create();

    cv::Mat frame;

    while(true){

        cap >> frame;
        if(frame.empty()) break;

        int w = frame.cols;
        int h = frame.rows;

        cv::Mat K, dist;

        makeApproxCameraMatrix(w, h, K, dist);

        




    }





    return 0;
}

