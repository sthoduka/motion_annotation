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
#include <fstream>
#include <iostream>

namespace bfs = boost::filesystem;

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

    std::ifstream file_in_(log_filepath.c_str());
    std::string frame_number_str, contour_id_str, tl_x_str, tl_y_str, br_x_str, br_y_str;
    file_in_ >> frame_number_str >> contour_id_str >> tl_x_str >> tl_y_str >> br_x_str >> br_y_str;
    int frame_number = std::stoi(frame_number_str.substr(0, frame_number_str.size()-1));
    int tl_x = std::stoi(tl_x_str.substr(0, tl_x_str.size()-1));
    int tl_y = std::stoi(tl_y_str.substr(0, tl_y_str.size()-1));
    int br_x = std::stoi(br_x_str.substr(0, br_x_str.size()-1));
    int br_y = std::stoi(br_y_str);

    char key;
    int display_frame_number = 0;
    cv::Mat im;
    std::set<std::string>::iterator iter = sorted_images.begin();
    im = cv::imread(*iter, CV_LOAD_IMAGE_COLOR);
    display_frame_number++;
    while(iter != sorted_images.end())
    {
        std::cout << "Showing frame: " << display_frame_number << std::endl;
        ++iter;
        im = cv::imread(*iter, CV_LOAD_IMAGE_COLOR);
        if (im.empty())
        {
            std::cout << "done" << std::endl;
            exit(0);
        }
        if (frame_number < display_frame_number)
        {
            if (!file_in_.eof())
            {
                file_in_ >> frame_number_str >> contour_id_str >> tl_x_str >> tl_y_str >> br_x_str >> br_y_str;
                frame_number = std::stoi(frame_number_str.substr(0, frame_number_str.size()-1));
                tl_x = std::stoi(tl_x_str.substr(0, tl_x_str.size()-1));
                tl_y = std::stoi(tl_y_str.substr(0, tl_y_str.size()-1));
                br_x = std::stoi(br_x_str.substr(0, br_x_str.size()-1));
                br_y = std::stoi(br_y_str);
            }
        }

        while (frame_number == display_frame_number)
        {
            cv::Point top_left(tl_x, tl_y);
            cv::Point bottom_right(br_x, br_y);
            cv::rectangle(im, top_left, bottom_right, cv::Scalar(0,0,255), 2,8,0);

            if (!file_in_.eof())
            {
                file_in_ >> frame_number_str >> contour_id_str >> tl_x_str >> tl_y_str >> br_x_str >> br_y_str;
                frame_number = std::stoi(frame_number_str.substr(0, frame_number_str.size()-1));
                tl_x = std::stoi(tl_x_str.substr(0, tl_x_str.size()-1));
                tl_y = std::stoi(tl_y_str.substr(0, tl_y_str.size()-1));
                br_x = std::stoi(br_x_str.substr(0, br_x_str.size()-1));
                br_y = std::stoi(br_y_str);
            }
            else
            {
                frame_number++;
                break;
            }

        }

        cv::imshow("Frame Display", im);
        cv::moveWindow("Frame Display", 20, 20);
        key = cv::waitKey(0);
        if (key == 'x')
        {
            break;
        }
        display_frame_number++;
    }
}
