#include "myvideosurface.h"

MyVideoSurface::MyVideoSurface(QWidget *widget,int W,int H, QObject *parent) : QAbstractVideoSurface(parent)
{
    this->widget = widget;
    this->W = W;
    this->H = H;
}

QList<QVideoFrame::PixelFormat> MyVideoSurface::supportedPixelFormats(
        QAbstractVideoBuffer::HandleType handleType) const
{
    if (handleType == QAbstractVideoBuffer::NoHandle) {
        return QList<QVideoFrame::PixelFormat>()
                << QVideoFrame::Format_RGB24 //raspberry pi Format_RGB32不能用，會跳到 Format_ARGB32
                << QVideoFrame::Format_RGB32
                << QVideoFrame::Format_ARGB32
                << QVideoFrame::Format_ARGB32_Premultiplied
                << QVideoFrame::Format_RGB565
                << QVideoFrame::Format_RGB555;
    } else {
        return QList<QVideoFrame::PixelFormat>();
    }
}

bool MyVideoSurface::present(const QVideoFrame &frame)
{
    Q_UNUSED(frame);

    // Handle the frame and do your processing
    if (frame.isValid()) {
        currentFrame = frame;

        widget->repaint(); //通知外界的 widget 觸發 eventpaint 事件

        return true;
    }
    return false;
}

void MyVideoSurface::paintImage(QPainter *painter)
{
    //QVideoFrame 為可以抓取到內部記憶體中的圖之工具
    //map為，將VideoFrame內容映射至可授權的memory中
    //如果映射模式為WriteOnly，則原本的VideoFrame將會受到更改
    //當不再需要訪問數據時，請用unmap()函數釋放映射的memory
    if (currentFrame.map(QAbstractVideoBuffer::ReadOnly)) {

        QImage image(
                    currentFrame.bits(),
                    currentFrame.width(),
                    currentFrame.height(),
                    currentFrame.bytesPerLine(),
                    QVideoFrame::imageFormatFromPixelFormat(currentFrame.pixelFormat()));
        image = image.scaled(W,H);
        painter->drawImage(0,0,image);
        _currentImage = image;

        currentFrame.unmap();
    }
}

QImage MyVideoSurface::currentImage(){
    return _currentImage;
}