#include "get_face.hpp"
#include "lightened_cnn.hpp"
#include "common1.hpp"

feature_extractor *p_extractor;
face_verifier   * p_verifier;
std::vector<face_window*> face_win_list;
//extern lightened_cnn facelightcnn;

float compare(float * f0, float * f1, int len)
{
	float  product=0;
	float l2_sum0=0;
	float  l2_sum1=0;

	float score;


	for(int i=0;i<len;i++)
	{
		product+=f0[i]*f1[i];
		l2_sum0+=f0[i]*f0[i];
		l2_sum1+=f1[i]*f1[i];
	}

	score=product/sqrt(l2_sum0)/sqrt(l2_sum1);

	return score;
}

void get_face_title(cv::Mat& frame,face_box& box,cv::Mat& frame1,face_box& box1,unsigned int frame_seq)
{
	float feature[256];
	float feature1[256];
	//int face_id;
	float score;
	//face_window * p_win;
    const std::string extractor_name("lightened_cnn");
    lightened_cnn facelightcnn(extractor_name);
    const std::string root_path = get_root_path();
	std::string model_dir = root_path + "examples/build/faceid/models";
	//p_win=get_face_id_name_by_position(box,frame_seq);
	facelightcnn.load_model(model_dir);
#if 1
	cv::Mat aligned;
	cv::Mat aligned1;
	std::cout << "get_face 45 " << "\n";
	/* align face */
	get_aligned_face(frame,(float *)&box.landmark,5,128,aligned);
	/* align face */
	get_aligned_face(frame1,(float *)&box1.landmark,5,128,aligned1);
	std::cout << "get_face 50 " << "\n";
	/* get feature */
	facelightcnn.extract_feature(aligned,feature);
	/* get feature */
	facelightcnn.extract_feature(aligned1,feature1);
	std::cout << "get_face 55 " << "\n";
	/* search feature in db */
	float ret=compare(feature,feature1,256);
	//int ret=p_verifier->search(feature,&face_id,&score);
	std::cout << "ret  result " << ret  << "\n";
	/* found in db*/
	if(ret==0 && score>0.8)
	{
          //      p_win->face_id=face_id;
		//get_face_name_by_id(face_id,p_win->name);
	}
#endif

	//sprintf(p_win->title,"%d %s",p_win->face_id,p_win->name.c_str());
}





