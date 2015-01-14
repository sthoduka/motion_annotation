/* video_interaction.cpp
 *
 * Copyright (C) 2014 Santosh Thoduka
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <motion_annotation/video_interaction.h>

VideoInteraction::VideoInteraction(int skip_frames) : frame_number_(0), skip_frames_(skip_frames)
{    
}

VideoInteraction::~VideoInteraction()
{
}

bool VideoInteraction::open(const bfs::path &video_filepath)
{
    capture_ = cv::VideoCapture(video_filepath.string().c_str());
    return capture_.isOpened();
}

void VideoInteraction::skip(int num_frames)
{
    cv::Mat frame;
    for (int i = 0; i < num_frames; i++)
    {
        capture_ >> frame;
        frame_number_++;
    }
}

int VideoInteraction::getCurrentFrameNumber()
{
    return frame_number_;
}

cv::Mat VideoInteraction::getPreviousFrame()
{
    return previous_frame_;
}

cv::Mat VideoInteraction::getCurrentFrame()
{
    return current_frame_;
}

bool VideoInteraction::getFrame(cv::Mat &frame)
{
    previous_frame_ = current_frame_.clone();
    capture_ >> frame;
    if (!frame.empty())
    {
        frame_number_++;
        current_frame_ = frame;
    }
    skip(skip_frames_);
    return !frame.empty();
}

