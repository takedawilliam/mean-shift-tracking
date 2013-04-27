#include "MeanShift.h"

//const char* FILENAME = "/media/sda4/OpenCV/Video test/Yulianti Maria Kristin (INA).avi"; 
//const char* FILENAME = "/media/sda4/OpenCV/Video test/badminton_indoor_vancouver.avi"; 
//const char* FILENAME = "/media/sda4/OpenCV/Video test/clip_01.avi";
const char* FILENAME = "/home/vu/test1";

void mouseHandler(int event, int x, int y, int flags, void* param);
Rect rect;
CvPoint p1, p2;
bool bMoveDown = false;
bool isDrawing = false;
bool bDrawingFinished = false;


int main() {
    VideoCapture capture(FILENAME);
    MeanShift ms;
    Mat frame, imgBuffer, imgShow;
    int delay = (int)(1000 / capture.get(CV_CAP_PROP_FPS));

    if (!capture.isOpened()) {
        cout << "Error reading video!" << endl;
        return 1;
    }
    
    namedWindow(FILENAME);
    capture >> frame;
    imgBuffer = imgShow = frame.clone();
    setMouseCallback(FILENAME, mouseHandler, &imgBuffer);

    while (1) {
        if (isDrawing) {
            frame.copyTo(imgBuffer);
            rectangle(imgBuffer, p1, p2, CV_RGB(255, 0, 0), 2);
        }
        imgBuffer.copyTo(imgShow);
        imshow(FILENAME, imgShow);
        if (bDrawingFinished || waitKey(delay) == 27)
            break;
    }
    
    namedWindow("BACK");
    Mat imgBackProject;
    if (bDrawingFinished) {
        rect.x = p1.x;
        rect.y = p1.y;
        rect.width = p2.x - p1.x;
        rect.height = p2.y - p1.y;
        while (1) {
            if (!capture.read(frame) || waitKey(delay) == 27)
                break;
        }
    }
    return 0;
}

void mouseHandler(int event, int x, int y, int flags, void* param) {
    Mat img = *((Mat*)param);

    switch (event) {
        case CV_EVENT_MOUSEMOVE:
            if (bMoveDown) {
                p2.x = x;
                p2.y = y;
                isDrawing = true;
            }
            break;
        case CV_EVENT_LBUTTONDOWN:
            if (!isDrawing) {
                bMoveDown = true;
                p1.x = x;
                p1.y = y;
            }
            break;
        case CV_EVENT_LBUTTONUP:
            bMoveDown = false;
            if (isDrawing) {
                bDrawingFinished = true;
                isDrawing = false;
            }
            break;
        case CV_EVENT_RBUTTONDOWN:
            break;
    }
}

