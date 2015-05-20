/*M///////////////////////////////////////////////////////////////////////////////////////
 //
 //  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
 //
 //  By downloading, copying, installing or using the software you agree to this license.
 //  If you do not agree to this license, do not download, install,
 //  copy or use the software.
 //
 //
 //                           License Agreement
 //
 // Copyright (C) 2012, Takuya MINAGAWA.
 // Third party copyrights are property of their respective owners.
 //
 // Permission is hereby granted, free of charge, to any person obtaining a copy
 // of this software and associated documentation files (the "Software"), to deal
 // in the Software without restriction, including without limitation the rights to
 // use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 // of the Software, and to permit persons to whom the Software is furnished to do
 // so, subject to the following conditions:
 //
 // The above copyright notice and this permission notice shall be included in all
 // copies or substantial portions of the Software.
 //
 // THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 // INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 // PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 // HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 // OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 // SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 //
 //M*/
#include "guiAR.h"

#include <iostream>

//OpenGL
#include <GL/glut.h>
//OpenCV
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "../Tracking/trackingOBJ.h"
#include "../Overlay/viewModel.h"
#include "commonCvFunctions.h"
#include "utilFunctions.h"

#define _USE_MATH_DEFINES
#include <math.h>

//#define NO_OBJRECOG
//#define PLOT_PT
//#define NO_CAMERA
//#define NO_OVERLAY

using namespace std;
using namespace cv;
using namespace cvar;
using namespace cvar::orns;
using namespace cvar::tracking;
using namespace cvar::overlay;

controlOR* ctrlOR = 0;	// ���蕨�̔F���N���X
trackingOBJ* trckOBJ = 0;	// �I�u�W�F�N�g�ǐՃN���X
viewModel *viewMDL;	// OpenGL�摜�\���N���X�i�V���O���g���j

VideoCapture capture(1);	// �J�����L���v�`��
int seq_id = 0;	// �g���b�L���O�̃V�[�P���XID
int wait_seq_id = 0; // ��g���b�L���O���̃V�[�P���XID
bool track_f = false;	// �g���b�L���O�t���O
int query_scale = 1;	// �N�G���[�摜�k���X�P�[��
int max_query_size = 320;	// �ő�N�G���[�摜�T�C�Y
Mat query_image;	// �摜�F���N�G���[�p�k���摜�T�C�Y
//Mat pose_mat_scale;	// �z���O���t�B�s��i�[�p
string config_file = "config.xml";	// �ݒ�t�@�C��

//�X�N���[���T�C�Y�̃v���p�e�B
bool fullscreen = false;	// �t���X�N���[�����[�h
int screen_pos_x;
int screen_pos_y;
int screen_width;
int screen_height;

#ifdef NO_CAMERA
string imgname="ardemo\\test\\hoge_0.png";
//string imgname="ardemo\\test\\img_0.png";
Mat frame;
#endif

namespace cvar {

void fullScreenChange();

void setARConfigFile(string& conf_f) {
	config_file = conf_f;
}

// fixed FileNode& to FileNode
void readModelParams(FileNode fn, string& modelfile_name, int& type_id,
		float& scale, Mat& initRot, Mat& initTrans) {
	string model_type;

	fn["modelfile"] >> modelfile_name;
	fn["ModelType"] >> model_type;
	type_id = modelObjectFactory::getModelTypeId(model_type);

	if (fn["scale"].isNone()) {
		scale = 1.0;
	} else {
		fn["scale"] >> scale;
	}

	initRot.release();
	initTrans.release();

	float d[] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
	FileNode poseNode = fn["init_pose"];
	if (poseNode.isNone()) {
		initRot = Mat(3, 3, CV_32FC1, d).clone();
		initTrans.create(3, 1, CV_32FC1);
		initTrans.setTo(Scalar(0));
	} else {
		float yaw, pitch, roll;
		float x, y, z;

		poseNode["yaw"] >> yaw;
		poseNode["pitch"] >> pitch;
		poseNode["roll"] >> roll;
		poseNode["x"] >> x;
		poseNode["y"] >> y;
		poseNode["z"] >> z;

		Mat yawMat = Mat(3, 3, CV_32FC1, d).clone();
		Mat pitchMat = Mat(3, 3, CV_32FC1, d).clone();
		Mat rollMat = Mat(3, 3, CV_32FC1, d).clone();

		float rad_yaw = yaw * M_PI / 180;
		yawMat.at<float>(1, 1) = (yawMat.at<float>(0, 0) = cos(rad_yaw));
		yawMat.at<float>(0, 1) = -(yawMat.at<float>(1, 0) = sin(rad_yaw));

		float rad_pitch = pitch * M_PI / 180;
		pitchMat.at<float>(2, 2) = (pitchMat.at<float>(0, 0) = cos(rad_pitch));
		pitchMat.at<float>(0, 2) = -(pitchMat.at<float>(2, 0) = sin(rad_pitch));

		float rad_roll = roll * M_PI / 180;
		rollMat.at<float>(2, 2) = (rollMat.at<float>(1, 1) = cos(rad_roll));
		rollMat.at<float>(1, 2) = -(rollMat.at<float>(2, 1) = sin(rad_roll));

		initRot = rollMat * pitchMat * yawMat;
		initTrans.release();
		initTrans.create(3, 1, CV_32FC1);
		initTrans.at<float>(0, 0) = x;
		initTrans.at<float>(1, 0) = y;
		initTrans.at<float>(2, 0) = z;
	}
}

void setARConfig(Size& frame_size) {
	try {
		FileStorage cvfs;
		// Config�t�@�C���̓ǂݍ���
		cvfs.open(config_file, CV_STORAGE_READ);

		// ��̓t���[���p�e�N�X�`���T�C�Y(2�̗ݏ�)���v�Z
		int tw = 128;
		int th = 128;
		while (frame_size.width > tw) {
			tw <<= 1;
		}
		while (frame_size.height > th) {
			th <<= 1;
		}
		viewMDL->setTwoPowerSize(tw, th);

		// visual word�̓ǂݍ���
		FileNode fn;
		fn = cvfs["VisualWord"];
		std::string vwfile;
		fn["visualWord"] >> vwfile;
		std::string idxfile;
		fn["index"] >> idxfile;
		if (idxfile.empty()) {
			ctrlOR->loadVisualWords(vwfile);
		} else {
			ctrlOR->loadVisualWordsBinary(vwfile, idxfile);
		}

		// �I�u�W�F�N�gDB�̓ǂݍ���
		ctrlOR->loadObjectDB(cvfs["ObjectDB"]);

		// �摜�F���N�G���[�p�ő�摜�T�C�Y�̓ǂݍ���
		cvfs["max_query_size"] >> max_query_size;

		// �N�G���[�p�摜�T�C�Y��K�؂ȑ傫���֏k�����ė̈�m��
		int frame_max_size;
		if (frame_size.width > frame_size.height) {
			frame_max_size = frame_size.width;
		} else {
			frame_max_size = frame_size.height;
		}
		query_scale = 1;
		while ((frame_max_size / query_scale) > max_query_size) {
			query_scale *= 2;
		}
		query_image.create(frame_size.height / query_scale,
				frame_size.width / query_scale, CV_8UC1);

		// �J���������p�����[�^�̓ǂݍ���
		Mat camera_matrix;
		FileStorage fs(cvfs["camera_matrix"], FileStorage::READ);
		fs["camera_matrix"] >> camera_matrix;
		viewMDL->init(frame_size, camera_matrix);

		// �œ_�����ݒ�i�ȗ������ꍇ��1.0�ɐݒ肳���j
		if (!cvfs["focal_length"].isNone()) {

			// fixed error
			viewMDL->setFocalLength(cvReadReal(*cvfs["focal_length"],0));
		}

		// �t���X�N���[�����[�h�̓ǂݍ���
		string str_flg;
		if (cvfs["full_screen_mode"].isNone()) {
			str_flg = "false";
		} else {
			cvfs["full_screen_mode"] >> str_flg;
		}
		if (str_flg == "true") {
			if (!fullscreen) {
				fullScreenChange();
			}
		}

		// �~���[���[�h�̓ǂݍ���
		if (cvfs["mirror_mode"].isNone()) {
			str_flg = "false";
		} else {
			cvfs["mirror_mode"] >> str_flg;
		}
		if (str_flg == "true") {
			viewMDL->setMirrorMode(true);
		} else {
			viewMDL->setMirrorMode(false);
		}

		// �d���\���̂��߂̃��f�����ǂݍ���
		fn = cvfs["model_info"];
		FileNode fn2;
		viewMDL->releaseModel();

		FileNodeIterator fn_itr = fn.begin();
		int id, type_id;
		string modelfile_name;
		string model_type;
		float scale;
		Mat initRot, initTrans;
		Size imgsize;
		while (fn_itr != fn.end()) {
			(*fn_itr)["id"] >> id;
			imgsize = (ctrlOR->image_db.getImageInfo(id)).img_size;

			readModelParams(*fn_itr, modelfile_name, type_id, scale, initRot,
					initTrans);

			viewMDL->addModel(id, imgsize, type_id, modelfile_name, scale,
					initRot, initTrans);
			fn_itr++;
		}

		// �҂��󂯎��ɕ\�����郂�f�����ǂݍ���
		fn = cvfs["WaitingModel"];
		if (!fn.isNone()) {
			int timer = fn["timer"];
			readModelParams(fn, modelfile_name, type_id, scale, initRot,
					initTrans);
			viewMDL->addWaitModel(timer, type_id, modelfile_name, scale,
					initRot, initTrans);
		}
	} catch (std::exception& e) {
		cout << "Failed to read file " + config_file << endl;
		throw e;
	}
}

void displayFunc(void) {
#ifndef NO_CAMERA
	Mat frame;
	if (capture.isOpened()) { //�J���������݂���Ƃ�
		//�L���v�`��
		capture >> frame;
	} else { //�J���������݂��Ȃ��Ƃ�
		//���ɂ�邱�ƂȂ�
	}
#else
	frame = imread(imgname);
#endif

#ifndef NO_OBJRECOG
	//�e�N�X�`���ɕ`�悵�����摜�𓊂���
	Mat grayImg;
	cvtColor(frame, grayImg, CV_BGR2GRAY);

	if (!track_f) {
		try {
			cv::resize(grayImg, query_image, query_image.size());
			vector<resultInfo> recog_result = ctrlOR->queryImage(query_image);// �k���摜�ŔF��
//			vector<resultInfo> recog_result = ctrlOR->queryImage(grayImg);	// �J��������̉摜�ŔF��
			if (!recog_result.empty()) {

				cout << "img id: " << recog_result[0].img_id << endl;

				// k¬æpzOtBðJæpÉÏ·
				Mat pose_mat_scale = recog_result[0].pose_mat.clone();
				pose_mat_scale.row(0) *= query_scale;
				pose_mat_scale.row(1) *= query_scale;

				const Mat& test = grayImg;

				vector<Point2f> test1 = scalePoints(recog_result[0].object_position, (double)query_scale);

				trckOBJ->startTracking(test, test1 );
				track_f = viewMDL->setRecogId(recog_result[0].img_id, pose_mat_scale);

//				trckOBJ.startTracking(grayImg, recog_result[0].object_position);
//				viewMDL->setRecogId(recog_result[0].img_id, recog_result[0].pose_mat);
//				track_f = true;
				seq_id = 0;
				wait_seq_id = 0;

				// Draw Result
//				drawLineContour(frame, trckOBJ.object_position, Scalar(255));
//				vector<Point2f>::iterator itr = trckOBJ.corners.begin();
//				while(itr!=trckOBJ.corners.end()){
//					circle(frame, *itr, 3, Scalar(255,0,0));
//					itr++;
//				}
			}
		} catch (exception& e) {
		}
	} else {
		track_f = trckOBJ->onTracking(grayImg);
		seq_id++;
	}
#endif

#ifdef PLOT_PT
	if(track_f) {
		drawLineContour(frame, trckOBJ.object_position, Scalar(255));
		drawPoints(frame, trckOBJ.corners, trckOBJ.track_status, Scalar(255));
	}
#endif

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	viewMDL->drawScene(frame);

	////////////////// �I�u�W�F�N�g��`�� //////////////////
//	drawOctahedron();
#ifndef NO_OVERLAY
	if (track_f) {
		try {
			viewMDL->drawObject(trckOBJ->getHomographyMat(), seq_id);
		} catch (std::exception& e) {
			track_f = false;
		}
	} else {
		try {
			viewMDL->drawWaitModel(wait_seq_id);
			wait_seq_id++;
		} catch (std::exception& e) {
		}
	}
#endif

	// �`��i�o�b�t�@�[���ւ��j
//	glFlush();

	glutSwapBuffers();

}

// �A�C�h�����̃R�[���o�b�N
void idleFunc() {
	//�ĕ`��v��
	glutPostRedisplay();
}

// �E�C���h�E���T�C�Y�̃R�[���o�b�N
void resizeFunc(int w, int h) {
	viewMDL->resize(w, h);
}

void fullScreenChange() {
	if (fullscreen) {
		glutReshapeWindow(screen_width, screen_height);
		glutPositionWindow(screen_pos_x, screen_pos_y);
		fullscreen = false;
	} else {
		screen_pos_x = glutGet(GLUT_WINDOW_X);
		screen_pos_y = glutGet(GLUT_WINDOW_Y);
		screen_width = glutGet(GLUT_WINDOW_WIDTH);
		screen_height = glutGet(GLUT_WINDOW_HEIGHT);
		glutFullScreen();
		fullscreen = true;
	}
}

// �L�[�{�[�h��̓R�[���o�b�N
void keyboardFunc(unsigned char key, int x, int y) {
	switch (key) {
	case 'q':
	case 'Q':
	case '\033':  // '\033' �� ESC �� ASCII �R�[�h
		exit(0);
		break;
	case 'f':
	case 'F':
		fullScreenChange();
		break;
	default:
		break;
	}
}

// �I���֐�
void myExit() {
	viewMDL->exitFunc();
	query_image.release();
	delete trckOBJ;
}

void setControlOR(controlOR& ctrlOR_cls) {
	ctrlOR = &ctrlOR_cls;
}

int startGUI(int argc, char *argv[]) {
	// viewModel�̎擾
	viewMDL = viewModel::getInstance();

	// �I�������̒�`
	atexit(myExit);

#ifndef NO_CAMERA
	// �J��������
	if (!capture.isOpened()) {
		std::cout << "Failed to Open Camera" << std::endl;
		return -1;
	}

	Mat frame;
	capture >> frame;
#else
	frame = imread(imgname);
#endif

	//Initialize OpenGL
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(frame.cols, frame.rows);
	glutCreateWindow("Augmented Reality");

	try {
		trckOBJ = trackingOBJ::create(trackingOBJ::TRACKER_KLT);

		Size s = Size(frame.cols, frame.rows);
		setARConfig(s);

	} catch (std::exception& e) {
		throw e;
	}

#ifndef NO_OBJRECOG
	if (ctrlOR == 0)
		return -1;
#else
	track_f = true;
	double d2[] = {1,0,0,0,1,0,0,0,1};
	Mat diagMat = Mat(3,3,CV_64FC1,d2).clone();
	trckOBJ.homographyMat = diagMat;
	viewMDL->setRecogId(4,diagMat);
#endif

	//callback functions
	glutDisplayFunc(displayFunc);
	glutReshapeFunc(resizeFunc);
	glutIdleFunc(idleFunc);
	glutKeyboardFunc(keyboardFunc);

	// main loop
	glutMainLoop();

	viewModel::deleteInstance();

	return 0;
}

}
;
