/* contour_selection.cpp
 *
 * Copyright (C) 2014 Santosh Thoduka
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <motion_annotation/contour_selection.h>
#include <iostream>


ContourSelection::ContourSelection() : answer_received_(false), is_satisfied_(false)
{
}

ContourSelection::~ContourSelection()
{
}

void ContourSelection::selectContour(cv::Mat &frame, const cv::Mat &previous_frame, std::vector<cv::Point> &points)
{
    cv::imshow("Contour Selection", frame);
    cv::setMouseCallback("Contour Selection", mouseCallback, this);

    while (!is_satisfied_)
    {        
        start_ = false;
        points_.clear();
        frame.copyTo(frame_);
        cv::imshow("Contour Selection", frame_);
        cv::waitKey(1);

        char key;
        while ( (key = cv::waitKey(0)) != 'x')
        {
            std::cout << "Press 'x' to exit" << key << std::endl;
            if (key == '1')
            {
                std::cout << "showing current " << std::endl;
                cv::imshow("Contour Selection", frame_);
            }
            else if (key == '2')
            {
                std::cout << "showing previous " << std::endl;
                cv::imshow("Contour Selection", previous_frame);
            }
        }   
        
        if (points_.size() > 1)
        {
            cv::line(frame_, points_.back(), points_[0], cv::Scalar(0, 0, 255));            
            cv::imshow("Contour Selection", frame_);
            cv::waitKey(1);
        }

        if ((key = cv::waitKey(0)) == 'y')break;
        else continue;
    }
    cv::destroyWindow("Contour Selection");
    cv::destroyWindow("Instructions");
    frame_.copyTo(frame);
    points = points_;
    points_.clear();        
}


void ContourSelection::mouseCallback(int event, int x, int y, int flags, void *param)
{
    ContourSelection *this_obj = static_cast<ContourSelection*>(param);
    this_obj->doMouseCallback(event, x, y, flags);
}

void ContourSelection::dialogMouseCallback(int event, int x, int y, int flags, void *param)
{
    ContourSelection *this_obj = static_cast<ContourSelection*>(param);
    this_obj->doDialogMouseCallback(event, x, y, flags);
}

void ContourSelection::doDialogMouseCallback(int event, int x, int y, int flags)
{
    if (event == CV_EVENT_LBUTTONDOWN)
    {
        if (!answer_received_)
        {
            if (x > 10 && x < 100 && y > 30 && y < 45)
            {
                is_satisfied_ = true; 
                answer_received_ = true;
            }
            if (x > 150 && x < 240 && y > 30 && y < 45)
            {
                is_satisfied_ = false;
                answer_received_ = true;
            }
        }
    }
}
void ContourSelection::doMouseCallback(int event, int x, int y, int flags)
{
//    if (event == CV_EVENT_LBUTTONDOWN)
    if (event == CV_EVENT_MOUSEMOVE && start_)
    {
        points_.push_back(cv::Point(x, y));
        if (points_.size() > 1)
        {
            cv::line(frame_, points_.back(), points_[points_.size() - 2], cv::Scalar(0, 0, 255));            
            cv::imshow("Contour Selection", frame_);
            cv::waitKey(1);
        }
    }
    if (!start_ && event == CV_EVENT_LBUTTONDOWN)
    {
        points_.push_back(cv::Point(x, y));
        if (points_.size() > 1)
        {
            cv::line(frame_, points_.back(), points_[points_.size() - 2], cv::Scalar(0, 0, 255));            
            cv::imshow("Contour Selection", frame_);
            cv::waitKey(1);
        }
        start_ = true;
    }
    else if (start_  && event == CV_EVENT_LBUTTONDOWN)
    {
        start_ = false;
    }
}

void ContourSelection::setDialogText(const std::string &text, const std::string &option1, const std::string &option2)
{
    dialog_ = cv::Mat::zeros(50,350,CV_8UC3);
    cv::putText(dialog_, text, cv::Point(5,25), CV_FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,0,255),1,8,false);
    if (!option1.empty() && !option2.empty())
    {
        cv::rectangle(dialog_, cv::Point(10,30), cv::Point(100,45), cv::Scalar(0,0,255),1);
        cv::rectangle(dialog_, cv::Point(150,30), cv::Point(240,45), cv::Scalar(0,0,255),1);
        cv::putText(dialog_, option1, cv::Point(30,40), CV_FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,0,255),1,8,false);
        cv::putText(dialog_, option2, cv::Point(170,40), CV_FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,0,255),1,8,false);
    }
    cv::imshow("Instructions", dialog_);
    cv::waitKey(1);
    if (!option1.empty() && !option2.empty())
    {
        cv::setMouseCallback("Instructions", dialogMouseCallback, this);
    }
}
