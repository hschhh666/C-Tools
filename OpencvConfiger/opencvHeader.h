#pragma once


#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>

#if _DEBUG
#pragma comment(lib, "C:/opencv2/opencv/build/x86/vc14/lib/opencv_highgui2413d.lib")
#pragma comment(lib, "C:/opencv2/opencv/build/x86/vc14/lib/opencv_imgproc2413d.lib")
#pragma comment(lib, "C:/opencv2/opencv/build/x86/vc14/lib/opencv_core2413d.lib")
#pragma comment(lib, "C:/opencv2/opencv/build/x86/vc14/lib/opencv_calib3d2413d.lib")
#pragma comment(lib, "C:/opencv2/opencv/build/x86/vc14/lib/opencv_contrib2413d.lib")

#else
#pragma comment(lib, "C:/opencv2/opencv/build/x86/vc14/lib/opencv_highgui2413.lib")
#pragma comment(lib, "C:/opencv2/opencv/build/x86/vc14/lib/opencv_imgproc2413.lib")
#pragma comment(lib, "C:/opencv2/opencv/build/x86/vc14/lib/opencv_core2413.lib")
#pragma comment(lib, "C:/opencv2/opencv/build/x86/vc14/lib/opencv_contrib2413.lib")
#pragma comment(lib, "C:/opencv2/opencv/build/x86/vc14/lib/opencv_calib3d2413.lib")
#endif

