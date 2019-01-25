#ifndef __GET_FACE_HPP__
#define __GET_FACE_HPP__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include <unistd.h>
#include <signal.h>
#include "mtcnn_utils.hpp"
//#include "mtcnn.hpp"
#include "face_align.hpp"
#include "feature_extractor.hpp"
#include "face_verify.hpp"
//#include "face_mem_store.hpp"

struct face_window
{
	face_box box;
	unsigned int face_id;
        unsigned int frame_seq;
	float center_x;
	float center_y;
	std::string name;
        char title[128];
};

void get_face_title(cv::Mat& frame,face_box& box,cv::Mat& frame1,face_box& box1,unsigned int frame_seq);


#endif
