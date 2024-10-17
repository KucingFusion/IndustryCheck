#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>

class IndustryCheck;
class cropbox;
//图像显示线程
class ImgDisplayThread : public QThread
{
    Q_OBJECT
public:
    explicit ImgDisplayThread(IndustryCheck&m_industrycheck_, QObject *parent = nullptr);

protected:
    void run() override;

private:
    IndustryCheck& m_industrycheck;
      
signals:

};

//图像处理线程
class ImgProcessThread : public QThread
{
    friend class cropbox;
    Q_OBJECT
public:
    explicit ImgProcessThread(IndustryCheck&m_industrycheck_, QObject *parent = nullptr);

protected:
    void run() override;

private:
    IndustryCheck& m_industrycheck;
    cropbox * m_cropbox;
signals:

};

#endif // MYTHREAD_H


