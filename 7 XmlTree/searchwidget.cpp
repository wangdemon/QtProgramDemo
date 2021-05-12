#include "searchwidget.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QIcon>
#include <QMessageBox>
#include <QPainter>
#include <QPaintEvent>
#include <QStyleOption>

#include "global.h"

SearchWidget::SearchWidget(QWidget *parent)
    : QWidget(parent)
{
    initialize();
    createConnections();
}

void SearchWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void SearchWidget::initialize()
{
    m_pMainHLayout = new QHBoxLayout;
    m_pMainHLayout->setSpacing(8);
    m_pMainHLayout->setMargin(0);
    m_pMainHLayout->setContentsMargins(0, 0, 0, 0);
    m_pSearchLineEdit = new QLineEdit;
    m_pSearchLineEdit->setFixedHeight(32);
    m_pPreviousButton = new QPushButton;
    m_pPreviousButton->setObjectName("PreviousButton");
    m_pPreviousButton->setIcon(QIcon(Global::GetImagePath() + "previous.png"));
    m_pPreviousButton->setFixedSize(35, 35);
    //    m_pPreviousButton->setStyleSheet("background: red;");
    m_pPreviousButton->setIconSize(QSize(30, 30));
    m_pNextButton = new QPushButton;
    m_pNextButton->setObjectName("NextButton");
    m_pNextButton->setIcon(QIcon(Global::GetImagePath() + "next.png"));
    m_pNextButton->setFixedSize(35, 35);
    m_pNextButton->setIconSize(QSize(30, 30));
    //    m_pSearchButton = new QPushButton;
    //    m_pSearchButton->setFixedSize(35, 35);
    //    m_pSearchButton->setIconSize(QSize(30, 30));
    //    m_pSearchButton->setIcon(QIcon(":/resources/image/search.png"));
    //    this->setStyleSheet("QPushButton {"
    //                        "border: none;"
    //                        "}"
    //                        "QPushButton{"
    //                        "background: transparent;}"
    //                        "QPushButton::hover {"
    //                        "background: #2F9DEC;"
    //                        "color: red;}"
    //                        "QPushButton::pressed {"
    //                        "background: #177FC9;}"
    //                        );
    m_pMainHLayout->addWidget(m_pSearchLineEdit);
    m_pMainHLayout->addWidget(m_pPreviousButton);
    m_pMainHLayout->addWidget(m_pNextButton);
    //    m_pMainHLayout->addWidget(m_pSearchButton);

    this->setLayout(m_pMainHLayout);
    this->setObjectName("SearchWidget");

    this->setStyleSheet("QPushButton {"
                        "border:none;"
                        //"border: 1px solid white;"
                        //"border-radius: 6px;"
                        "background-color: transparent;"
                        "}"
                        "QPushButton:hover {"
                        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #142DE9, stop: 1 #14E3E9);"
                        "}"
                        "QPushButton:pressed {"
                        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #EB0BCB, stop: 1 #086CDA);"
                        "}"
                        );
}

void SearchWidget::createConnections()
{
    //    connect(m_pSearchButton, &QPushButton::clicked, this, &SearchWidget::slotSubmitSearch);
    connect(m_pSearchLineEdit, &QLineEdit::textEdited, this, &SearchWidget::slotSubmitSearch);
    connect(m_pSearchLineEdit, &QLineEdit::returnPressed, this, &SearchWidget::slotSubmitSearch);
    connect(m_pPreviousButton, &QPushButton::clicked, this, &SearchWidget::signalPrevious);
    connect(m_pNextButton, &QPushButton::clicked, this, &SearchWidget::signalNext);
}

void SearchWidget::slotSubmitSearch()
{
    QString strSearch = m_pSearchLineEdit->text();
    if(strSearch.isEmpty()) {
        //        QMessageBox msgBox;
        //        //  msgBox.setWindowTitle("提示");
        //        msgBox.setText("搜索内容为空");
        //        msgBox.exec();
        return;
    }
    emit signalSearch(strSearch);
}
