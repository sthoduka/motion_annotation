#ifndef MOTION_LOGGER_H_
#define MOTION_LOGGER_H_

#include <fstream>
#include <opencv2/opencv.hpp>

#include <boost/filesystem.hpp>
namespace bfs = boost::filesystem;

class MotionLogger
{
    public:
        MotionLogger(const bfs::path &log_filepath);
        virtual ~MotionLogger();

        void writeContour(const std::vector<cv::Point> &points, int frame_number, int contour_id);

    private:
        std::ofstream file_out_;
};
#endif
