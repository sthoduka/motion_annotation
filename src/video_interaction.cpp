#include <motion_annotation/video_interaction.h>

VideoInteraction::VideoInteraction() : frame_number_(0)
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
    return !frame.empty();
}

