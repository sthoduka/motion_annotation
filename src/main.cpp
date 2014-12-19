#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <motion_annotation/video_interaction.h>
#include <motion_annotation/motion_logger.h>
#include <motion_annotation/contour_selection.h>
#include <iostream>


int main(int argc, char** argv)
{
    std::string video_filepath = std::string(argv[1]);
    std::string log_filepath = std::string(argv[2]);

    VideoInteraction vi;
    vi.open(video_filepath);   
    MotionLogger ml(log_filepath);
    ContourSelection cs;

    char key;
    cv::Mat frame;
    bool frame_exists = false;
    frame_exists = vi.getFrame(frame);
    if (frame_exists)
    {
        cv::imshow("Frame Display", frame);
        cv::waitKey(30);
    }
    key = cv::waitKey(0);
    while(frame_exists)
    {
        if (key == 'x')
        {
            break;
        }
        if (key == 'y')
        {
            int contour_id = 0;
            do
            {
                std::vector<cv::Point> points;
                cs.selectContour(frame, points);
                ml.writeContour(points, vi.getCurrentFrameNumber(), contour_id);
                cv::imshow("Frame Display", frame);
                cv::waitKey(1);
                contour_id++;
                key = cv::waitKey(0);
            } while (key == 'c');
            frame_exists = vi.getFrame(frame);
            if (frame_exists)
            {
                cv::imshow("Frame Display", frame);
                cv::waitKey(1);
            }
            key = cv::waitKey(0);
        }
        else
        {
            frame_exists = vi.getFrame(frame);
            if (frame_exists)
            {
                cv::imshow("Frame Display", frame);
                cv::waitKey(1);
            }
            key = cv::waitKey(0);
            continue;
        }
    }
}
