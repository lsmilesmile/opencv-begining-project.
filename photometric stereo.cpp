#include "stdafx.h"
#include<iostream>
#include<vector>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include <fstream>
#include <string>

using namespace std;
using namespace cv;
string IMAGE_PATH_PREFIX = "Objects/";
Mat readlightDirectionTxt(string file);//返回20行3列，每一行为一个光照参数向量
vector<Mat>GetImage();
Mat CalNormalVector(vector<Mat>& imgs, Mat& S);
int main()
{
	Mat S=readlightDirectionTxt("light_directions.txt");
   // Mat result;
	vector<Mat> imgs=GetImage();
	CalNormalVector(imgs,S);
	getchar();
}
Mat readlightDirectionTxt(string file){
	double a[3][20];
	char c;
	ifstream infile;
	infile.open(file.data());   //将文件流对象与文件连接起来 
	assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 
	for (int i = 0; i<3; i++)	
		for (int j = 0; j < 20; j++)
		{
		infile >> a[i][j];
		infile >> c;//跳过txt文件的逗号
		}
	Mat kk(3, 20, CV_32FC1);
	for (int i = 0; i <3; i++)
		for (int j = 0; j < 20; j++)//20列
			kk.at<float>(i, j) = a[i][j];
	      kk=kk.t();
	//cout << kk;
	return kk;
}
vector<Mat>GetImage(){
	vector<Mat> imgs;
	Mat img = imread(IMAGE_PATH_PREFIX + "Image_01.png", 0);
		imgs.push_back(img);
		img = imread(IMAGE_PATH_PREFIX + "Image_02.png", 0);
		imgs.push_back(img);
		img = imread(IMAGE_PATH_PREFIX + "Image_03.png", 0);
		imgs.push_back(img);
		img = imread(IMAGE_PATH_PREFIX + "Image_04.png", 0);
		imgs.push_back(img);
		img = imread(IMAGE_PATH_PREFIX + "Image_05.png", 0);
		imgs.push_back(img);
		img = imread(IMAGE_PATH_PREFIX + "Image_06.png", 0);
		imgs.push_back(img);
		img = imread(IMAGE_PATH_PREFIX + "Image_07.png", 0);
		imgs.push_back(img);
		img = imread(IMAGE_PATH_PREFIX + "Image_08.png", 0);
		imgs.push_back(img);
		img = imread(IMAGE_PATH_PREFIX + "Image_09.png", 0);
		imgs.push_back(img);
		img = imread(IMAGE_PATH_PREFIX + "Image_10.png", 0);
		imgs.push_back(img);
		img = imread(IMAGE_PATH_PREFIX + "Image_11.png", 0);
		imgs.push_back(img);
		img = imread(IMAGE_PATH_PREFIX + "Image_12.png", 0);
		imgs.push_back(img);
		img = imread(IMAGE_PATH_PREFIX + "Image_13.png", 0);
		imgs.push_back(img);
		img = imread(IMAGE_PATH_PREFIX + "Image_14.png", 0);
		imgs.push_back(img);
		img = imread(IMAGE_PATH_PREFIX + "Image_15.png", 0);
		imgs.push_back(img);
		img = imread(IMAGE_PATH_PREFIX + "Image_16.png", 0);
		imgs.push_back(img);
		img = imread(IMAGE_PATH_PREFIX + "Image_17.png", 0);
		imgs.push_back(img);
		img = imread(IMAGE_PATH_PREFIX + "Image_18.png", 0);
		imgs.push_back(img); 
		img = imread(IMAGE_PATH_PREFIX + "Image_19.png", 0);
		imgs.push_back(img); 
		img = imread(IMAGE_PATH_PREFIX + "Image_20.png", 0);
		imgs.push_back(img);
	return imgs;
}
Mat CalNormalVector(vector<Mat>& imgs, Mat& S){
	Mat mask = imread("mask.jpg", 0);
	mask = mask / 255.0;
	Mat I = Mat(20, 1, CV_32FC1); 
	Mat result = Mat(mask.rows, mask.cols, CV_32FC3);
	Mat S_1;
	invert(S, S_1, DECOMP_SVD);
	for (int i = 0; i < mask.rows; i++)
			for (int j = 0; j < mask.cols; j++)
			{
			if (mask.at<uchar>(i, j) == 0) continue;
			   for (int n = 0; n < 20; n++)			 
				   I.at<float>(n, 0) = imgs[n].at<uchar>(i, j);//得到每个像素的I（20X1）
			   Mat G= S_1*Mat(I);
			   float p = sqrt(G.dot(G));
			   Mat n;
			   if (p > 0)
				   n = G*1.0 / p;
			   else n = G;
			   result.at <Vec3f>(i,j)= n;
			} 
	Mat N,normal;
	result.convertTo(N,CV_8UC3,255,0);//之前就死在没有乘以255，一除去p全图变黑，不除p等同于法向量没有归一化，效果图会出现颜色突变
	cvtColor(N,normal,CV_BGR2RGB);
	imshow("result", normal);
	waitKey(0);
	return normal;
}

