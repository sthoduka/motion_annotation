/* main.cpp
 *
 * Copyright (C) 2014 Santosh Thoduka
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <motion_annotation/video_interaction.h>
#include <motion_annotation/motion_logger.h>
#include <motion_annotation/box_selection.h>
#include <iostream>


int main(int argc, char** argv)
{
    std::string video_filepath = std::string(argv[1]);
    std::string log_filepath = std::string(argv[2]);
    
    int skip_frames = 0;
    if (argc > 3)
    {
        skip_frames = std::stoi(argv[3]); 
    }

    VideoInteraction vi(skip_frames);
    vi.open(video_filepath);   
    MotionLogger ml(log_filepath);
    BoxSelection bs;

    char key;
    cv::Mat frame;
    bool frame_exists = false;
    vi.getFrame(frame);
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
                cv::Point top_left;
                cv::Point bottom_right;
                bs.selectBox(frame, vi.getPreviousFrame(), top_left, bottom_right);
                if (top_left.x != bottom_right.x && top_left.y != bottom_right.y)
                    ml.writeBoundingBox(top_left, bottom_right, vi.getCurrentFrameNumber(), contour_id);
                cv::rectangle(frame, top_left, bottom_right, cv::Scalar(0,0,255), 2,8,0);
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
            std::cout << "Frame: " << vi.getCurrentFrameNumber() << std::endl;
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
