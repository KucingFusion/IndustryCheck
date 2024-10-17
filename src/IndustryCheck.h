#pragma once
#include <iostream>
#include "stdio.h"
#include <unistd.h>

#include "ui_IndustryCheck.h"

#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <QLabel>
#include <QPainter>
#include <QPen>
#include <QRect>
#include <QMouseEvent>

#include <opencv2/opencv.hpp>

#include "MvCamera.h"
#include "MvCameraControl.h"

#include "myThread.h"
#include "cropbox.h"
#include "cropRoi.h"

struct lineStruct
{
    cv::Point  plineStart, plineEnd;
};

struct circleStruct
{
    cv::Point2f  pcircelCenter;
    float circleRadius;
};

class IndustryCheck : public QWidget 
{
    friend class ImgDisplayThread;
    friend class ImgProcessThread;
    Q_OBJECT
    
public:
    IndustryCheck(QWidget* parent = nullptr);
    ~IndustryCheck();

    void init_MvSdk();                                              //初始化sdk
    void release_MvSdk();                                           //释放sdk
    void enum_Device();                                             //枚举设备
    void enum_captureMode();                                        //枚举采集模式
    void enum_triggerMode();                                        //枚举触发模式

    int open_Device();                                              //打开设备
    int close_Device();                                             //关闭设备

private slots:
    void slot_connect_Device();                                     //设备连接状态
    void slot_capture_Mode();                                       //设置采集模式
    void slot_trigger_Mode();                                       //设置触发模式
    void slot_capture_State();                                      //图像采集状态
    void slot_setTemp_ROI();                                        //设置图像模板ROI

    void slot_tempMarch_ROI();
    void slot_process_State();                                      //图像调参状态
    void slot_binarization_parameters(int index);                   //二值化调参
    void slot_morphology_operation(int index);                      //形态学操作
    void slot_canny_detrction();                                    //Canny边缘检测
    void slot_filtered_contours();                                  //过滤轮廓

    void slot_geometric_detection();                                //几何检测
    void slot_geometric_calculation();                              //几何计算

public:

    MV_FRAME_OUT                                stImageInfo = {0};                      //图像结构体，输出图像地址及图像信息 
    QImage                                      displayImage;                           //图像显存
    cv::Mat                                     cvprocessImage;                         //存放处理后的图像
    QImage                                      qcvROI;                                 //框选操作的ROI图像 Qimage类型
    cv::Mat                                     cvtempRoi;                              //框选操作的ROI图像 Mat类型
    cv::Mat                                     marchRoi;                               //匹配ROI后的图像
    cv::Mat                                     threshold;                              //二值化阈值处理后的图像
    cv::Mat                                     morph;                                  //形态学操作处理后的图像   
    cv::Mat                                     canny;                                  //canny操作处理后的图像
    std::vector<std::vector<cv::Point>>         contours;                               //将过滤操作处理前的轮廓
    std::vector<std::vector<cv::Point>>         filterContours;                         //将过滤操作处理前的轮廓
    cv::Mat                                     filterContoursImg;                      //将过滤操作处理后的轮廓图像
    cv::Mat                                     geometricDetectionImg;                  //几何检测后拟合的图片
    int debugnum;


private:
    Ui_IndustryCheck*                           ui;

    MV_CC_DEVICE_INFO_LIST                      m_stDevList;                            //保存设备信息的链表
    CMvCamera*                                  m_pcMyCamera;                           //用于操作相机的指针

    bool                                        m_isDeviceConnect;                      //是否连接到设备
    bool                                        m_captureModeFlag;                      //采集模式标志位        true：连续采集 false：单帧采集
    bool                                        m_triggerModeFlag;                      //触发模式标志位        ture：软触发   false：硬触发
    bool                                        m_captureStateFlag;                     //采集状态标志位        ture：开始     false：结束
    bool                                        m_captureStateBtn;                      //采集按钮状态          ture：开始     false：结束

    //图像处理参数
    bool                                        cv_processStateBtn;                     //图像处理按钮标志位

    bool                                        cv_tempMarch;                           //模板匹配
    uint8_t                                     binarizationThreshold;                  //二值化阈值
    bool                                        cv_binaryState;                         //二值化处理标志位      true：开始 flase：结束
    cv::Mat                                     kernel;                                 //形态学核心
    int                                         kernelIndex;                            //结构元素大小
    bool                                        cv_morphology;                          //形态学处理标志位      true：开始
    int                                         cannyThreshold1, cannyThreshold2;       //canny阈值
    bool                                        cv_canny;                               //canny边缘检测处理标志位 true：开始
    double                                      contersLength, contersArea;             //过滤轮廓面积
    bool                                        cv_filter;                              //过滤轮廓处理标志位     true：开始 flase：结束
    bool                                        cv_geometricDetection;                  //几何检测标志位
    bool                                        cv_geometricCalculation;                //几何计算标志位
    
    lineStruct                                  line[12];
    circleStruct                                circle[12];

    std::vector<cv::Vec4f>                      lineParams;                             // 存放直线的参数
    std::vector<std::pair<cv::Point2f, float>>  circleParams;                           // 存放圆的参数（中心，半径）

    ImgDisplayThread*                           m_ImgDisplayThread;                     //图像显示线程句柄
    ImgProcessThread*                           m_ImgProcessThread;                     //图像处理线程句柄
    cropbox*                                    cropWidget;


};
