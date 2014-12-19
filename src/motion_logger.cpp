#include <motion_annotation/motion_logger.h>

MotionLogger::MotionLogger(const bfs::path &log_filepath) : file_out_(log_filepath.string().c_str())
{

}

MotionLogger::~MotionLogger()
{
    file_out_.close();
}

void MotionLogger::writeContour(const std::vector<cv::Point> &points, int frame_number, int contour_id)
{
    file_out_ << frame_number << ", " << contour_id;
    for (int i = 0; i < points.size(); i++)
    {
        cv::Point p = points.at(i);
        file_out_ <<", " << p.x << ", " << p.y;
    }
    file_out_ << std::endl;
}
