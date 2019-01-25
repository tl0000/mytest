/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * License); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * AS IS BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * Copyright (c) 2018, Open AI Lab
 * Author: chunyinglv@openailab.com
 */
#include <string>
#include <sys/time.h>
#include "mtcnn.hpp"
#include "mtcnn_utils.hpp"
#include "common1.hpp"
#include "get_face.hpp"
#include "lightened_cnn.hpp"

//using namespace std;
int current_frame_count=0;
//extern feature_extractor *p_extractor;


int main(int argc, char** argv)
{
   const std::string root_path = get_root_path();
   std::string img_name = root_path + "examples/build/faceid/images/face1.jpg";
   std::string img_name1 = root_path + "examples/build/faceid/images/face2.jpg";
   std::string model_dir = root_path + "examples/build/faceid/models";
   std::string sv_name = root_path + "examples/build/faceid/out/result.jpg";

    if(init_tengine() < 0)
    {
        std::cout << " init tengine failed\n";
        return 1;
    }
    if(request_tengine_version("0.9") < 0)
    {
        std::cout << " request tengine version failed\n";
        return 1;
    }

    if(argc == 1)
    {
        std::cout << "[usage]: " << argv[0] << root_path << " <test.jpg>  <model_dir> [save_result.jpg] \n";
    }
    if(argc >= 2)
        img_name = argv[1];
    if(argc >= 3)
        model_dir = argv[2];
    if(argc >= 4)
        sv_name = argv[3];

    cv::Mat image = cv::imread(img_name);
    if(image.empty())
    {
        std::cerr << "cv::imread " << img_name << " failed\n";
        return -1;
    }

    cv::Mat image1 = cv::imread(img_name1);
    if(image1.empty())
    {
        std::cerr << "cv::imread " << img_name1 << " failed\n";
        return -1;
    }

    int min_size = 40;

    float conf_p = 0.6;
    float conf_r = 0.7;
    float conf_o = 0.8;

    float nms_p = 0.5;
    float nms_r = 0.7;
    float nms_o = 0.7;

    mtcnn* pfacedet = new mtcnn(min_size, conf_p, conf_r, conf_o, nms_p, nms_r, nms_o);
    pfacedet->load_3model(model_dir);

    int repeat_count = 1;
    const char* repeat = std::getenv("REPEAT_COUNT");

    if(repeat)
        repeat_count = std::strtoul(repeat, NULL, 10);

    struct timeval t0, t1;
    float avg_time = 0.f;
    std::cout << "102 " << "\n";
    std::vector<face_box> face_info;
    std::vector<face_box> face_info1;
    for(int i = 0; i < repeat_count; i++)
    {
        gettimeofday(&t0, NULL);
        pfacedet->detect(image, face_info);
        pfacedet->detect(image1, face_info1);
        gettimeofday(&t1, NULL);
	    current_frame_count = 1;	
        std::cout << "112 " << "\n";

    	for(unsigned int i=0;i<face_info.size();i++)
    	{
    		face_box& box=face_info[i]; 
            face_box& box1=face_info1[i]; 
            get_face_title(image,box,image1,box1,current_frame_count);
    	}
        
        float mytime = ( float )((t1.tv_sec * 1000000 + t1.tv_usec) - (t0.tv_sec * 1000000 + t0.tv_usec)) / 1000;

        std::cout << "i =" << i << " time is " << mytime << "\n";
        // <<face_info[0].x0<<","<<face_info[0].y0<<","<<face_info[0].x1<<","<<face_info[0].y1<<"\n";

        avg_time += mytime;
    }

    std::cout << "repeat " << repeat_count << ", avg time is " << avg_time / repeat_count << " \n"
              << "detected face num: " << face_info.size() << "\n";

    for(unsigned int i = 0; i < face_info.size(); i++)
    {
        face_box& box = face_info[i];
        std::printf("BOX:( %g , %g ),( %g , %g )\n", box.x0, box.y0, box.x1, box.y1);
        cv::rectangle(image, cv::Point(box.x0, box.y0), cv::Point(box.x1, box.y1), cv::Scalar(0, 255, 0), 1);
        for(int l = 0; l < 5; l++)
        {
           // cv::circle(image, cv::Point(box.landmark.x[l], box.landmark.y[l]), 1, cv::Scalar(255, 0, 255), 2);
        }
    }

    cv::imwrite(sv_name, image);

    delete pfacedet;

    release_tengine();

    return 0;
}
