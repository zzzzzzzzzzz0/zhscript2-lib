#include<opencv2/opencv.hpp>
#include<cstdio>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace cv;
using namespace std;

class Screen_ {
	Display* display = nullptr;
	XImage* ximg = nullptr;
	//std::vector<std::uint8_t> pixels;
	
	void free__() {
		if(ximg) {
			XDestroyImage(ximg);
			ximg = nullptr;
		}
		if(display) {
			XCloseDisplay(display);
			display = nullptr;
		}
	}
public:
	~Screen_() {
		free__();
	}
	void mk__(Mat &img, int type) {
		display = XOpenDisplay(nullptr);
		Window root = DefaultRootWindow(display);
		XWindowAttributes xwa = {0};
		XGetWindowAttributes(display, root, &xwa);
		int w = xwa.width;
		int h = xwa.height;
		//XYBitmap, XYPixmap, ZPixmap
		XImage* ximg = XGetImage(display, root, 0, 0, w, h, AllPlanes, ZPixmap);
		int bpp = ximg->bits_per_pixel;
		type = bpp > 24 ? CV_8UC4 : CV_8UC3;
		
		/*pixels.resize(w * h * 4);
		memcpy(&pixels[0], ximg->data, pixels.size());
		img = Mat(h, w, type, &pixels[0]);*/

		img = Mat(h, w, type, ximg->data);
#ifdef ver_debug_
		/*vector<int> compression_params;
		compression_params.push_back(IMWRITE_PNG_COMPRESSION);
		compression_params.push_back(9);
		imwrite("tmp.png", img, compression_params);*/
		imshow("img", img);
		waitKey(0);
#endif
	}
};

extern "C" void match_tmpl__(const char *imgname, const char *tmplname, int readmode, int method,
		char *buf, const char *buf_fmt,
		bool show, int thickness, int lineType, int rect_color_r, int rect_color_g, int rect_color_b) {
#ifdef ver_debug_
	printf("match_tmpl__%s_%s_%d_%s\n", imgname, tmplname, method, buf_fmt);
#endif
	try {
		Mat tmpl = imread(tmplname, readmode);
		Mat img;
		Screen_ scr;
		if(imgname)
			img = imread(imgname, readmode);
		else
			scr.mk__(img, tmpl.type());

		//创建输出图像，输出图像的宽度 = 被查找到额图像的宽度 - 模版图像的宽度 + 1， 高度同样符合
		Mat dst;
		dst.create(img.rows - tmpl.rows + 1, img.cols - tmpl.cols + 1, CV_32FC1);

#ifdef ver_debug_
		{
			//Assertion failed ((depth == CV_8U || depth == CV_32F) && type == _templ.type() && _img.dims() <= 2)
			int type = img.type(), depth = CV_MAT_DEPTH(type);
			int type2 = tmpl.type();
			printf("depth=%d(%d|%d) type=%d/%d \n", depth, CV_8U, CV_32F, type, type2);
		}
#endif
		/*//进行模版匹配，首先是方式0（平方差匹配法）
		matchTemplate(img_play, tmpl, dst, 0);
		normalize(dst, dst, 0, 1, 32);*/
		// 进行匹配和标准化
		matchTemplate(img, tmpl, dst, method);
		normalize(dst, dst, 0, 1, NORM_MINMAX, -1, Mat());

		/*//首先是从得到的 输出矩阵中得到 最大或最小值（平方差匹配方式是越小越好，所以在这种方式下，找到最小位置）
		Point minPoint;
		minMaxLoc(dst, 0, 0, &minPoint, 0);*/
		// 通过函数 minMaxLoc 定位最匹配的位置
		double minVal, maxVal;
		Point minLoc, maxLoc, loc;
		minMaxLoc(dst, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
		/// 对于方法 SQDIFF 和 SQDIFF_NORMED, 越小的数值代表更高的匹配结果. 而对于其他方法, 数值越大匹配越好
		switch(method) {
		case CV_TM_SQDIFF:
		case CV_TM_SQDIFF_NORMED:
			loc = minLoc;
			break;
		default:
			loc = maxLoc;
			break;
		}

		Point loc2 = Point(loc.x + tmpl.cols, loc.y + tmpl.rows);
		sprintf(buf, buf_fmt, loc.x, loc.y, loc2.x, loc2.y);

		if(show) {
			Mat img_play;
			img.copyTo(img_play);

			/*rectangle(img_play, minPoint, Point(minPoint.x + tmpl.cols, minPoint.y + tmpl.rows)
				, Scalar(theRNG().uniform(0, 255), theRNG().uniform(0, 255), theRNG().uniform(0, 255)), 3, 8);
			imshow(showtitle, img_play);*/
			
			//Scalar::all(0)
			const Scalar& color = Scalar(rect_color_b, rect_color_g, rect_color_r);
			//坐标点的小数点位数
			int shift = 0;
			
			rectangle(img_play, loc, loc2, color, thickness, lineType, shift);
			imshow(tmplname, img_play);

			rectangle(dst, loc, loc2, color, thickness, lineType, shift);
			imshow("", dst);

			waitKey(0);
		}
	} catch(Exception e) {}
}
