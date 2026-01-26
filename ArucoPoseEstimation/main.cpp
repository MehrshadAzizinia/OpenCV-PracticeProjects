#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <iostream>

static void makeApproxCameraMatrix(int w, int h, cv::Mat &K, cv::Mat &dist){
    // estmating camera intrinsic matrix, will work on proper calibration later

    double fx = 0.9 * w;
    double fy = 0.9 * h;
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

    cv::VideoCapture cap(0, cv::CAP_AVFOUNDATION);

    if(!cap.isOpened()){
        std::cout << "Unable to start camera\n";
        return 1;
    }

    // Set camera properties explicitly
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

   

    auto dict = cv::aruco::getPredefinedDictionary(dictId);
    cv::aruco::DetectorParameters params; 
    cv::aruco::ArucoDetector detector(dict, params);

    cv::Mat frame;

    // Give camera time to warm up
    std::cout << "Initializing camera...\n";
    for(int i = 0; i < 30; i++){
        cap >> frame;
        if(!frame.empty()) break;
        cv::waitKey(100); // wait 100ms between attempts
    }

    if(frame.empty()){
        std::cout << "Unable to read frame after initialization\n";
        return 1;
    }

    int w = frame.cols;
    int h = frame.rows;

    

    cv::Mat K, dist;
    makeApproxCameraMatrix(w, h, K, dist);

    

    while(true){

        cap >> frame;
        if(frame.empty()) break;
        
        

    

        std::vector<int> ids;
        std::vector<std::vector<cv::Point2f>> corners;
        detector.detectMarkers(frame, corners, ids);

        if(!ids.empty()){

            cv::aruco::drawDetectedMarkers(frame, corners, ids);

            std::vector<cv::Vec3d> rvecs, tvecs;
            cv::aruco::estimatePoseSingleMarkers(corners, markerLength, K, dist, rvecs, tvecs);

            for(int i = 0; i < ids.size(); i++){

                cv::drawFrameAxes(frame, K, dist, rvecs[i], tvecs[i], markerLength * 0.5f );

                double x = tvecs[i][0], y = tvecs[i][1], z = tvecs[i][2];
                std::cout << "ID " << ids[i]
                          << "  tvec(m): [" << x << ", " << y << ", " << z << "]"
                          << "  dist~ " << std::sqrt(x*x + y*y + z*z) << " m\n";

            }

        }
        cv::imshow("aruco Pose", frame);
        int key = cv::waitKey(1);
        if (key == 27 || key == 'q') break; 


    }

    return 0;
}

