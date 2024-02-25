#include <opencv2/opencv.hpp>

int main() {
    // Read the image
    cv::Mat image = cv::imread("img.jpg");

    if (image.empty()) {
        std::cerr << "Error: Unable to load image" << std::endl;
        return -1;
    }
    Point p1(0, 0), p2(100, 0); 
    Point p3(200, 0), p4(500, 500); 
    int thickness = 2; 
  
    // Line drawn using 8 connected: Bresenham algorithm 
    line(image, p1, p4, Scalar(255, 0, 0), 
         thickness, LINE_8);     // Display the image in a window
    cv::namedWindow("Image", cv::WINDOW_NORMAL);
    cv::imshow("Image", image);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}

