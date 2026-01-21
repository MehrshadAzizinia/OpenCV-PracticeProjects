#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <iostream>

int main(){

    int dictId = cv::aruco::DICT_4X4_50;
    int markerId = 0;
    int markerSize = 600;

    auto dict = cv::aruco::getPredefinedDictionary(dictId);
    cv::Mat marker;

    cv::aruco::generateImageMarker(dict, markerId, markerSize ,marker,1);
    cv::imwrite("aruco_marker.png", marker);
    std::cout << "Marker has been created";

    return 0;


}