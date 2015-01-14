/* motion_logger.h
 *
 * Copyright (C) 2014 Santosh Thoduka
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

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
        void writeBoundingBox(const cv::Rect &rect, int frame_number, int contour_id);
        void writeBoundingBox(const cv::Point &top_left, const cv::Point &bottom_right, int frame_number, int contour_id);

    private:
        std::ofstream file_out_;
};
#endif
