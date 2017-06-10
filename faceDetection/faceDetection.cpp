// faceDetection.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "dirent.h"
#include <vector>
#include <string>
#include <iostream>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\imgproc\imgproc.hpp>
using namespace std;
using namespace cv;
int getdir(string dir, vector<string> &files);
int _tmain(int argc, _TCHAR* argv[])
{
	string dir = string(".");//資料夾路徑(絕對位址or相對位址)
	vector<string> files = vector<string>();
	getdir(dir, files);
	CascadeClassifier face_cascade;
	face_cascade.load("C:\\opencv\\sources\\data\\haarcascades_cuda\\haarcascade_frontalface_alt.xml");
	std::vector<Rect> faces;
	CreateDirectoryA("dst", NULL);
	for (unsigned int i = 0; i < files.size(); i++){
		Mat src = imread(files[i],1),dst;
		if (src.data != 0){//如果讀到檔影像了
			resize(src, src, Size(1680, 2376));
			face_cascade.detectMultiScale(src, faces, 1.1, 3, CV_HAAR_SCALE_IMAGE, Size(90, 120));
			for (unsigned int j = 0; j < faces.size(); j++){
				Mat dst = src(Rect(faces[j].x, faces[j].y /*- int(faces[j].height * 1 / 2)*/, faces[j].width, (int)faces[j].height/* *4 / 3*/));
				imwrite(".\\dst\\" + files[i], dst);
				cout << files[i] << endl;//輸出資料夾和檔案名稱於螢幕
			}
		}
	}
	system("pause");
	return 0;
}
int getdir(string dir, vector<string> &files){
	DIR *dp;//創立資料夾指標
	struct dirent *dirp;
	if ((dp = opendir(dir.c_str())) == NULL){
		cout << "Error(" << errno << ") opening " << dir << endl;
		return errno;
	}
	while ((dirp = readdir(dp)) != NULL){//如果dirent指標非空
		files.push_back(string(dirp->d_name));//將資料夾和檔案名放入vector
	}
	closedir(dp);//關閉資料夾指標
	return 0;
}