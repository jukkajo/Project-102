#include <pylon/PylonIncludes.h>
#include <opencv2/opencv.hpp> 
#include <iostream>
#include <string> 

#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc.hpp> 

#include <fstream>
// Namespaces.

using namespace cv;
using namespace cv::dnn;
using namespace Pylon;

int main()
{
    // PylonInitialize() is automatically called
    Pylon::PylonAutoInitTerm autoInitTerm;
    try
    {
        // Create an instant camera object with the first available camera
        CInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());
        std::cout << "Using device " << camera.GetDeviceInfo().GetModelName() << std::endl;

        // Open the camera
        camera.Open();

        // Continuous image acquiring
        camera.StartGrabbing(GrabStrategy_LatestImageOnly);

        // OpenCV image container
        cv::Mat image;

        // Window for displaying images
        //cv::namedWindow("CanNotBeEmptyItSeems:(", cv::WINDOW_NORMAL);

        // Main loop of logic
        while (true)
        {
            // Wait for an image and retrieve it. Timeout: 5000 ms
            CGrabResultPtr ptrGrabResult;
            camera.RetrieveResult(5000, ptrGrabResult, TimeoutHandling_ThrowException);

            // If image grabbed successfully
            if (ptrGrabResult->GrabSucceeded())
            {
                // Accessing image data buffer
                const uint8_t* pImageBuffer = static_cast<const uint8_t*>(ptrGrabResult->GetBuffer());

                // Create an OpenCV Mat from the image data
                int widthOrig = ptrGrabResult->GetWidth();
                int heightOrig = ptrGrabResult->GetHeight();
                image = cv::Mat(heightOrig, widthOrig, CV_8UC1, const_cast<uint8_t*>(pImageBuffer));

                // Resize factor for downscaling the image
                double resizeFactor = 0.5; 
                cv::resize(image, image, cv::Size(), resizeFactor, resizeFactor);

                int width = widthOrig * resizeFactor;
                int height = heightOrig * resizeFactor;

                // ------- Drawing cross-cursor to FOV center -------
                // Lets make padding as 30 percent of dimensions
                int xPadding = width * 0.3;
                int yPadding = height * 0.3;

                // Vertical vector
                Point p1(xPadding, (height / 2)), p2((width - xPadding), (height / 2));
                // Horizontal
                Point p3((width / 2), yPadding), p4((width / 2), (height - yPadding));

                // Line thickness adjusted based on resizing factor
                int thickness = static_cast<int>(1.0 / resizeFactor);

                // Line drawn using 8 connected 
                // Bresenham algorithm 
                line(image, p1, p2, Scalar(255, 0, 0), thickness, LINE_8);
                line(image, p3, p4, Scalar(255, 0, 0), thickness, LINE_8);
                // ---------------------------------------------------
                
                // Displaying the image(s) via OpenCV window
                std::string name = std::string(camera.GetDeviceInfo().GetModelName().c_str());
                cv::imshow(name, image);

                /* Check for user input to exit the loop
                   'Esc' to exit
                 */
                if (cv::waitKey(1) == 27)
                    break;
            }
            else
            {
                std::cout << "Error: " << std::hex << ptrGrabResult->GetErrorCode() << std::dec << " " << ptrGrabResult->GetErrorDescription() << std::endl;
            }
        }

        // Stop grabbing images
        camera.StopGrabbing();

        cv::destroyAllWindows();
    }
    catch (const GenericException& e)
    {
        std::cerr << "Exception: " << e.GetDescription() << std::endl;
    }

    return 0;
}

