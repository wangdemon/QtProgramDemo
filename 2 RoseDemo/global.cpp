#include "global.h"

#include <QApplication>
#include <QFile>
#include <QDir>
#include <QList>
#include <QSettings>


Global *Global::Instance()
{
    if(m_pInstance == nullptr)
    {
        QMutexLocker locker(&m_mutex);
        if(m_pInstance == nullptr)
            m_pInstance = new Global;
    }
    return m_pInstance;
}

void Global::CheckResource()
{
    if(!setting)
    {
        setting = new QSettings(GetIniPath(), QSettings::IniFormat);
        setting->setIniCodec("UTF-8");
    }

    // 检查配置文件目录是否存在
    QList<QString> listPath;
    listPath << GetRootPath();
    for(QString path : listPath)
    {
        QDir dir(path);
        if(!dir.exists())
            dir.mkpath(path);
    }

    QFile iniFile(GetIniPath());
    if(!iniFile.exists())
    {
        // QSettings* setting = new QSettings(GetIniPath(), QSettings::IniFormat);
        // setting->setIniCodec("UTF-8");
        setting->setValue("/Config/PEProgramName", PEProgramName);
        setting->setValue("/Config/ChartProgramName", ChartProgramName);
        setting->setValue("/Config/Frame", FrameState);

        setting->setValue("/RoundProgress/X", RoundProgressPos.x());
        setting->setValue("/RoundProgress/Y", RoundProgressPos.y());
        setting->setValue("/RoundProgress/Width", RountProgressSize.width());
        setting->setValue("/RoundProgress/Height", RountProgressSize.height());

        setting->setValue("/RoseChart/X", RoseChartPos.x());
        setting->setValue("/RoseChart/Y", RoseChartPos.y());
        setting->setValue("/RoseChart/Width", RoseChartSize.width());
        setting->setValue("/RoseChart/Height", RoseChartSize.height());

        setting->setValue("/SineChart/X", SineChartPos.x());
        setting->setValue("/SineChart/Y", SineChartPos.y());
        setting->setValue("/SineChart/Width", SineChartSize.width());
        setting->setValue("/SineChart/Height", SineChartSize.height());

        setting->setValue("/BarChart/X", BarChartPos.x());
        setting->setValue("/BarChart/Y", BarChartPos.y());
        setting->setValue("/BarChart/Width", BarChartSize.width());
        setting->setValue("/BarChart/Height", BarChartSize.height());

        //        delete setting;
        //        setting = nullptr;
    }
    else
    {
        //        QSettings* setting = new QSettings(GetIniPath(), QSettings::IniFormat);
        //        setting->setIniCodec("UTF-8");

        if(!setting->contains("/Config/PEProgramName"))
        {
            setting->setValue("/Config/PEProgramName", PEProgramName);
        }

        if(!setting->contains("/Config/ChartProgramName"))
        {
            setting->setValue("/Config/ChartProgramName", ChartProgramName);
        }

        if(!setting->contains("/Config/Frame"))
        {
            setting->setValue("/Config/Frame", FrameState);
        }

        if(!setting->contains("/RoundProgress/X"))
        {
            setting->setValue("/RoundProgress/X", RoundProgressPos.x());
        }

        if(!setting->contains("/RoundProgress/Y"))
        {
            setting->setValue("/RoundProgress/Y", RoundProgressPos.y());
        }

        if(!setting->contains("/RoundProgress/Width"))
        {
            setting->setValue("/RoundProgress/Width", RountProgressSize.width());
        }

        if(!setting->contains("/RoundProgress/Height"))
        {
            setting->setValue("/RoundProgress/Height", RountProgressSize.height());
        }

        if(!setting->contains("/RoseChart/X"))
        {
            setting->setValue("/RoseChart/X", RoseChartPos.x());
        }

        if(!setting->contains("/RoseChart/Y"))
        {
            setting->setValue("/RoseChart/Y", RoseChartPos.y());
        }

        if(!setting->contains("/RoseChart/Width"))
        {
            setting->setValue("/RoseChart/Width", RoseChartSize.width());
        }

        if(!setting->contains("/RoseChart/Height"))
        {
            setting->setValue("/RoseChart/Height", RoseChartSize.height());
        }

        if(!setting->contains("/SineChart/X"))
        {
            setting->setValue("/SineChart/X", SineChartPos.x());
        }

        if(!setting->contains("/SineChart/Y"))
        {
            setting->setValue("/SineChart/Y", SineChartPos.y());
        }

        if(!setting->contains("/SineChart/Width"))
        {
            setting->setValue("/SineChart/Width", SineChartSize.width());
        }

        if(!setting->contains("/SineChart/Height"))
        {
            setting->setValue("/SineChart/Height", SineChartSize.height());
        }

        if(!setting->contains("/BarChart/X"))
        {
            setting->setValue("/BarChart/X", BarChartPos.x());
        }

        if(!setting->contains("/BarChart/Y"))
        {
            setting->setValue("/BarChart/Y", BarChartPos.y());
        }

        if(!setting->contains("/BarChart/Width"))
        {
            setting->setValue("/BarChart/Width", BarChartSize.width());
        }

        if(!setting->contains("/BarChart/Height"))
        {
            setting->setValue("/BarChart/Height", BarChartSize.height());
        }

        RoundProgressPos.setX(setting->value("/RoundProgress/X", RoundProgressPos.x()).toInt());
        RoundProgressPos.setY(setting->value("/RoundProgress/Y", RoundProgressPos.y()).toInt());
        RountProgressSize.setWidth(setting->value("/RoundProgress/Width", RountProgressSize.width()).toInt());
        RountProgressSize.setHeight(setting->value("/RoundProgress/Height", RountProgressSize.height()).toInt());

        RoseChartPos.setX(setting->value("/RoseChart/X", RoseChartPos.x()).toInt());
        RoseChartPos.setY(setting->value("/RoseChart/Y", RoseChartPos.y()).toInt());
        RoseChartSize.setWidth(setting->value("/RoseChart/Width", RoseChartSize.width()).toInt());
        RoseChartSize.setHeight(setting->value("/RoseChart/Height", RoseChartSize.height()).toInt());

        SineChartPos.setX(setting->value("/SineChart/X", SineChartPos.x()).toInt());
        SineChartPos.setY(setting->value("/SineChart/Y", SineChartPos.y()).toInt());
        SineChartSize.setWidth(setting->value("/SineChart/Width", SineChartSize.width()).toInt());
        SineChartSize.setHeight(setting->value("/SineChart/Height", SineChartSize.height()).toInt());

        BarChartPos.setX(setting->value("/BarChart/X", BarChartPos.x()).toInt());
        BarChartPos.setY(setting->value("/BarChart/Y", BarChartPos.y()).toInt());
        BarChartSize.setWidth(setting->value("/BarChart/Width", BarChartSize.width()).toInt());
        BarChartSize.setHeight(setting->value("/BarChart/Height", BarChartSize.height()).toInt());

        FrameState = setting->value("/Config/Frame", FrameState).toBool();
        PEProgramName = setting->value("/Config/PEProgramName", PEProgramName).toString();
        ChartProgramName = setting->value("/Config/ChartProgramName", ChartProgramName).toString();

        //        delete setting;
        //        setting = nullptr;
    }
}

QString Global::GetIniPath()
{
    return RootPath + "/resouces/SetupConfig.ini";
}

QString Global::GetRootPath()
{
    return RootPath;
}

void Global::SetRootPath(const QString &path)
{
    RootPath = path;
}

QString Global::GetPEProgramName()
{
    return PEProgramName;
}

QString Global::GetChartProgramName()
{
    return ChartProgramName;
}

bool Global::GetFrameState()
{
    return FrameState;
}

void Global::SetRoundProgressPos(QPoint pos)
{
    RoundProgressPos = pos;
    setting->setValue("/RoundProgress/X", RoundProgressPos.x());
    setting->setValue("/RoundProgress/Y", RoundProgressPos.y());
}

void Global::SetRountProgressSize(QSize size)
{
    RountProgressSize = size;
    setting->setValue("/RoundProgress/Width", RountProgressSize.width());
    setting->setValue("/RoundProgress/Height", RountProgressSize.height());
}

QPoint Global::GetRoundProgressPos()
{
    return RoundProgressPos;
}

QSize Global::GetRountProgressSize()
{
    return RountProgressSize;
}

void Global::SetRoseChartPos(QPoint pos)
{
    RoseChartPos = pos;
    setting->setValue("/RoseChart/X", RoseChartPos.x());
    setting->setValue("/RoseChart/Y", RoseChartPos.y());
}

void Global::SetRoseChartSize(QSize size)
{
    RoseChartSize = size;
    setting->setValue("/RoseChart/Width", RoseChartSize.width());
    setting->setValue("/RoseChart/Height", RoseChartSize.height());
}

QPoint Global::GetRoseChartPos()
{
    return RoseChartPos;
}

QSize Global::GetRoseChartSize()
{
    return RoseChartSize;
}

void Global::SetSineChartPos(QPoint pos)
{
    SineChartPos = pos;
    setting->setValue("/SineChart/X", SineChartPos.x());
    setting->setValue("/SineChart/Y", SineChartPos.y());
}

void Global::SetSineChartSize(QSize size)
{
    SineChartSize = size;
    setting->setValue("/SineChart/Width", SineChartSize.width());
    setting->setValue("/SineChart/Height", SineChartSize.height());
}

QPoint Global::GetSineChartPos()
{
    return SineChartPos;
}

QSize Global::GetSineChartSize()
{
    return SineChartSize;
}

void Global::SetBarChartPos(QPoint pos)
{
    BarChartPos = pos;
    setting->setValue("/BarChart/X", BarChartPos.x());
    setting->setValue("/BarChart/Y", BarChartPos.y());
}

void Global::SetBarChartSize(QSize size)
{
    BarChartSize = size;
    setting->setValue("/BarChart/Width", BarChartSize.width());
    setting->setValue("/BarChart/Height", BarChartSize.height());
}

QPoint Global::GetBarChartPos()
{
    return BarChartPos;
}

QSize Global::GetBarChartSize()
{
    return BarChartSize;
}

Global::Global()
{    
}

Global* Global::m_pInstance = nullptr;
QMutex Global::m_mutex;
Global::GC Global::gc;
QString Global::RootPath = "";

QPoint Global::RoundProgressPos = QPoint(20, 20);
QSize Global::RountProgressSize = QSize(200, 50);

QPoint Global::RoseChartPos = QPoint(30, 100);
QSize Global::RoseChartSize = QSize(100, 100);

QPoint Global::SineChartPos = QPoint(30, 300);
QSize Global::SineChartSize = QSize(300, 100);

QPoint Global::BarChartPos = QPoint(500, 300);
QSize Global::BarChartSize = QSize(300, 100);

bool Global::FrameState = true;
QString Global::PEProgramName = "PE";
QString Global::ChartProgramName = "ChartProgram";

QSettings* Global::setting = nullptr;
