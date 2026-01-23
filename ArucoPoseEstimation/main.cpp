#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <iostream>

static void makeApproxCameraMatrix(int w, int h, cv::Mat &K, cv::Mat &dist){
    // estmating camera intrinsic matrix, will work on proper calibration later

    double fx = 0.9 * w;
    double fy = 0.9 * w;
    double cx = w/2.0;
    double cy = h/2.0;

    K = (cv::Mat_<double>(3,3) << fx, 0, cx, 
                                  0,  fy, cy, 
                                  0, 0, 1); 
    dist = cv::Mat::zeros(1, 5, CV_64F);

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
        
        std::vector<int> ids;
        std::vector<std::vector<cv::Point2f>> corners;

        cv::aruco::detectMarkers(frame, dict, corners, ids, params)
        




    }





    return 0;
}

