#include <iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

//素材图像尺寸
const int step_x = 20;
const int step_y = 20;

//获取文件夹下所有图像路径
int getImagePathList(string folder, vector<String>& imagePathList)
{
	glob(folder, imagePathList);
	return 0;
}

int main()
{
	Mat src = imread("D:\\studyspace\\OneEyeKunKun\\kunkun\\kunkun.jpg");
	if (src.empty())
	{
		cout << "No image!" << endl;
		system("pause");
		return 0;
	}

	resize(src, src, Size(step_x * 30, step_y * 30), 1, 1, INTER_CUBIC);

	//imshow("test", src);	
	//waitKey(0);
	vector<Mat>images;
	string filename = "D:\\studyspace\\OneEyeKunKun\\dingzheng";
	cout << "loading..." << endl;

	vector<String> imagePathList;
	getImagePathList(filename, imagePathList);

	for (int i = 0; i < imagePathList.size(); i++)
	{
		Mat img = cv::imread(imagePathList[i]);
		resize(img, img, Size(step_x, step_y), 1, 1, INTER_AREA);

		images.push_back(img);

	}
	cout << "done!" << endl;

	int rows = src.rows;
	int cols = src.cols;
	//height:表示生成的蒙太奇图像需要多少张素材图像填充rows
	//width:表示生成的蒙太奇图像需要多少张素材图像填充cols
	int height = rows / step_y, width = cols / step_x;

	Mat dst = Mat(src.size(), CV_8UC3, Scalar(255, 255, 255));
	for (int i = 0; i < height; ++i)
	{
	//int i = 0;
		for (int j = 0; j < width; ++j)
		{
			//index表示当前素材图像的索引
			int index = i * width + j;
			auto w = j * step_x;
			auto h = i * step_y;
			
			//将图像赋值给需要生成的蒙太奇图像对应区域
			images[index].copyTo(dst(Rect(j * step_x, i * step_y, step_x, step_y)));

		}
	}

	imshow("dst", dst);

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			//像素RGB值修改
			dst.at<Vec3b>(i, j)[0] = 0.512 * dst.at<Vec3b>(i, j)[0] + 0.498 * src.at<Vec3b>(i, j)[0];
			dst.at<Vec3b>(i, j)[1] = 0.512 * dst.at<Vec3b>(i, j)[1] + 0.498 * src.at<Vec3b>(i, j)[1];
			dst.at<Vec3b>(i, j)[2] = 0.512 * dst.at<Vec3b>(i, j)[2] + 0.498 * src.at<Vec3b>(i, j)[2];
		}
	}

	imshow("蒙太奇图像", dst);
	waitKey(0);
	system("pause");
	return 0;
}
