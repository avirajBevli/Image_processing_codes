/* #include<limits.h>  //for INT_MAX
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <math.h>
#include <iostream>
#include <queue>

using namespace cv;
using namespace std;


Point find_end(Mat img);

Point find_start(Mat img);

queue<Point> q; //q is a queue of Points  

int i = 0;

int isValidPixel(int r, int c, Mat img, Mat is_visited);

int main()
{
	Mat img = imread("path (2).jpg",CV_LOAD_IMAGE_COLOR);
	//Mat mdfs = Mat::zeros(img.rows, img.cols, CV_16UC1);
	Mat mdfs(img.rows, img.cols, CV_16UC1, Scalar(2000));
	//initially assign infinte mdfs to all the pixels
cout<<mdfs.at<uchar>(2,2)<<endl;

	namedWindow("image");
	namedWindow("is_visited");

	Mat is_visited = Mat::zeros(img.rows, img.cols, CV_8UC1);
	Mat prev_x = Mat::zeros(img.rows, img.cols, CV_8UC1);
	Mat prev_y = Mat::zeros(img.rows, img.cols, CV_8UC1);
	//is_visited value is zero if not visited, 1 if only visited once, 2 if properly visited

	//Mat prev = Mat::zeros(img.rows, img.cols, CV_8UC2);
	//1st channel is for the x coordinates

	Point start = find_start(img);
	Point end = find_end(img);

	is_visited.at<uchar>(start.y, start.x) = 2;
	mdfs.at<uchar>(start.y, start.x) = 0;

	Point current, temp;

	q.push(start);
	int i;

	while(!q.empty())
	{
		current = q.front();
		is_visited.at<uchar>(current.y, current.x) == 2;

		if( isValidPixel(current.y + 1 , current.x, img, is_visited) )
		{
			temp.x = current.x;
			temp.y = current.y + 1;
			prev_x.at<uchar>(temp.y, temp.x) = current.x;
			prev_y.at<uchar>(temp.y, temp.x) = current.y;

			img.at<Vec3b>(temp.y , temp.x)[0]=200; //making the pixels traversed bluish-greenish in color
			img.at<Vec3b>(temp.y , temp.x)[1]=10;		
			img.at<Vec3b>(temp.y , temp.x)[2]=0;

			if(is_visited.at<uchar>(temp.y, temp.x) == 1)
			{
				if( (mdfs.at<uchar>(current.y, current.x)+ sqrt( pow(temp.x-current.x , 2) + pow(temp.y-current.y , 2)) ) < (mdfs.at<uchar>(temp.y, temp.x)) )
				{
					mdfs = mdfs.at<uchar>(current.y, current.x)+ sqrt( pow(temp.x-current.x , 2) + pow(temp.y-current.y , 2)); 
				}

			}
			
			else if(is_visited.at<uchar>(temp.y, temp.x) == 0)
			{
				mdfs.at<uchar>(temp.y, temp.x) = mdfs.at<uchar>(current.y, current.x) + sqrt(pow((temp.x-current.x),2) + pow((temp.y-current.y),2));
				is_visited.at<uchar>(current.y, current.x) = 1;

			}

			if(temp.x==end.x && temp.y==end.y)
			{
				break;
			}

			q.push(temp);
		}

		
		if( isValidPixel(current.y , current.x + 1, img, is_visited) )
		{
			temp.x = current.x + 1;
			temp.y = current.y;
			prev_x.at<uchar>(temp.y, temp.x) = current.x;
			prev_y.at<uchar>(temp.y, temp.x) = current.y;

			img.at<Vec3b>(temp.y , temp.x)[0]=200; //making the pixels traversed bluish-greenish in color
			img.at<Vec3b>(temp.y , temp.x)[1]=10;		
			img.at<Vec3b>(temp.y , temp.x)[2]=0;

			if(is_visited.at<uchar>(temp.y, temp.x) == 1)
			{
				if( (mdfs.at<uchar>(current.y, current.x)+ sqrt( pow(temp.x-current.x , 2) + pow(temp.y-current.y , 2)) ) < (mdfs.at<uchar>(temp.y, temp.x)) )
				{
					mdfs = mdfs.at<uchar>(current.y, current.x)+ sqrt( pow(temp.x-current.x , 2) + pow(temp.y-current.y , 2)); 
				}

			}
			
			else if(is_visited.at<uchar>(temp.y, temp.x) == 0)
			{
				mdfs.at<uchar>(temp.y, temp.x) = mdfs.at<uchar>(current.y, current.x) + sqrt(pow((temp.x-current.x),2) + pow((temp.y-current.y),2));
				is_visited.at<uchar>(current.y, current.x) = 1;

			}

			if(temp.x==end.x && temp.y==end.y)
			{
				break;
			}

			q.push(temp);
		}

		
		if( isValidPixel(current.y - 1, current.x , img, is_visited) )
		{
			temp.x = current.x;
			temp.y = current.y - 1;
			prev_x.at<uchar>(temp.y, temp.x) = current.x;
			prev_y.at<uchar>(temp.y, temp.x) = current.y;

			img.at<Vec3b>(temp.y , temp.x)[0]=200; //making the pixels traversed bluish-greenish in color
			img.at<Vec3b>(temp.y , temp.x)[1]=10;		
			img.at<Vec3b>(temp.y , temp.x)[2]=0;

			if(is_visited.at<uchar>(temp.y, temp.x) == 1)
			{
				if( (mdfs.at<uchar>(current.y, current.x)+ sqrt( pow(temp.x-current.x , 2) + pow(temp.y-current.y , 2)) ) < (mdfs.at<uchar>(temp.y, temp.x)) )
				{
					mdfs = mdfs.at<uchar>(current.y, current.x)+ sqrt( pow(temp.x-current.x , 2) + pow(temp.y-current.y , 2)); 
				}

			}
			
			else if(is_visited.at<uchar>(temp.y, temp.x) == 0)
			{
				mdfs.at<uchar>(temp.y, temp.x) = mdfs.at<uchar>(current.y, current.x) + sqrt(pow((temp.x-current.x),2) + pow((temp.y-current.y),2));
				is_visited.at<uchar>(current.y, current.x) = 1;

			}

			if(temp.x==end.x && temp.y==end.y)
			{
				break;
			}

			q.push(temp);
		}

		if( isValidPixel(current.y , current.x - 1, img, is_visited) )
		{
			temp.x = current.x - 1;
			temp.y = current.y;
			prev_x.at<uchar>(temp.y, temp.x) = current.x;
			prev_y.at<uchar>(temp.y, temp.x) = current.y;

			img.at<Vec3b>(temp.y , temp.x)[0]=200; //making the pixels traversed bluish-greenish in color
			img.at<Vec3b>(temp.y , temp.x)[1]=10;		
			img.at<Vec3b>(temp.y , temp.x)[2]=0;

			if(is_visited.at<uchar>(temp.y, temp.x) == 1)
			{
				if( (mdfs.at<uchar>(current.y, current.x)+ sqrt( pow(temp.x-current.x , 2) + pow(temp.y-current.y , 2)) ) < (mdfs.at<uchar>(temp.y, temp.x)) )
				{
					mdfs = mdfs.at<uchar>(current.y, current.x)+ sqrt( pow(temp.x-current.x , 2) + pow(temp.y-current.y , 2)); 
				}

			}
			
			else if(is_visited.at<uchar>(temp.y, temp.x) == 0)
			{
				mdfs.at<uchar>(temp.y, temp.x) = mdfs.at<uchar>(current.y, current.x) + sqrt(pow((temp.x-current.x),2) + pow((temp.y-current.y),2));
				is_visited.at<uchar>(current.y, current.x) = 1;

			}

			if(temp.x==end.x && temp.y==end.y)
			{
				break;
			}

			q.push(temp);
		}

		q.pop();

		imshow("image",img);
		imshow("is_visited",is_visited);
		waitKey(1);
	}

	imshow("image",img);
	imshow("is_visited",is_visited);
	waitKey(0);
	destroyAllWindows();
	return 0;
}



int isValidPixel(int r, int c, Mat img ,Mat is_visited)
{
	if( !(img.at<Vec3b>(r,c)[0]==255 && img.at<Vec3b>(r,c)[1]==255 && img.at<Vec3b>(r,c)[2]==255 ) && (is_visited.at<uchar>(r,c) != 2) && r<img.rows && c<img.cols) //the pixel is not a part of the white obstacle
	{
		return 1;
	}

	else
	{
		return 0;
	}
}



Point find_end(Mat img)
{
	Mat hsv,bw;

	cvtColor(img,hsv,COLOR_BGR2HSV);  //convert rgb image to hsv scale

	inRange(hsv,Scalar(0,177,46),Scalar(36,255,255),bw);  //hue of red is 0-20
	//if a pixel in the hsv image is in the range of (0,177,46) and (36,255,255) in the HSV scale, then threshold such that
	//the correspoding pixel in the output matrix has value 255, otherwise 0

	//now the bw matrix is a greyscale image such that only the red dot(end point) is bright and other things are dark pixels(value 0)

	Moments omoments= moments(bw);  //calculate the moment values of all the pixels

	double m10 = omoments.m10; //summation of weight of pixels into x
	double m01 = omoments.m01; //summation of weight of pixels into y
	double m00 = omoments.m00; //summation of weight of pixels 
	//cout<<m10/m00<<" "<<m01/m00<<" "<<(int)(m10/m00)<<" "<<(int)(m01/m00);
	
	return Point(m10/m00,m01/m00);  //find_End() function returns the coordinates of the centroid of the red spot(end point)
}


Point find_start(Mat img)
{
	Mat hsv,bw;
	//namedWindow("END",WINDOW_NORMAL);
	cvtColor(img,hsv,COLOR_BGR2HSV);
	
	inRange(hsv,Scalar(35,177,46),Scalar(117,255,255),bw);  //hue of green is 110-130
	
	Moments omoments = moments(bw); 
	
	double m10=omoments.m10; //x power 1 and y power 0
	double m01=omoments.m01;
	double m00=omoments.m00;
	//imshow("END",bw);
	//waitKey(0);

	return Point(m10/m00,m01/m00);
}
 */


#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <math.h>
#include <iostream>
#include <queue>

using namespace cv;
using namespace std;

queue<Point> q; //q is a queue of Points 



Point find_end(Mat img);

Point find_start(Mat img); 

int isValidPixel(int r, int c, Mat img, Mat is_visited);

int dist(int x1, int x2, int y1, int y2);

Point stuck(Mat is_visited);

int main()
{
	Mat img = imread("sample.jpg",CV_LOAD_IMAGE_COLOR);
	//Mat mdfs = Mat::zeros(img.rows, img.cols, CV_16UC1);
	//Mat mdfs(img.rows, img.cols, CV_16UC1, Scalar(2000));
	//initially assign infinte mdfs to all the pixels


	int mdfs[img.rows][img.cols];

	int counter = 0;

	int i,j;

	for(i=0;i<img.rows;i++)
	{
		for(j=0;j<img.cols;j++)
		{
			mdfs[i][j] = 2000;
		}
	}

	//cout<<mdfs[67][130]<<endl;

	namedWindow("image");
	namedWindow("is_visited");

	Mat is_visited = Mat::zeros(img.rows, img.cols, CV_8UC1);
	//0 , 100, 200 are the 3 allowed values, for not visited, only visited, and explored respectively
	Mat prev_x = Mat::zeros(img.rows, img.cols, CV_8UC1);
	Mat prev_y = Mat::zeros(img.rows, img.cols, CV_8UC1);
	//is_visited value is zero if not visited, 1 if only visited once, 2 if properly visited

	//Mat prev = Mat::zeros(img.rows, img.cols, CV_8UC2);
	//1st channel is for the x coordinates

	Point start = find_start(img);
	Point end = find_end(img);

	//is_visited.at<uchar>(start.y, start.x) = 2;
	mdfs[start.y][start.x] = 0;

	Point current, temp;

	q.push(start);

	int r,c;
	int min;
	Point to_be_pushed;
	int flag;

	while(!q.empty())
	{
		min = 2001;
		current = q.front();
		is_visited.at<uchar>(current.y, current.x) = 200;

		if(current == end)
		{
			break;
		}
					
		flag = 0;

		for( c=current.x-1 ; c<=current.x+1 ; c++ )
		{
			for( r=current.y-1 ; r<=current.y+1 ; r++ )
			{
				if(isValidPixel(r,c,img, is_visited))
				{

					if(is_visited.at<uchar>(r,c) == 0)
					{
						mdfs[r][c] = mdfs[current.y][current.x] + dist(current.x, c, current.y, r);
						is_visited.at<uchar>(r,c) = 100;

						prev_x.at<uchar>(r,c) = current.x;
						prev_y.at<uchar>(r,c) = current.y;
					}

					else if(is_visited.at<uchar>(r,c) == 200)
					{
						continue;
					}
					

					if(mdfs[r][c] < min)
					{
						if(is_visited.at<uchar>(r,c)!=200)
						{
							min = mdfs[r][c];
							to_be_pushed.x = c;
							to_be_pushed.y = r;
							flag = 1;
						}
					}
				}
			}
		}

		if(flag == 0)
		{
			cout<<"I am stuck , help!   "<<counter<<endl;
			counter++;
			to_be_pushed = stuck(is_visited);
		}

		q.push(to_be_pushed);
		
		img.at<Vec3b>(to_be_pushed.y,to_be_pushed.x)[0] = 200;
		img.at<Vec3b>(to_be_pushed.y,to_be_pushed.x)[1] = 0;
		img.at<Vec3b>(to_be_pushed.y,to_be_pushed.x)[2] = 0;


		q.pop();

/*		imshow("image",img);
		imshow("is_visited",is_visited);
		waitKey(1);*/
	}

	int alla = 0;
/////////Code for backtracking////////////
	while(current!=start)
	{
		temp.x = prev_x.at<uchar>(current.y, current.x);
		temp.y = prev_y.at<uchar>(current.y, current.x);
		current = temp;

		img.at<Vec3b>(current.y, current.x)[0] = 200;
		img.at<Vec3b>(current.y, current.x)[1] = 100;
		img.at<Vec3b>(current.y, current.x)[2] = 100;
		
		cout<<"backtracking  "<<alla<<endl;
		alla++;

		imshow("image", img);
		imshow("is_visited", is_visited);
		waitKey(1);
	}


	imshow("image",img);
	imshow("is_visited",is_visited);
	waitKey(0);
	destroyAllWindows();
	return 0;
}



int isValidPixel(int r, int c, Mat img ,Mat is_visited)
{
	if( !(img.at<Vec3b>(r,c)[0]>150 && img.at<Vec3b>(r,c)[1]>150 && img.at<Vec3b>(r,c)[2]>150 ) && (is_visited.at<uchar>(r,c) != 200) && r<(img.rows-1) && c<(img.cols-1) && (r>0) && (c>0)) //the pixel is not a part of the white obstacle
	{
		return 1;
	}

	else
	{
		return 0;
	}
}



Point find_end(Mat img)
{
	Mat hsv,bw;

	cvtColor(img,hsv,COLOR_BGR2HSV);  //convert rgb image to hsv scale

	inRange(hsv,Scalar(0,177,46),Scalar(36,255,255),bw);  //hue of red is 0-20
	//if a pixel in the hsv image is in the range of (0,177,46) and (36,255,255) in the HSV scale, then threshold such that
	//the correspoding pixel in the output matrix has value 255, otherwise 0

	//now the bw matrix is a greyscale image such that only the red dot(end point) is bright and other things are dark pixels(value 0)

	Moments omoments= moments(bw);  //calculate the moment values of all the pixels

	double m10 = omoments.m10; //summation of weight of pixels into x
	double m01 = omoments.m01; //summation of weight of pixels into y
	double m00 = omoments.m00; //summation of weight of pixels 
	//cout<<m10/m00<<" "<<m01/m00<<" "<<(int)(m10/m00)<<" "<<(int)(m01/m00);
	
	return Point(m10/m00,m01/m00);  //find_End() function returns the coordinates of the centroid of the red spot(end point)
}


Point find_start(Mat img)
{
	Mat hsv,bw;
	//namedWindow("END",WINDOW_NORMAL);
	cvtColor(img,hsv,COLOR_BGR2HSV);
	
	inRange(hsv,Scalar(35,177,46),Scalar(117,255,255),bw);  //hue of green is 110-130
	
	Moments omoments = moments(bw); 
	
	double m10=omoments.m10; //x power 1 and y power 0
	double m01=omoments.m01;
	double m00=omoments.m00;
	//imshow("END",bw);
	//waitKey(0);

	return Point(m10/m00,m01/m00);
}


int dist(int x1, int x2, int y1, int y2)
{
	int temp = sqrt( pow((x1-x2),2) + pow((y1-y2),2) );
	return temp;
}


Point stuck(Mat is_visited)
{
	Point temp;
	int i,j;
	for(i=0;i<is_visited.rows;i++)
	{
		for(j=0;j<is_visited.cols;j++)
		{
			if(is_visited.at<uchar>(i,j)==100)
			{
				temp.x = j;
				temp.y = i;
			}
		}
	}

	return temp;
}