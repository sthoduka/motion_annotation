#ifndef CONTOUR_SELECTION_H_
#define CONTOUR_SELECTION_H_

#include <opencv2/opencv.hpp>

class ContourSelection
{
    public:
        ContourSelection();
        virtual ~ContourSelection();

        void selectContour(cv::Mat &frame, std::vector<cv::Point> &points);

        static void mouseCallback(int event, int x, int y, int flags, void *param);
        static void dialogMouseCallback(int event, int x, int y, int flags, void *param);

        void doMouseCallback(int event, int x, int y, int flags);
        void doDialogMouseCallback(int event, int x, int y, int flags);

    private:
        void setDialogText(const std::string &text, const std::string &option1 = std::string(), const std::string &option2 = std::string());

    private:
        cv::Mat dialog_;
        std::vector<cv::Point> points_;
        cv::Mat frame_;
        bool answer_received_;
        bool is_satisfied_;

};
#endif
