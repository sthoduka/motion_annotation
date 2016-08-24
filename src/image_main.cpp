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
    std::string input_directory;
    if (argc < 2)
    {
        std::cout << "specify input directory" << std::endl;
        return 1;
    }
    input_directory = std::string(argv[1]);

    if (!bfs::exists(input_directory) || !bfs::is_directory(input_directory))
    {
        std::cerr << "directory does not exist: " << input_directory << std::endl;
        return 1;
    }


    std::set<std::string> sorted_images;
    bfs::directory_iterator end;
    bfs::path image_directory = input_directory;
    image_directory /= "images";
    for (bfs::directory_iterator iter(image_directory); iter != end; ++iter)
    {
        if (!bfs::is_directory(*iter))
        {
            sorted_images.insert(iter->path().string());
        }
    }

    std::string log_filepath = std::string(argv[2]);

    int skip_frames = 0;
    if (argc > 3)
    {
        skip_frames = std::stoi(argv[3]);
    }

    MotionLogger ml(log_filepath);
    BoxSelection bs;

    char key;
    int frame_number = 0;
    cv::Mat im;
    std::set<std::string>::iterator iter = sorted_images.begin();
    im = cv::imread(*iter, CV_LOAD_IMAGE_COLOR);
    frame_number++;
    cv::Mat previous_frame;
    im.copyTo(previous_frame);
    while(iter != sorted_images.end())
    {
        std::cout << "Showing frame: " << frame_number << std::endl;
        ++iter;
        im = cv::imread(*iter, CV_LOAD_IMAGE_COLOR);
        if (im.empty())
        {
            std::cout << "done" << std::endl;
            exit(0);
        }
        cv::imshow("Frame Display", im);
        cv::moveWindow("Frame Display", 20, 20);
        key = cv::waitKey(0);
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
                bs.selectBox(im, previous_frame, top_left, bottom_right);
                if (top_left.x != bottom_right.x && top_left.y != bottom_right.y)
                    ml.writeBoundingBox(top_left, bottom_right, frame_number, contour_id);
                cv::rectangle(im, top_left, bottom_right, cv::Scalar(0,0,255), 2,8,0);
                cv::imshow("Frame Display", im);
                cv::moveWindow("Frame Display", 20, 20);
                cv::waitKey(1);
                contour_id++;
                key = cv::waitKey(0);
            } while (key == 'c');
        }
        if (key == '1' || key == '2')
        {
            do
            {
                if (key == '1')
                {
                    cv::imshow("Frame Display" , previous_frame);
                    key = cv::waitKey(0);
                }
                else if (key == '2')
                {
                    cv::imshow("Frame Display" , im);
                    key = cv::waitKey(0);
                }
                else if (key == 'y')
                {
                    cv::imshow("Frame Display" , im);
                    int contour_id = 0;
                    do
                    {
                        cv::Point top_left;
                        cv::Point bottom_right;
                        bs.selectBox(im, previous_frame, top_left, bottom_right);
                        if (top_left.x != bottom_right.x && top_left.y != bottom_right.y)
                            ml.writeBoundingBox(top_left, bottom_right, frame_number, contour_id);
                        cv::rectangle(im, top_left, bottom_right, cv::Scalar(0,0,255), 2,8,0);
                        cv::imshow("Frame Display", im);
                        cv::moveWindow("Frame Display", 20, 20);
                        cv::waitKey(1);
                        contour_id++;
                        key = cv::waitKey(0);
                    } while (key == 'c');
                }
            } while (key == '1' || key == '2' || key == 'y');
        }
        im.copyTo(previous_frame);
        frame_number++;
    }
}
