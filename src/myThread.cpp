#include "mythread.h"
#include "IndustryCheck.h"
#include "ui_IndustryCheck.h"
#include "MvCamera.h"

//直线到圆的距离
double lineToCircleDistance(cv::Vec4f lineParams, cv::Point2f circleCenter, float radius) {
    // 直线方程 Ax + By + C = 0
    double A = lineParams[1]; // 直线的斜率系数
    double B = -lineParams[0]; // 直线的 x 系数（斜率）
    double C = -(A * lineParams[2] + B * lineParams[3]); // 直线的截距

    // 圆心到直线的距离
    double distance = fabs(A * circleCenter.x + B * circleCenter.y + C) / sqrt(A * A + B * B);

    // 返回距离减去半径，得到直线到圆的最近距离
    return distance - radius;
}

//图像显示线程
ImgDisplayThread::ImgDisplayThread(IndustryCheck&m_industrycheck_, QObject *parent)
    : QThread{parent}
    ,m_industrycheck(m_industrycheck_)
{

}

void ImgDisplayThread::run()
{
    MV_FRAME_OUT stImageInfo = {0};
    //QImage displayImage;
    memset(&stImageInfo, 0, sizeof(MV_FRAME_OUT));
    int nRet = MV_OK; 
    int i = 0;
    m_industrycheck.ui->textBrowser->append(QString("ImgProcessThread running ..."));

    while (1)
    {
        //采集状态标志位开启
        if(m_industrycheck.m_captureStateFlag == true)
        {
            //检测是否接受到新ImageBuffer
            nRet = m_industrycheck.m_pcMyCamera->GetImageBuffer(&m_industrycheck.stImageInfo, 1000);
            if(nRet == MV_OK)
            {
                // 创建 QImage，确保数据格式正确
                m_industrycheck.displayImage = QImage(m_industrycheck.stImageInfo.pBufAddr, m_industrycheck.stImageInfo.stFrameInfo.nWidth, m_industrycheck.stImageInfo.stFrameInfo.nHeight, QImage::Format_Grayscale8);
                // 将 QImage 转换为 QPixmap
                QPixmap pim = QPixmap::fromImage(m_industrycheck.displayImage);

                // 获取 label 的大小并缩放 pixmap，保持宽高比
                QSize labelSize = m_industrycheck.ui->label->size();
                QPixmap scaledPixmap = pim.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

                // 设置缩放后的 pixmap 到 label
                m_industrycheck.ui->label->setPixmap(scaledPixmap);
                m_industrycheck.ui->label->update();  // 更新显示

                nRet = m_industrycheck.m_pcMyCamera->FreeImageBuffer(&m_industrycheck.stImageInfo);
                if (nRet != MV_OK)
                {
                    m_industrycheck.ui->textBrowser->append(QString("Free buf fail!"));
                }          
            }
        }
    }
}


//图像处理线程
ImgProcessThread::ImgProcessThread(IndustryCheck&m_industrycheck_, QObject *parent)
    : QThread{parent}
    ,m_industrycheck(m_industrycheck_)
{

}

void ImgProcessThread::run()
{
    //图像处理调参
    m_industrycheck.ui->textBrowser->append(QString("ImgProcessThread running ..."));
    while (1)
    {
        /* code */
        if (m_industrycheck.cv_tempMarch == true)                   //模板匹配
        {
            cv::Mat result(m_industrycheck.cvprocessImage.cols - m_industrycheck.cvtempRoi.cols + 1, m_industrycheck.cvprocessImage.rows - m_industrycheck.cvtempRoi.rows + 1, CV_8UC1);      // 创建结果图像，尺寸要足够大以容纳匹配结果
            cv::matchTemplate(m_industrycheck.cvprocessImage, m_industrycheck.cvtempRoi, result, cv::TM_CCOEFF_NORMED);    // 执行模板匹配
            cv::normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());    // 归一化结果图像
            // 找到最佳匹配的位置
            double minVal, maxVal;
            cv::Point minLoc, maxLoc, matchLoc;
            cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
            // 对于 cv::TM_CCOEFF_NORMED，最大值是最佳匹配
            matchLoc = maxLoc;
            cv::rectangle(m_industrycheck.cvprocessImage, matchLoc, cv::Point(matchLoc.x + m_industrycheck.cvtempRoi.cols, matchLoc.y + m_industrycheck.cvtempRoi.rows), cv::Scalar(255, 255, 255), 2);
            m_industrycheck.marchRoi = m_industrycheck.cvprocessImage(cv::Range(matchLoc.y + 2, matchLoc.y + m_industrycheck.cvtempRoi.rows - 2), cv::Range(matchLoc.x + 2, matchLoc.x + m_industrycheck.cvtempRoi.cols - 2));
            
            // 创建 QImage，确保数据格式正确
            QImage img(m_industrycheck.marchRoi.data,
                        m_industrycheck.marchRoi.cols,
                        m_industrycheck.marchRoi.rows,
                        m_industrycheck.marchRoi.step,
                        QImage::Format_Grayscale8);
            // 将 QImage 转换为 QPixmap
            QPixmap pim = QPixmap::fromImage(img);
            // 获取 label 的大小并缩放 pixmap，保持宽高比
            QSize labelSize = m_industrycheck.ui->label->size();
            QPixmap scaledPixmap = pim.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            // 设置缩放后的 pixmap 到 label
            m_industrycheck.ui->label->setPixmap(scaledPixmap);
            m_industrycheck.ui->label->update();  // 更新显示

            m_industrycheck.cv_tempMarch = false;
        }
        if(m_industrycheck.cv_binaryState == true)                  //二值化处理
        {
            cv::threshold(m_industrycheck.marchRoi, m_industrycheck.threshold, m_industrycheck.binarizationThreshold, 255, cv::THRESH_BINARY);
            
            // 创建 QImage，确保数据格式正确
            QImage img(m_industrycheck.threshold.data,
                        m_industrycheck.threshold.cols,
                        m_industrycheck.threshold.rows,
                        m_industrycheck.threshold.step,
                        QImage::Format_Grayscale8);
            // 将 QImage 转换为 QPixmap
            QPixmap pim = QPixmap::fromImage(img);
            // 获取 label 的大小并缩放 pixmap，保持宽高比
            QSize labelSize = m_industrycheck.ui->label->size();
            QPixmap scaledPixmap = pim.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            // 设置缩放后的 pixmap 到 label
            m_industrycheck.ui->label->setPixmap(scaledPixmap);
            m_industrycheck.ui->label->update();  // 更新显示

            m_industrycheck.cv_binaryState = false; 
        }

        if (m_industrycheck.cv_morphology == true)                  //形态学操作
        {
            m_industrycheck.kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(m_industrycheck.kernelIndex, m_industrycheck.kernelIndex));//结构元素
            cv::morphologyEx(m_industrycheck.threshold, m_industrycheck.morph, cv::MORPH_OPEN, m_industrycheck.kernel);

            // 创建 QImage，确保数据格式正确
            QImage img(m_industrycheck.morph.data,
                        m_industrycheck.morph.cols,
                        m_industrycheck.morph.rows,
                        m_industrycheck.morph.step,
                        QImage::Format_Grayscale8);
            // 将 QImage 转换为 QPixmap
            QPixmap pim = QPixmap::fromImage(img);
            // 获取 label 的大小并缩放 pixmap，保持宽高比
            QSize labelSize = m_industrycheck.ui->label->size();
            QPixmap scaledPixmap = pim.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            // 设置缩放后的 pixmap 到 label
            m_industrycheck.ui->label->setPixmap(scaledPixmap);
            m_industrycheck.ui->label->update();  // 更新显示

            m_industrycheck.cv_morphology = false;
        }

        if (m_industrycheck.cv_canny == true)                       //canny操作
        {
            cv::Canny(m_industrycheck.morph, m_industrycheck.canny, m_industrycheck.cannyThreshold1, m_industrycheck.cannyThreshold2);
            
            // 创建 QImage，确保数据格式正确
            QImage img(m_industrycheck.canny.data,
                        m_industrycheck.canny.cols,
                        m_industrycheck.canny.rows,
                        m_industrycheck.canny.step,
                        QImage::Format_Grayscale8);
            // 将 QImage 转换为 QPixmap
            QPixmap pim = QPixmap::fromImage(img);
            // 获取 label 的大小并缩放 pixmap，保持宽高比
            QSize labelSize = m_industrycheck.ui->label->size();
            QPixmap scaledPixmap = pim.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            // 设置缩放后的 pixmap 到 label
            m_industrycheck.ui->label->setPixmap(scaledPixmap);
            m_industrycheck.ui->label->update();  // 更新显示

            m_industrycheck.cv_canny = false;
        } 

        if(m_industrycheck.cv_filter == true)                       //过滤轮廓处理
        {
            cv::findContours(m_industrycheck.canny, m_industrycheck.contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
            // 清空过滤后的轮廓容器，以确保它是空的
            m_industrycheck.filterContours.clear();
            // 遍历轮廓并过滤
            for (const auto& contour : m_industrycheck.contours)
            {
                // 检查面积和周长是否符合阈值
                if(cv::contourArea(contour) > m_industrycheck.contersArea || cv::arcLength(contour, false) > m_industrycheck.contersLength)
                {
                    
                    m_industrycheck.filterContours.push_back(contour);// 将符合条件的轮廓添加到新容器中
                }
            }
            qDebug("过滤后轮廓数量:%d", m_industrycheck.filterContours.size());
            // 绘制过滤后的轮廓
            m_industrycheck.filterContoursImg = cv::Mat::zeros(m_industrycheck.canny.size(), m_industrycheck.canny.type());
            cv::drawContours(m_industrycheck.filterContoursImg, m_industrycheck.filterContours, -1, cv::Scalar(255, 255, 255), 1);

            // 创建 QImage，确保数据格式正确
            QImage img(m_industrycheck.filterContoursImg.data,
                        m_industrycheck.filterContoursImg.cols,
                        m_industrycheck.filterContoursImg.rows,
                        m_industrycheck.filterContoursImg.step,
                        QImage::Format_Grayscale8);
            // 将 QImage 转换为 QPixmap
            QPixmap pim = QPixmap::fromImage(img);
            // 获取 label 的大小并缩放 pixmap，保持宽高比
            QSize labelSize = m_industrycheck.ui->label->size();
            QPixmap scaledPixmap = pim.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            // 设置缩放后的 pixmap 到 label
            m_industrycheck.ui->label->setPixmap(scaledPixmap);
            m_industrycheck.ui->label->update();  // 更新显示

            m_industrycheck.cv_filter = false;
        }

        if (m_industrycheck.cv_geometricDetection == true)          //几何检测
        {
            //cv::cvtColor(m_industrycheck.marchRoi, m_industrycheck.geometricDetectionImg, cv::COLOR_GRAY2RGB); 
            m_industrycheck.geometricDetectionImg = cv::Mat::zeros(m_industrycheck.filterContoursImg.size(), m_industrycheck.filterContoursImg.type());
            std::vector<std::vector<cv::Point>> lineContours;  // 存放近似直线的轮廓
            std::vector<std::vector<cv::Point>> circleContours; // 存放近似圆的轮廓
            m_industrycheck.lineParams.clear();
            m_industrycheck.circleParams.clear();
            // 分类轮廓
            for (const auto& contour : m_industrycheck.filterContours) {
                // 轮廓的简化
                std::vector<cv::Point> approx;
                double epsilon = cv::arcLength(contour, true); // 根据轮廓周长设置逼近精度
                cv::approxPolyDP(contour, approx, 0.02 * epsilon, true); // 逼近轮廓
                // 轮廓的角点数量
                int vertexCount = approx.size();

                if (vertexCount == 2) {
                    // 近似直线
                    lineContours.push_back(contour);
                } else if (vertexCount > 2) {
                    // 近似圆
                    circleContours.push_back(contour);
                }
            }

            int lineNum = 0, circleNum = 0;
            // 拟合直线
            for (const auto& contour : lineContours) {
                cv::Vec4f lineParams;
                cv::fitLine(contour, lineParams, cv::DIST_L2, 0, 0.01, 0.01);
                m_industrycheck.lineParams.push_back(lineParams);

                // 根据拟合结果绘制直线
                cv::Point2f pointOnLine(lineParams[2], lineParams[3]);
                cv::Point2f direction(lineParams[0], lineParams[1]);

                cv::Point pt1 = pointOnLine - 1000 * cv::Point2f(direction);
                cv::Point pt2 = pointOnLine + 1000 * cv::Point2f(direction);

                cv::putText(m_industrycheck.geometricDetectionImg, "line" + std::to_string(lineNum), pt2, cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(255,255,255), 2);
                cv::line(m_industrycheck.geometricDetectionImg, pt1, pt2, cv::Scalar(255, 255, 255), 2); // 用绿色绘制直线
            
                lineNum++;
            }

            // 拟合圆
            for (const auto& contour : circleContours) {
                cv::Point2f center;
                float radius;
                cv::minEnclosingCircle(contour, center, radius);
                m_industrycheck.circleParams.emplace_back(center, radius);

                cv::putText(m_industrycheck.geometricDetectionImg, "circle" + std::to_string(circleNum), center, cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(255,255,255), 2);
                cv::circle(m_industrycheck.geometricDetectionImg, center, cvRound(radius), cv::Scalar(255, 255, 255), 2); // 用蓝色绘制圆
                
                circleNum++;
            }
            // 创建 QImage，确保数据格式正确
            QImage img(m_industrycheck.geometricDetectionImg.data,
                        m_industrycheck.geometricDetectionImg.cols,
                        m_industrycheck.geometricDetectionImg.rows,
                        m_industrycheck.geometricDetectionImg.step,
                        QImage::Format_Grayscale8);
            // 将 QImage 转换为 QPixmap
            QPixmap pim = QPixmap::fromImage(img);
            // 获取 label 的大小并缩放 pixmap，保持宽高比
            QSize labelSize = m_industrycheck.ui->label->size();
            QPixmap scaledPixmap = pim.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            // 设置缩放后的 pixmap 到 label
            m_industrycheck.ui->label->setPixmap(scaledPixmap);
            m_industrycheck.ui->label->update();  // 更新显示

            m_industrycheck.cv_geometricDetection = false;
        } 
        
        if(m_industrycheck.cv_geometricCalculation == true)
        {
            // 计算每条直线到每个圆的距离
            for (const auto& line : m_industrycheck.lineParams) {
                for (const auto& circle : m_industrycheck.circleParams) {
                    double distance = lineToCircleDistance(line, circle.first, circle.second);
                    m_industrycheck.ui->textBrowser->append(QString("diatance = %1").arg(distance));
                }
            }
            m_industrycheck.cv_geometricCalculation = false;
        }
    }
}