#include "widget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QDir>
#include <QComboBox>
#include <QDebug>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    initialzie();
    createConnections();
}

Widget::~Widget()
{
}

void Widget::initialzie()
{
    m_pMainVLayout = new QVBoxLayout;

    m_pTextAndParameterHLayout = new QHBoxLayout;
    m_pMainVLayout->addLayout(m_pTextAndParameterHLayout);

    m_pTextEdit = new QTextEdit;
    m_pTextAndParameterHLayout->addWidget(m_pTextEdit);

    m_pPathHLayout = new QHBoxLayout;
    m_pPathLabel = new QLabel;
    m_pPathLabel->setText("路径");
    m_pPathLineEdit = new QLineEdit;
    m_pOpenPathButton = new QPushButton;
    m_pOpenPathButton->setText("打开");
    m_pSubmitButton = new QPushButton;
    m_pSubmitButton->setText("确认");
    m_pPathHLayout->addWidget(m_pPathLabel);
    m_pPathHLayout->addWidget(m_pPathLineEdit);
    m_pPathHLayout->addWidget(m_pOpenPathButton);
    m_pPathHLayout->addWidget(m_pSubmitButton);
    m_pMainVLayout->addLayout(m_pPathHLayout);

    m_pParameterWidget = new QWidget;
    m_pParameterWidget->setObjectName("ParameterWidget");
    m_pParameterWidget->setFixedWidth(300);
    m_pParameterMainVLayout = new QVBoxLayout;
    m_pParameterWidget->setLayout(m_pParameterMainVLayout);
    m_pTextAndParameterHLayout->addWidget(m_pParameterWidget);

    m_pParameterFilterLayout = new QHBoxLayout;
    m_pParameterFilterLabel = new QLabel;
    m_pParameterFilterLabel->setText("文件过滤:");
    m_pParameterFilterLineEdit = new QLineEdit;
    m_pParameterFilterLayout->addWidget(m_pParameterFilterLabel);
    m_pParameterFilterLayout->addWidget(m_pParameterFilterLineEdit);
    m_pParameterMainVLayout->addLayout(m_pParameterFilterLayout);

    m_pShowPathLayout = new QHBoxLayout;
    m_pShowPathLabel = new QLabel;
    m_pShowPathLabel->setText("是否显示路径:");
    m_pShowPathComboBox = new QComboBox;
    m_pShowPathComboBox->setFixedHeight(30);
    m_pShowPathComboBox->addItem("否");
    m_pShowPathComboBox->addItem("是");
    m_pShowPathLayout->addWidget(m_pShowPathLabel);
    m_pShowPathLayout->addWidget(m_pShowPathComboBox);
    m_pParameterMainVLayout->addLayout(m_pShowPathLayout);

    m_pShowReturnLayout = new QHBoxLayout;
    m_pShowReturnLabel = new QLabel;
    m_pShowReturnLabel->setText("是否显示换行:");
    m_pShowReturnComboBox = new QComboBox;
    m_pShowReturnComboBox->setFixedHeight(30);
    m_pShowReturnComboBox->addItem("否");
    m_pShowReturnComboBox->addItem("是");
    m_pShowReturnLayout->addWidget(m_pShowReturnLabel);
    m_pShowReturnLayout->addWidget(m_pShowReturnComboBox);
    m_pParameterMainVLayout->addLayout(m_pShowReturnLayout);


    m_pShowSuffixLayout = new QHBoxLayout;
    m_pShowSuffixLabel = new QLabel;
    m_pShowSuffixLabel->setText("是否显示后缀名:");
    m_pShowSuffixComboBox = new QComboBox;
    m_pShowSuffixComboBox->setFixedHeight(30);
    m_pShowSuffixComboBox->addItem("否");
    m_pShowSuffixComboBox->addItem("是");
    m_pShowSuffixLayout->addWidget(m_pShowSuffixLabel);
    m_pShowSuffixLayout->addWidget(m_pShowSuffixComboBox);
    m_pParameterMainVLayout->addLayout(m_pShowSuffixLayout);

    m_pShowPrefixLayout = new QHBoxLayout;
    m_pPrefixLabel = new QLabel;
    m_pPrefixLabel->setText("前缀:");
    m_pPrefixLineEdit = new QLineEdit;
    m_pShowPrefixLayout->addWidget(m_pPrefixLabel);
    m_pShowPrefixLayout->addWidget(m_pPrefixLineEdit);
    m_pParameterMainVLayout->addLayout(m_pShowPrefixLayout);

    m_pParameterMainVLayout->addStretch();

    this->setLayout(m_pMainVLayout);
    this->resize(700, 400);
    this->setWindowTitle("查找文件名");
    this->setObjectName("MainWidget");
}

void Widget::createConnections()
{
    connect(m_pOpenPathButton, &QPushButton::clicked, this, &Widget::slotOpenPath);
    connect(m_pSubmitButton, &QPushButton::clicked, this, &Widget::slotSubmit);
}

void Widget::findAllFileName()
{
    getFileFilterParameter();
    getShowPathParameter();
    getShowReturnParamter();
    getFilePathParameter();
    getShowFileSuffixParameter();
    getPrefixParameter();

    m_pTextEdit->clear();

    QDir dir(m_sDirPath);
    if (dir.exists()) {
        QStringList dir_list = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);   //去掉"."和".."
        QStringList file_list = dir.entryList(QDir::Files | QDir::NoDotAndDotDot);
        // QStringList nameFilters;
        // nameFilters << "*.txt" << "*.ini";
        // 获取文件名
        // QStringList file_list_spec = dir.entryList(m_slistFilter, QDir::Files | QDir::NoDotAndDotDot);
        QList<QFileInfo> listFileInfo = dir.entryInfoList(m_slistFilter, QDir::Files | QDir::NoDotAndDotDot);
        for(int i = 0; i < listFileInfo.size(); i++) {
            // qDebug() << listFileInfo.at(i);
            QFileInfo fileInfo = listFileInfo.at(i);

            if(m_iReturnLine == 0) {
                if(m_iShowPath == 0) {
                    if(m_iShowSuffix == 0) {
                        if(m_sPrefix.isEmpty()) {
                            m_pTextEdit->insertPlainText(" " + fileInfo.baseName());
                        }
                        else {
                            m_pTextEdit->insertPlainText(" " + m_sPrefix + fileInfo.baseName());
                        }

                    }
                    else {
                        if(m_sPrefix.isEmpty()) {
                            m_pTextEdit->insertPlainText(" " + fileInfo.fileName());
                        }
                        else {
                            m_pTextEdit->insertPlainText(" " + m_sPrefix + fileInfo.fileName());
                        }
                    }

                }
                else {
                    if(m_iShowSuffix == 0) {
                        if(m_sPrefix.isEmpty()) {
                            m_pTextEdit->insertPlainText(" " + fileInfo.absolutePath() + "/" + fileInfo.baseName());
                        }
                        else {
                            m_pTextEdit->insertPlainText(" " + m_sPrefix + fileInfo.absolutePath() + "/" + fileInfo.baseName());
                        }

                    }
                    else {
                        if(m_sPrefix.isEmpty()) {
                            m_pTextEdit->insertPlainText(" " + fileInfo.filePath());
                        }
                        else {
                            m_pTextEdit->insertPlainText(" " + m_sPrefix + fileInfo.filePath());
                        }
                    }
                }
            }
            else {
                if(m_iShowPath == 0) {
                    if(m_iShowSuffix == 0) {
                        if(m_sPrefix.isEmpty()) {
                            m_pTextEdit->append(fileInfo.baseName());
                        }
                        else {
                            m_pTextEdit->append(m_sPrefix + fileInfo.baseName());
                        }

                    }
                    else {
                        if(m_sPrefix.isEmpty()) {
                            m_pTextEdit->append(fileInfo.fileName());
                        }
                        else {
                            m_pTextEdit->append(m_sPrefix + fileInfo.fileName());
                        }
                    }

                }
                else {
                    if(m_iShowSuffix == 0) {
                        if(m_sPrefix.isEmpty()) {
                            m_pTextEdit->append(fileInfo.absolutePath() + "/" + fileInfo.baseName());
                        }
                        else {
                            m_pTextEdit->append(m_sPrefix + fileInfo.absolutePath() + "/" + fileInfo.baseName());
                        }

                    }
                    else {
                        if(m_sPrefix.isEmpty()) {
                            m_pTextEdit->append(fileInfo.filePath());
                        }
                        else {
                            m_pTextEdit->append(m_sPrefix + fileInfo.filePath());
                        }
                    }
                }
            }
        }
    }
    else {
        QMessageBox msgBox;
        msgBox.setText("文件夹路径不存在");
        msgBox.exec();
    }
}

void Widget::getShowPathParameter()
{
    m_iShowPath = m_pShowPathComboBox->currentIndex();
}

void Widget::getShowReturnParamter()
{
    m_iReturnLine = m_pShowReturnComboBox->currentIndex();
}

void Widget::getFilePathParameter()
{
    m_sDirPath = m_pPathLineEdit->text();
}

void Widget::getShowFileSuffixParameter()
{
    m_iShowSuffix = m_pShowSuffixComboBox->currentIndex();
}

void Widget::getPrefixParameter()
{
    m_sPrefix = m_pPrefixLineEdit->text();
}

void Widget::getFileFilterParameter()
{
    m_slistFilter.clear();
    QString fileNames = m_pParameterFilterLineEdit->text().trimmed();
    QStringList tempListFileName = fileNames.split(" ");
    for (int i = 0; i < tempListFileName.size(); i++) {
        QString tempFileName = tempListFileName[i].trimmed();
        if(!tempFileName.isEmpty()) {
            m_slistFilter << tempFileName;
        }
    }
}

void Widget::slotOpenPath()
{
    QString dir = QFileDialog::getExistingDirectory(this, "打开目录",
                                                    QDir::currentPath(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    if(!dir.isEmpty()) {
        m_sDirPath = dir;
        m_pPathLineEdit->setText(m_sDirPath);
    }

}

void Widget::slotSubmit()
{
    findAllFileName();
}

