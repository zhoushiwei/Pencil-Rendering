#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
void ConvertCombine(IplImage * src,IplImage * dst)
{
	float theta = rand()%100;
	theta -= 50;
	theta /= 10;

	
	IplImage * middle = cvCloneImage(src) ;
	middle->origin = src->origin;
	cvZero(middle);//��ת���м���������middle
	CvMat* rot_mat = cvCreateMat(2,3,CV_32FC1);//�����վ�����Ϊ��ת����
	CvPoint2D32f center = cvPoint2D32f(src->width/2,src->height/2);//ͼ������Ϊ��ת����
	double scale = 20 +(rand()%160);
	scale /= 100;//��С�������80%
	cv2DRotationMatrix(center,theta,scale,rot_mat);
	//����ƽ�Ʊ任��ƽ�Ʊ任����������256���
	*( (float*)CV_MAT_ELEM_PTR(*rot_mat,0,2)) += rand()%512 - 256;
	*( (float*)CV_MAT_ELEM_PTR(*rot_mat,1,2)) += rand()%512 - 256 + 20;
	cvWarpAffine(src,middle,rot_mat);
	
	/*float mov[] = {	1,0,rand()%512 - 256,
					0,1,rand()%512 - 256};
	CvMat mov_mat = cvMat(2,3,CV_32FC1,mov);
	
	cvWarpAffine(middle,middle2,&mov_mat);*/
	//����alpha���
	IplImage * middle2 = cvCloneImage(dst) ;
	cvAddWeighted(middle2,1.0,middle,(float)(rand()%50)/100 + 0.5,0,dst);
	//cvNamedWindow("middle");
	//cvShowImage("middle",dst);
	//cvWaitKey(0);
	cvReleaseImage(&middle);
	cvReleaseImage(&middle2);
	//cvDestroyWindow("middle");

}
int main()
{
	srand((unsigned)time(0));
	cvNamedWindow("src");
	cvNamedWindow("dst");
	IplImage * src = cvLoadImage("stokes.bmp",0);
	cvShowImage("src",src);
	cvNot(src,src);

	IplImage * dst = cvCreateImage(cvGetSize(src),src->depth,src->nChannels);
	cvCopy(src,dst);//����Ŀ��ͼ��
	for(int now = 1; now <= 32 ; now ++)
	{
		IplImage * dstcopy = cvCloneImage(dst);
		for(int i = 0; i < 70 ; i++)
		{
			ConvertCombine(src,dst);//ÿһ���������һ������������Ŀ��ͼ��
		}//��������
		CvScalar score = cvAvg(dst);
		printf("%02d:%d\n",now,(int)score.val[0]);
		if(now <= 20)
		{
			if((int)score.val[0] != now * 7)
			{
				now --;
				cvReleaseImage(&dst);
				dst = cvCloneImage(dstcopy);
			}
			else
			{
				cvNot(dst,dst);
				char filename[100];
				sprintf(filename,"%02d.bmp",now);
				cvSaveImage(filename,dst);
				cvNot(dst,dst);
			}
		}
		else if(now <= 25)
		{
			if((int)score.val[0] != now * 7 - (now - 20))
			{
				now --;
				cvReleaseImage(&dst);
				dst = cvCloneImage(dstcopy);
			}
			else
			{
				cvNot(dst,dst);
				char filename[100];
				sprintf(filename,"%02d.bmp",now);
				cvSaveImage(filename,dst);
				cvNot(dst,dst);
			}
		}
		else if(now < 30)
		{
			if((int)score.val[0] != 170 + (now-25)*5)
			{
				now --;
				cvReleaseImage(&dst);
				dst = cvCloneImage(dstcopy);
			}
			else
			{
				cvNot(dst,dst);
				char filename[100];
				sprintf(filename,"%02d.bmp",now);
				cvSaveImage(filename,dst);
				cvNot(dst,dst);
			}
		}
		else
		{
			if((int)score.val[0] != 190 + (now-29)*4)
			{
				now --;
				cvReleaseImage(&dst);
				dst = cvCloneImage(dstcopy);
			}
			else
			{
				cvNot(dst,dst);
				char filename[100];
				sprintf(filename,"%02d.bmp",now);
				cvSaveImage(filename,dst);
				cvNot(dst,dst);
			}
		}
		cvReleaseImage(&dstcopy);
		//cvShowImage("dst",dst);
		//cvWaitKey(100);
		//cvNot(dst,dst);
	}
	cvNot(dst,dst);
	cvShowImage("dst",dst);
	cvWaitKey(0);
	cvReleaseImage(&dst);
	cvReleaseImage(&src);
	cvDestroyWindow("src");
	return(0);
}