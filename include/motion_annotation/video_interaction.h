#ifndef VIDEO_INTERACTION_H_
#define VIDEO_INTERACTION_H_

#include <opencv2/opencv.hpp>
#include <boost/filesystem.hpp>

namespace bfs = boost::filesystem;
class VideoInteraction
{
    public:
        VideoInteraction();
        virtual ~VideoInteraction();

        bool open(const bfs::path &video_filepath);

        void skip(int num_frames);

        int getCurrentFrameNumber();

        bool getFrame(cv::Mat &frame);

        cv::Mat getPreviousFrame();
        cv::Mat getCurrentFrame();


    private:

        int frame_number_;
        cv::VideoCapture capture_;
        cv::Mat previous_frame_;
        cv::Mat current_frame_;
};
#endif
