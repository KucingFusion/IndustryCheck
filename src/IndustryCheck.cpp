#include "IndustryCheck.h"

IndustryCheck::IndustryCheck(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui_IndustryCheck)
    , m_pcMyCamera(NULL)
    , m_isDeviceConnect(true)
    , m_captureModeFlag(true)
    , m_triggerModeFlag(true)
    , m_captureStateFlag(false)
    , m_captureStateBtn(true)
    , cv_processStateBtn(false)
    , cv_tempMarch(false)
    , binarizationThreshold(0)
    , cv_binaryState(false)
    , cv_morphology(false)
    , cannyThreshold1(0)
    , cannyThreshold2(0)
    , cv_canny(false)
    , contersArea(0)
    , contersLength(0)
    , cv_filter(false)
    , cv_geometricDetection(false)
    , cv_geometricCalculation(false)
    , stImageInfo({0})
    , debugnum(0)
{
    m_ImgDisplayThread = new ImgDisplayThread(*this);
    m_ImgProcessThread = new ImgProcessThread(*this);
    ui->setupUi(this);
    ui->textBrowser->append(QString("IndustryCheck GUI!"));
   
    //打开软件初始化过程
    init_MvSdk();                                                                                                                               //初始化SDK
    enum_Device();                                                                                                                              //枚举设备
    enum_captureMode();                                                                                                                         //枚举采集模式
    enum_triggerMode();                                                                                                                         //枚举触发模式
    m_ImgDisplayThread->start();
    m_ImgProcessThread->start();
                                                   
    connect(ui->connectDeviceBtn,    QOverload<bool>::of(&QPushButton::clicked),            this, &IndustryCheck::slot_connect_Device           );  //打开或关闭设备
    connect(ui->captureModecomboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),   this, &IndustryCheck::slot_capture_Mode             );  //采集模式设置
    connect(ui->triggerModecomboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),   this, &IndustryCheck::slot_trigger_Mode             );  //触发模式设置
    connect(ui->captureStateBtn,     QOverload<bool>::of(&QPushButton::clicked),            this, &IndustryCheck::slot_capture_State            );  //图像采集
    connect(ui->saveParameterBtn,    QOverload<bool>::of(&QPushButton::clicked),            this, &IndustryCheck::slot_process_State            );  //图像处理 
    connect(ui->settempRoiBtn,       QOverload<bool>::of(&QPushButton::clicked),            this, &IndustryCheck::slot_setTemp_ROI              );  //设置图像模板ROI
    connect(ui->tempMatchRoi,        QOverload<bool>::of(&QPushButton::clicked),            this, &IndustryCheck::slot_tempMarch_ROI            );  //匹配图像模板ROI
    connect(ui->binarizationSlider,  QOverload<int>::of(&QSlider::valueChanged),            this, &IndustryCheck::slot_binarization_parameters  );  //二值化处理
    connect(ui->binarizationSlider,  QOverload<>::of(&QSlider::sliderReleased), [=](){
        cv_binaryState = true;
        ui->textBrowser->append(QString("QSlider release"));
    });
    connect(ui->morphkernalSlider,   QOverload<int>::of(&QSlider::valueChanged),            this, &IndustryCheck::slot_morphology_operation     );  //形态学处理
    connect(ui->morphkernalSlider,   QOverload<>::of(&QSlider::sliderReleased), [=](){
        cv_morphology = true;
        ui->textBrowser->append(QString("QSlider release"));
    });
    connect(ui->cannyEditNum1,       QOverload<>::of(&QLineEdit::returnPressed),            this, &IndustryCheck::slot_canny_detrction          );  //canny边缘检测阈值1改变
    connect(ui->cannyEditNum2,       QOverload<>::of(&QLineEdit::returnPressed),            this, &IndustryCheck::slot_canny_detrction          );  //canny边缘检测阈值2改变
    connect(ui->contoursLengthEdit,  QOverload<>::of(&QLineEdit::returnPressed),            this, &IndustryCheck::slot_filtered_contours        );  //过滤轮廓长度
    connect(ui->contoursAreaEdit,    QOverload<>::of(&QLineEdit::returnPressed),            this, &IndustryCheck::slot_filtered_contours        );  //过滤轮廓面积
    connect(ui->detectionBtn,        QOverload<bool>::of(&QPushButton::clicked),            this, &IndustryCheck::slot_geometric_detection      );  //打开或关闭设备
    connect(ui->calculationBtn,      QOverload<bool>::of(&QPushButton::clicked),            this, &IndustryCheck::slot_geometric_calculation    );  //打开或关闭设备


}

IndustryCheck::~IndustryCheck()
{
    release_MvSdk();
    m_ImgDisplayThread->quit();
    m_ImgProcessThread->quit();
    // m_ImgDisplayThread->wait();
    // m_ImgProcessThread->wait();
    delete m_ImgDisplayThread;
    delete m_ImgProcessThread;
    delete cropWidget;
    delete m_pcMyCamera;
    delete ui; 
}

void IndustryCheck::init_MvSdk()                                        //初始化SDK
{
    int nRet = MV_CC_Initialize();
    if (MV_OK != nRet)
    {
        ui->textBrowser->append(QString("Initialize SDK fail!"));
        return;
    }
    else{
        ui->textBrowser->append(QString("Initialize SDK success!"));
    }

}

void IndustryCheck::release_MvSdk()                                     //释放SDK
{
    MV_CC_Finalize();
    ui->textBrowser->append(QString("release SDK ok!"));
    sleep(3);
}

void IndustryCheck::enum_Device()                                       //ch:枚举设备 | en:Enum device
{
    QString strMsg;
    ui->deviceComboBox->clear();

    memset(&m_stDevList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
    int nRet = CMvCamera::EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &m_stDevList);
    if (MV_OK != nRet)
    {
        ui->textBrowser->append(QString("Enum Devices fail! nRet = %1").arg(nRet));
        return;
    }
    else{
        ui->textBrowser->append(QString("Enum Devices OK! nRet = %1").arg(nRet));
    }

    for (unsigned int i = 0; i < m_stDevList.nDeviceNum; i++)
    {
         MV_CC_DEVICE_INFO* pDeviceInfo = m_stDevList.pDeviceInfo[i];
        if (NULL == pDeviceInfo)
        {
            continue;
        }

        if (pDeviceInfo->nTLayerType == MV_GIGE_DEVICE)
        {
            int nIp1 = ((m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
            int nIp2 = ((m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
            int nIp3 = ((m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
            int nIp4 = (m_stDevList.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff);

            char strUserName[256] = {0};
            sprintf_s(strUserName, 256, "%s %s (%s)", pDeviceInfo->SpecialInfo.stGigEInfo.chManufacturerName,
                      pDeviceInfo->SpecialInfo.stGigEInfo.chModelName,
                      pDeviceInfo->SpecialInfo.stGigEInfo.chSerialNumber);

            QString  UserName(strUserName);

            strMsg= QString("[%1]GigE: %2  %3.%4.%5.%6")
                         .arg( QString::number(i)).
                     arg(strUserName).
                     arg(QString::number(nIp1)).
                     arg(QString::number(nIp2)).
                     arg(QString::number(nIp3)).
                     arg( QString::number(nIp4));
            ui->deviceComboBox->addItem(strMsg);
        }
    }

    if (0 == m_stDevList.nDeviceNum)
    {
        ui->textBrowser->append(QString("Find No devices!"));
        return;
    }
    ui->deviceComboBox->setCurrentIndex(0); //ComboBox设备默认选择第一个

}

void IndustryCheck::slot_connect_Device()                               //连接或关闭设备
{
    if(m_isDeviceConnect)
    {
        //打开设备
        if(open_Device() == MV_OK)
        {
            ui->connectDeviceBtn->setText("关闭");
            m_isDeviceConnect = false;
        }  
    }
    else
    {
        //关闭设备
        if(close_Device() == MV_OK)
        {
            ui->connectDeviceBtn->setText("打开");
            m_isDeviceConnect = true;
        }
    }
}

int IndustryCheck::open_Device()                                        //按下打开设备按钮
{
    m_pcMyCamera = new CMvCamera;
    if (m_pcMyCamera == nullptr)
    {
        ui->textBrowser->append(QString("Failed to create camera instance!"));
        return -1;
    }

    int nIndex = ui->deviceComboBox->currentIndex();                    // 获取comboBox控件当前选中索引
    int nRet = m_pcMyCamera->Open(m_stDevList.pDeviceInfo[nIndex]);

    if (MV_OK != nRet)
    {
        delete m_pcMyCamera;
        m_pcMyCamera = NULL;
        ui->textBrowser->append(QString("Device Open error!"));
        return -1;
    }
    else{
        ui->textBrowser->append(QString("Device Open success!"));
        return MV_OK;
    }

     // ch:探测网络最佳包大小(只对GigE相机有效) | en:Detection network optimal package size(It only works for the GigE camera)
    if (m_stDevList.pDeviceInfo[nIndex]->nTLayerType == MV_GIGE_DEVICE)
    {
        unsigned int nPacketSize = 0;
        nRet = m_pcMyCamera->GetOptimalPacketSize(&nPacketSize);
        if (nRet == MV_OK)
        {
            nRet = m_pcMyCamera->SetIntValue("GevSCPSPacketSize",nPacketSize);
            if(nRet != MV_OK)
            {
                ui->textBrowser->append(QString("Warning: Set Packet Size fail!"));
            }
        }
        else
        {
            ui->textBrowser->append(QString("Warning: Get Packet Size fail!"));
        }
    }
}

int IndustryCheck::close_Device()                                       //按下关闭设备按钮
{
    int nRet = m_pcMyCamera->Close();
    if (nRet == MV_OK)
    {
        delete m_pcMyCamera;
        m_pcMyCamera = NULL;
        ui->textBrowser->append(QString("Device Close success!"));
        return MV_OK;
    }
    else{
        ui->textBrowser->append(QString("Device Close error!"));
        return -1;
    }
}

void IndustryCheck::enum_captureMode()                                  //枚举采集模式
{
    ui->captureModecomboBox->addItem("  连续采集  ");
    ui->captureModecomboBox->addItem("  单帧采集  ");
}

void IndustryCheck::slot_capture_Mode()                                 //设置采集模式
{
    if(ui->captureModecomboBox->currentIndex() == 0)
    {
        ui->textBrowser->append(QString("当前选择：连续采集模式"));
        m_captureModeFlag = true;                                       //采集模式标志位ture
        ui->triggerModecomboBox->setEnabled(false);                     //连续采集模式下触发模式不可设置
        ui->triggerModecomboBox->setStyleSheet("color:gray");           //设置触发模式列表变灰色
    }
    else if(ui->captureModecomboBox->currentIndex() == 1)
    {
        ui->textBrowser->append(QString("当前选择：单帧采集模式"));
        m_captureModeFlag = false;                                      //采集模式标志位false
        ui->triggerModecomboBox->setEnabled(true);                      //单帧模式下可选择触发模式
        ui->triggerModecomboBox->setStyleSheet("color:black");          //设置触发模式列表变灰色
    }
}

void IndustryCheck::enum_triggerMode()                                  //枚举触发模式
{
    ui->triggerModecomboBox->addItem("  软触发  ");
    ui->triggerModecomboBox->addItem("  硬触发  ");
    ui->triggerModecomboBox->setEnabled(false);                         //连续采集模式下触发模式不可设置
    ui->triggerModecomboBox->setStyleSheet("color:gray");               //设置触发模式列表变灰色
}

void IndustryCheck::slot_trigger_Mode()                                 //设置触发模式(采集模式设置为单帧采集时才可以设置触发模式)
{
    if(m_captureModeFlag == false && ui->triggerModecomboBox->currentIndex() == 0)
    {
        ui->textBrowser->append(QString("当前选择：软触发模式"));
        m_triggerModeFlag = true;
    }
    else if(m_captureModeFlag == false && ui->triggerModecomboBox->currentIndex() == 1)
    {
        ui->textBrowser->append(QString("当前选择：硬触发模式"));
        m_triggerModeFlag = false;
    }
}

void IndustryCheck::slot_capture_State()                                //图像采集
{
    ui->textBrowser->append(QString("captureModeFlag: %1, triggerModeFlag: %2").arg(m_captureModeFlag).arg(m_triggerModeFlag)); //debug标志位
    int iRet = MV_OK;

    if(m_captureStateBtn)
    {
        //连续采集不触发
        if(m_captureModeFlag == true)
        {
            int iRet = m_pcMyCamera->SetEnumValue("AcquisitionMode", 2);//设置采集模式为连续采集
            MV_OK != iRet ? ui->textBrowser->append(QString("连续采集模式: error code : %1").arg(iRet)) : ui->textBrowser->append(QString("连续采集模式设置成功")) ;
            iRet = m_pcMyCamera->SetEnumValue("TriggerMode", 0);        //触发模式off
            MV_OK != iRet ? ui->textBrowser->append(QString("关闭触发模式: error code : %1").arg(iRet)) : ui->textBrowser->append(QString("关闭触发模式成功")) ;
            
            ui->captureModecomboBox->setEnabled(false);
            ui->captureModecomboBox->setStyleSheet("color:gray");
            ui->triggerModecomboBox->setEnabled(false);
            ui->triggerModecomboBox->setStyleSheet("color:gray");

            iRet =  m_pcMyCamera->StartGrabbing();
            if (MV_OK == iRet)
            {
                ui->textBrowser->append(QString("开始连续取流"));
                m_captureStateFlag = true;                              //开始采集线程信号
            }
            
            //设置ui按钮为结束
            ui->captureStateBtn->setText("结束采集");
            m_captureStateBtn = false;
        }
        //单帧采集软触发
        else if(m_captureModeFlag == false && m_triggerModeFlag == true)
        {
            int iRet = m_pcMyCamera->SetEnumValue("AcquisitionMode", 0);   //设置采集模式为单帧采集
            MV_OK != iRet ? ui->textBrowser->append(QString("单帧采集模式: error code : %1").arg(iRet)) : ui->textBrowser->append(QString("单帧采集模式设置成功")) ;
            iRet = m_pcMyCamera->SetEnumValue("TriggerSource", 7);      //软触发
            MV_OK != iRet ? ui->textBrowser->append(QString("软触发:error code : %1").arg(iRet)) : ui->textBrowser->append(QString("软触发设置成功")) ;

            iRet =  m_pcMyCamera->StartGrabbing();
            if (MV_OK == iRet)
            {
                ui->textBrowser->append(QString("开始单帧取流"));
                m_captureStateFlag = true;
            }
            sleep(1);//取流一秒，保存最后一帧
            
            iRet = m_pcMyCamera->StopGrabbing();
            if(MV_OK == iRet)
            {
                m_captureStateFlag = false;
                ui->textBrowser->append(QString("停止单帧取流"));
            }
        }
        //单帧采集硬触发(暂不处理)
        else if(m_captureModeFlag == false && m_triggerModeFlag == false)
        {
            // int iRet = m_pcMyCamera->SetEnumValue("AcquisitionMode ", 0);   //设置采集模式为单帧采集
            // MV_OK != iRet ? ui->textBrowser->append(QString("error code : %1").arg(iRet)) : ui->textBrowser->append(QString("单帧采集模式")) ;
            // iRet = m_pcMyCamera->SetEnumValue("TriggerMode", 1);   //触发模式on
            // MV_OK != iRet ? ui->textBrowser->append(QString("error code : %1").arg(iRet)) : ui->textBrowser->append(QString("打开触发模式")) ;
            // iRet = m_pcMyCamera->SetEnumValue("TriggerSource", 4);   //硬触发：计数器触发
            // MV_OK != iRet ? ui->textBrowser->append(QString("error code : %1").arg(iRet)) : ui->textBrowser->append(QString("硬触发")) ;
        }
    
    }
    else
    {
        //结束采集 
        ui->captureModecomboBox->setEnabled(true);
        ui->captureModecomboBox->setStyleSheet("color:black");

        

        int iRet =  m_pcMyCamera->StopGrabbing();
        if (MV_OK == iRet)
        {
            m_captureStateFlag = false;         //停止采集线程信号
            ui->textBrowser->append(QString("停止连续取流"));
        }

        ui->captureStateBtn->setText("开始采集");
        m_captureStateBtn = true;
        
    }
}

void IndustryCheck::slot_setTemp_ROI()                                  //设置图像模板ROI
{
    cropWidget = new cropbox(*this);
    cropWidget->setAttribute(Qt::WA_DeleteOnClose, true);
    cropWidget->show();
}

void IndustryCheck::slot_process_State() // 图像处理
{
    if (cv_processStateBtn == true)
    {
        ui->saveParameterBtn->setText("设置参数");
        ui->binarizationSlider->setEnabled(false);
        ui->morphkernalSlider->setEnabled(false);
        ui->cannyEditNum1->setEnabled(false);
        ui->cannyEditNum2->setEnabled(false);
        ui->contoursLengthEdit->setEnabled(false);
        ui->contoursAreaEdit->setEnabled(false);
        ui->tempMatchRoi->setEnabled(false);
        ui->textBrowser->append(QString("保存参数sucess!"));
        cv_processStateBtn = false;
    }
    else{
        ui->saveParameterBtn->setText("保存参数");
        ui->binarizationSlider->setEnabled(true);
        ui->morphkernalSlider->setEnabled(true);
        ui->cannyEditNum1->setEnabled(true);
        ui->cannyEditNum2->setEnabled(true);
        ui->contoursLengthEdit->setEnabled(true);
        ui->contoursAreaEdit->setEnabled(true);
        ui->tempMatchRoi->setEnabled(true);
        ui->textBrowser->append(QString("设置参数ing..."));

        //按下设置参数按钮保存最后一帧图像并装换成Mat类型，后续以该图像进行调参
        cvprocessImage = cv::Mat(displayImage.height(),
                                displayImage.width(),
                                CV_8UC1,
                                displayImage.bits(),
                                displayImage.bytesPerLine());
        qDebug("cv_PRO:%d, %d", cvprocessImage.cols, cvprocessImage.rows);
        //将框选的ROI（qcvROI）转换成Mat类型
        cvtempRoi = cv::Mat(qcvROI.height(),
                        qcvROI.width(),
                        CV_8UC1,
                        qcvROI.bits(),
                        qcvROI.bytesPerLine());
        qDebug("cv_ROI:%d, %d", cvtempRoi.cols, cvtempRoi.rows);

        cv_processStateBtn = true;
    }
}

void IndustryCheck::slot_tempMarch_ROI()                                //匹配模板ROI
{
    cv_tempMarch = true;
}

void IndustryCheck::slot_binarization_parameters(int index)             //二值化处理
{
    ui->binarizationthresholdNum->setNum(index);
    binarizationThreshold = index; 
}

void IndustryCheck::slot_morphology_operation(int index)                //形态学操作
{
    ui->morphkernalNum->setNum(index);
    kernelIndex = index;
}

void IndustryCheck::slot_canny_detrction()                              //Canny边缘检测
{
    cannyThreshold1 = (ui->cannyEditNum1->text()).toInt();
    cannyThreshold2 = (ui->cannyEditNum2->text()).toInt();
    cv_canny = true;
    ui->textBrowser->append(QString("cannyThreshold1 = %1, cannyThreshold2 = %2!").arg(cannyThreshold1).arg(cannyThreshold2));
}

void IndustryCheck::slot_filtered_contours()                            //过滤轮廓
{
    contersLength = (ui->contoursLengthEdit->text().toDouble());
    contersArea   = (ui->contoursAreaEdit->text().toDouble());
    cv_filter = true;
    ui->textBrowser->append(QString("set filter Length = %1 Area = %2").arg(contersLength).arg(contersArea));
}

void IndustryCheck::slot_geometric_detection()                          //几何检测
{
    cv_geometricDetection = true;
}

void IndustryCheck::slot_geometric_calculation()                        //几何计算
{
    cv_geometricCalculation = true;
}
