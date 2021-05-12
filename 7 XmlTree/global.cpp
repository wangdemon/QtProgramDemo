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
        setting->setValue("/Config/Fixed", FixedState);
        setting->setValue("Config/InitializeShow", InitializeShow);

        setting->setValue("/TreeWidget/X", TreeWidgetPos.x());
        setting->setValue("/TreeWidget/Y", TreeWidgetPos.y());
        setting->setValue("/TreeWidget/Width", TreeWidgetSize.width());
        setting->setValue("/TreeWidget/Height", TreeWidgetSize.height());

        setting->setValue("/TreeWidget/BgColor", BgColor.name(QColor::HexArgb));
        setting->setValue("/TreeWidget/HoverBgColor", HoverBgColor.name(QColor::HexArgb));
        setting->setValue("/TreeWidget/CheckedBgColor", CheckedBgColor.name(QColor::HexArgb));
        setting->setValue("/TreeWidget/TextColor", TextColor.name(QColor::HexArgb));
        setting->setValue("/TreeWidget/HoverTextColor", HoverTextColor.name(QColor::HexArgb));
        setting->setValue("/TreeWidget/CheckedTextColor", CheckedTextColor.name(QColor::HexArgb));
        setting->setValue("/TreeWidget/LineColor", LineColor.name(QColor::HexArgb));

        setting->setValue("/TreeWidget/BkImageState", BkImageState);
        setting->setValue("/TreeWidget/BkImagePath", BkImagePath);
        setting->setValue("/TreeWidget/BkImageOpacity", QString::number(BkImageOpacity));

        setting->setValue("/TreeWidget/ExpandFirstSubItemState", ExpandFirstSubItemState);
        setting->setValue("/TreeWidget/HideRootItemState", HideRootItemState);


        setting->setValue("/NewTreeWidget/X", NewTreeWidgetPos.x());
        setting->setValue("/NewTreeWidget/Y", NewTreeWidgetPos.y());
        setting->setValue("/NewTreeWidget/Width", NewTreeWidgetSize.width());
        setting->setValue("/NewTreeWidget/Height", NewTreeWidgetSize.height());

        setting->setValue("/Screen/ScreenWidth", ScreenWidth);
        setting->setValue("/Screen/ScreenHeight", ScreenHeight);

        setting->setValue("/NewAddItem/NewAddItemText", NewAddItemText);


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

        if(!setting->contains("/Config/Fixed"))
        {
            setting->setValue("/Config/Fixed", FixedState);
        }

        if(!setting->contains("/Config/InitializeShow"))
        {
            setting->setValue("/Config/InitializeShow", InitializeShow);
        }

        if(!setting->contains("/TreeWidget/X"))
        {
            setting->setValue("/TreeWidget/X", TreeWidgetPos.x());
        }

        if(!setting->contains("/TreeWidget/Y"))
        {
            setting->setValue("/TreeWidget/Y", TreeWidgetPos.y());
        }

        if(!setting->contains("/TreeWidget/Width"))
        {
            setting->setValue("/TreeWidget/Width", TreeWidgetSize.width());
        }

        if(!setting->contains("/TreeWidget/Height"))
        {
            setting->setValue("/TreeWidget/Height", TreeWidgetSize.height());
        }

        if(!setting->contains("/TreeWidget/BgColor"))
        {
            setting->setValue("/TreeWidget/BgColor", BgColor.name(QColor::HexArgb));
        }
        if(!setting->contains("/TreeWidget/HoverBgColor"))
        {
            setting->setValue("/TreeWidget/HoverBgColor", HoverBgColor.name(QColor::HexArgb));
        }
        if(!setting->contains("/TreeWidget/CheckedBgColor"))
        {
            setting->setValue("/TreeWidget/CheckedBgColor", CheckedBgColor.name(QColor::HexArgb));
        }
        if(!setting->contains("/TreeWidget/TextColor"))
        {
            setting->setValue("/TreeWidget/TextColor", TextColor.name(QColor::HexArgb));
        }
        if(!setting->contains("/TreeWidget/HoverTextColor"))
        {
            setting->setValue("/TreeWidget/HoverTextColor", HoverTextColor.name(QColor::HexArgb));
        }
        if(!setting->contains("/TreeWidget/CheckedTextColor"))
        {
            setting->setValue("/TreeWidget/CheckedTextColor", CheckedTextColor.name(QColor::HexArgb));
        }
        if(!setting->contains("/TreeWidget/LineColor"))
        {
            setting->setValue("/TreeWidget/LineColor", LineColor.name(QColor::HexArgb));
        }

        if(!setting->contains("/TreeWidget/BkImageState"))
        {
            setting->setValue("/TreeWidget/BkImageState", BkImageState);
        }
        if(!setting->contains("/TreeWidget/BkImagePath"))
        {
            setting->setValue("/TreeWidget/BkImagePath", BkImagePath);
        }
        if(!setting->contains("/TreeWidget/BkImageOpacity"))
        {
            setting->setValue("/TreeWidget/BkImageOpacity", QString::number(BkImageOpacity));
        }

        if(!setting->contains("/TreeWidget/ExpandFirstSubItemState"))
        {
            setting->setValue("/TreeWidget/ExpandFirstSubItemState", ExpandFirstSubItemState);
        }
        if(!setting->contains("/TreeWidget/HideRootItemState"))
        {
            setting->setValue("/TreeWidget/HideRootItemState", HideRootItemState);
        }


        if(!setting->contains("/NewTreeWidget/X"))
        {
            setting->setValue("/NewTreeWidget/X", NewTreeWidgetPos.x());
        }

        if(!setting->contains("/NewTreeWidget/Y"))
        {
            setting->setValue("/NewTreeWidget/Y", NewTreeWidgetPos.y());
        }

        if(!setting->contains("/NewTreeWidget/Width"))
        {
            setting->setValue("/NewTreeWidget/Width", NewTreeWidgetSize.width());
        }

        if(!setting->contains("/NewTreeWidget/Height"))
        {
            setting->setValue("/NewTreeWidget/Height", NewTreeWidgetSize.height());
        }

        if(!setting->contains("/Screen/ScreenWidth"))
        {
            setting->setValue("/Screen/ScreenWidth", ScreenWidth);
        }
        if(!setting->contains("/Screen/ScreenHeight"))
        {
            setting->setValue("/Screen/ScreenHeight", ScreenHeight);
        }

        if(!setting->contains("/NewAddItem/NewAddItemText"))
        {
            setting->setValue("/NewAddItem/NewAddItemText", NewAddItemText);
        }

        TreeWidgetPos.setX(setting->value("/TreeWidget/X", TreeWidgetPos.x()).toInt());
        TreeWidgetPos.setY(setting->value("/TreeWidget/Y", TreeWidgetPos.y()).toInt());
        TreeWidgetSize.setWidth(setting->value("/TreeWidget/Width", TreeWidgetSize.width()).toInt());
        TreeWidgetSize.setHeight(setting->value("/TreeWidget/Height", TreeWidgetSize.height()).toInt());

        FrameState = setting->value("/Config/Frame", FrameState).toBool();
        FixedState = setting->value("/Config/Fixed", FixedState).toBool();
        InitializeShow = setting->value("/Config/InitializeShow", InitializeShow).toBool();
        PEProgramName = setting->value("/Config/PEProgramName", PEProgramName).toString();
        ChartProgramName = setting->value("/Config/ChartProgramName", ChartProgramName).toString();

        BgColor = setting->value("/TreeWidget/BgColor", BgColor.name(QColor::HexArgb)).toString();
        HoverBgColor = setting->value("/TreeWidget/HoverBgColor", HoverBgColor.name(QColor::HexArgb)).toString();
        CheckedBgColor = setting->value("/TreeWidget/CheckedBgColor", CheckedBgColor.name(QColor::HexArgb)).toString();
        TextColor = setting->value("/TreeWidget/TextColor", TextColor.name(QColor::HexArgb)).toString();
        HoverTextColor = setting->value("/TreeWidget/HoverTextColor", HoverTextColor.name(QColor::HexArgb)).toString();
        CheckedTextColor = setting->value("/TreeWidget/CheckedTextColor", CheckedTextColor.name(QColor::HexArgb)).toString();
        LineColor = setting->value("/TreeWidget/LineColor", LineColor.name(QColor::HexArgb)).toString();

        BkImageState = setting->value("/TreeWidget/BkImageState", BkImageState).toBool();
        BkImagePath = setting->value("/TreeWidget/BkImagePath", BkImagePath).toString();
        BkImageOpacity = setting->value("/TreeWidget/BkImageOpacity", BkImagePath).toFloat();


        ExpandFirstSubItemState = setting->value("/TreeWidget/ExpandFirstSubItemState", ExpandFirstSubItemState).toBool();
        HideRootItemState = setting->value("/TreeWidget/HideRootItemState", HideRootItemState).toBool();


        NewTreeWidgetPos.setX(setting->value("/NewTreeWidget/X", NewTreeWidgetPos.x()).toInt());
        NewTreeWidgetPos.setY(setting->value("/NewTreeWidget/Y", NewTreeWidgetPos.y()).toInt());
        NewTreeWidgetSize.setWidth(setting->value("/NewTreeWidget/Width", NewTreeWidgetSize.width()).toInt());
        NewTreeWidgetSize.setHeight(setting->value("/NewTreeWidget/Height", NewTreeWidgetSize.height()).toInt());

        ScreenWidth = setting->value("/Screen/ScreenWidth", ScreenWidth).toInt();
        ScreenHeight = setting->value("/Screen/ScreenHeight", ScreenHeight).toInt();

        NewAddItemText = setting->value("/NewAddItem/NewAddItemText", NewAddItemText).toString();

        //  delete setting;
        //  setting = nullptr;
    }
}

QString Global::GetIniPath()
{
    return RootPath + "/resources/SetupConfig.ini";
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

bool Global::GetFixedState()
{
    return FixedState;
}

bool Global::GetInitialzieShow()
{
    return InitializeShow;
}

void Global::SetTreeWidgetPos(QPoint pos)
{
    TreeWidgetPos = pos;
    setting->setValue("/TreeWidget/X", TreeWidgetPos.x());
    setting->setValue("/TreeWidget/Y", TreeWidgetPos.y());
}

void Global::SetTreeWidgetSize(QSize size)
{
    TreeWidgetSize = size;
    setting->setValue("/TreeWidget/Width", TreeWidgetSize.width());
    setting->setValue("/TreeWidget/Height", TreeWidgetSize.height());
}

QPoint Global::GetTreeWidgetPos()
{
    return TreeWidgetPos;
}

QSize Global::GetTreeWidgetSize()
{
    return TreeWidgetSize;
}

void Global::SetNewTreeWidgetPos(QPoint pos)
{
    NewTreeWidgetPos = pos;
    setting->setValue("/NewTreeWidget/X", NewTreeWidgetPos.x());
    setting->setValue("/NewTreeWidget/Y", NewTreeWidgetPos.y());
}

void Global::SetNewTreeWidgetSize(QSize size)
{
    NewTreeWidgetSize = size;
    setting->setValue("/NewTreeWidget/Width", NewTreeWidgetSize.width());
    setting->setValue("/NewTreeWidget/Height", NewTreeWidgetSize.height());
}

QPoint Global::GetNewTreeWidgetPos()
{
    return NewTreeWidgetPos;
}

QSize Global::GetNewTreeWidgetSize()
{
    return NewTreeWidgetSize;
}

QColor Global::GetBgColor()
{
    return BgColor;
}

QColor Global::GetHoverBgColor()
{
    return HoverBgColor;
}

QColor Global::GetCheckedBgColor()
{
    return CheckedBgColor;
}

QColor Global::GetTextColor()
{
    return TextColor;
}

QColor Global::GetHoverTextColor()
{
    return HoverTextColor;
}

QColor Global::GetCheckedTextColor()
{
    return CheckedTextColor;
}

QColor Global::GetLineColor()
{
    return LineColor;
}

bool Global::GetBkImageState()
{
    return BkImageState;
}

QString Global::GetBkImagePath()
{
    return RootPath + "/resources/image/" + BkImagePath;
}

float Global::GetBkImageOpacity()
{
    return BkImageOpacity;
}

QString Global::GetImagePath()
{
    return RootPath + "/resources/" + ImagePath + "/";
}

bool Global::GetExpandFirstSubItemState()
{
    return ExpandFirstSubItemState;
}

bool Global::GetHideRootItemState()
{
    return HideRootItemState;
}

QSize Global::GetScreenSize()
{
    return QSize(ScreenWidth, ScreenHeight);
}

void Global::SetScreenSize(int width, int height)
{
    ScreenWidth = width;
    ScreenHeight = height;
    setting->setValue("/Screen/ScreenWidth", ScreenWidth);
    setting->setValue("/Screen/ScreenHeight", ScreenHeight);
}

QString Global::GetNewAddItemText()
{
    return NewAddItemText;
}

QString Global::GetStyleSheetStr()
{
    QString strStyle = QString("QWidget#MainWidget{"
                               "background: rgba(255, 0, 0, 0);"
                               "color: transparent;"
                               "}"
                               "QTreeView {"
                               "background-color: transparent;"
                               "font-size: 15px;"
                               "color: white;"
                               "border: none;"
                               "}"
                               "QTreeView::item {"
                               "height: 25px;"
                               "color: white;"
                               "border: none;"
                               "background-color: transparent;"
                               "}"
                               "QTreeView::item:hover, QTreeView::branch:hover { "
                                    "background-color: %1;"
                               "}"
                               "QTreeView::item:selected, QTreeView::branch:selected { "
                                    "background-color: %2;"
                               "}"
                               "QTreeView::branch {"
                                    "background-color: transparent;"
                               "}"
                               "QTreeView::branch:open:has-children {"
                               "image: url(%3);"
                               "}"
                               "QTreeView::branch:closed:has-children {"
                               "image: url(%4);"
                               "}"

                               "QScrollBar:vertical {"
                                   "background: rgba(0, 160, 230, 100);"
                                   "width: 15px;"
                                   "margin: 0px 0 0px 0;"
                               "}"
                               "QScrollBar::handle:vertical {"
                                   "background: rgb(49,226,238);"
                                   "min-height: 20px;"
                                   "margin: 0 1px 0 2px;"
    //                                   "border-radius: 3px;"
                               "border: none;"
                               "}"

                               "QScrollBar::add-line:vertical {"
                                   "background: rgba(0, 160, 230, 100);"
                                   "height: 0px;"
                                   "subcontrol-position: bottom;"
                                   "subcontrol-origin: margin;"
                               "}"

                               "QScrollBar::sub-line:vertical {"
                                   "background: rgba(0, 160, 230, 100);"
                                   "height: 0px;"
                                   "subcontrol-position: top;"
                                   "subcontrol-origin: margin;"
                               "}"

                               "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {"
                                   "border: 1px solid grey;"
                                   "width: 3px;"
                                   "height: 3px;"
                                   "background: white;"
                               "}"

                               "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
                                   "background: none;"
                               "}"


                               "QScrollBar:horizontal {"
                                   "background: rgba(0, 160, 230, 100);"
                                   "height: 15px;"
                                   "margin: 0px 0 0px 0;"
                               "}"
                               "QScrollBar::handle:horizontal {"
                                   "background: rgb(49,226,238);"
                                   "min-width: 20px;"
                                   "margin: 2px 0px 1px 0px;"
    //                                   "border-radius: 3px;"
                               "border: none;"
                              "}"
                               "QScrollBar::add-line:horizontal {"
                                   "border: 0px solid grey;"
                                   "background: #32CC99;"
                                   "width: 0px;"
                                  " subcontrol-position: right;"
                                   "subcontrol-origin: margin;"
                               "}"

                               "QScrollBar::sub-line:horizontal {"
                                   "border: 0px solid grey;"
                                   "background: #32CC99;"
                                   "width: 0px;"
                                   "subcontrol-position: left;"
                                   "subcontrol-origin: margin;"
                               "}"

                               "QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {"
                                   "background: none;"
                               "}"

                               "QPushButton#RedButton {"
                                    "background: #C8FD4135;"
                                    "border: 1px solid white;"
                               "}"
                               "QPushButton#RedButton::hover {"
                                    "background: #FB3B59;"
                                    "border: 1px solid white;"
                               "}"
                               "QPushButton#RedButton::pressed {"
                                    "background: #BF0F2A;"
                                    "border: 1px solid #FD4135;"
                               "}"

                               "QPushButton#GreenButton {"
                                    "background: #C85DC51A;"
                                    "border: 1px solid white;"
                               "}"
                               "QPushButton#GreenButton::hover {"
                                    "background: #79F828;"
                                    "border: 1px solid white;"
                               "}"
                               "QPushButton#GreenButton::pressed {"
                                    "background: #47A50B;"
                                    "border: 1px solid #5DC51A;"
                               "}"

                               "QPushButton#OrangeButton {"
                                    "background: #C8F87F32;"
                                    "border: 1px solid white;"
                               "}"
                               "QPushButton#OrangeButton::hover {"
                                    "background: #FD9857;"
                                    "border: 1px solid white;"
                               "}"
                               "QPushButton#OrangeButton::pressed {"
                                    "background: #EC7428;"
                                    "border: 1px solid #3157E5;"
                               "}"

                               "QPushButton#NoneButton {"
                                    "background: #C8C9CBD1;"
                                    "border: 1px solid white;"
                               "}"
                               "QPushButton#NoneButton::hover {"
                                    "background: #DDDEE0;"
                                    "border: 0px solid white;"
                               "}"
                               "QPushButton#NoneButton::pressed {"
                                    "background: #B1B3B7;"
                                    "border: 1px solid #C9CBD1;"
                               "}"

                               "QPushButton#AddButton {"
                                    "background: transparent;"
                                    "border: 1px solid white;"
                               "}"
                               "QPushButton#AddButton::hover {"
                                    "background: #DDDEE0;"
                                    "border: 0px solid white;"
                               "}"
                               "QPushButton#AddButton::pressed {"
                                    "background: #CA47F0;"
                                    "border: 1px solid #C9CBD1;"
                               "}"

                               "QPushButton#DeleteButton {"
                                    "background: transparent;"
                                    "border: 1px solid white;"
                               "}"
                               "QPushButton#DeleteButton::hover {"
                                    "background: #DDDEE0;"
                                    "border: 0px solid white;"
                               "}"
                               "QPushButton#DeleteButton::pressed {"
                                    "background: #CA47F0;"
                                    "border: 1px solid #C9CBD1;"
                               "}"

                               "QLabel#TipLabel {"
                                    "color: #E92877;"
                               "}"
                                "QTableWidget {"
                                    "background: transparent;"
                                    "color: white;"
                                    //"border: none;"
                                    "border: 1px solid white;"
                                "}"
                               "QComboBox {"
                                "background: transparent;"
                                "}"
                               ).arg(Global::GetHoverBgColor().name(QColor::HexArgb)).arg(Global::GetCheckedBgColor().name(QColor::HexArgb))
            .arg(Global::GetImagePath() + "arrow_bottom.png").arg(Global::GetImagePath() + "arrow_right.png");
    return strStyle;
}

Global::Global()
{
}

Global* Global::m_pInstance = nullptr;
QMutex Global::m_mutex;
Global::GC Global::gc;
QString Global::RootPath = "";

QPoint Global::TreeWidgetPos = QPoint(20, 20);
QSize Global::TreeWidgetSize = QSize(200, 50);

QPoint Global::NewTreeWidgetPos = QPoint(200, 200);
QSize Global::NewTreeWidgetSize = QSize(200, 300);

bool Global::FrameState = true;
bool Global::FixedState = false;
bool Global::InitializeShow = false;
QString Global::PEProgramName = "PE";
QString Global::ChartProgramName = "ChartProgram";

QSettings* Global::setting = nullptr;

QColor Global::BgColor = QColor("#31495A");
QColor Global::HoverBgColor = QColor("#77D8C4");
QColor Global::CheckedBgColor = QColor("#18BD9B");
QColor Global::TextColor = QColor("#F0F0F0");
QColor Global::HoverTextColor = QColor("#000000");
QColor Global::CheckedTextColor = QColor("#F0F0F0");
QColor Global::LineColor = QColor("#404244");
bool Global::BkImageState = false;
QString Global::BkImagePath = "";
float Global::BkImageOpacity = 0.0;

QString Global::ImagePath = "image";

bool Global::ExpandFirstSubItemState = false;
bool Global::HideRootItemState = true;

int Global::ScreenWidth = 1920;
int Global::ScreenHeight = 1080;
QString Global::NewAddItemText = "新增";

