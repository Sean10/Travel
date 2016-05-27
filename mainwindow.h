#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCoreApplication>
#include <QFile>
#include <QComboBox>
#include <QDebug>
#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QStackedLayout>
#include <QStackedWidget>
#include <QLineEdit>
#include <QRadioButton>
#include <QDialog>
#include <QMessageBox>
#include <QApplication>
#include <QLabel>
#include <QTextCodec>
#include <QThread>
#include <QCheckBox>
#include <QDebug>
#include <QTextEdit>
#include <QIcon>
#include <QMutex>
#include <QTimer>

//typedef struct Tour Tour;
//class Running;


class Widget : public QStackedWidget
{
    Q_OBJECT

public:
    Widget(QStackedWidget *parent = 0);
    ~Widget();
    void CreateFirstPage();
    void CreateSecondPage();
    void CreateThirdPage();
    void CreateFourthPage();
    void CreateFifthPage();
    void CreateSecond2Page();
    void CreateThird2Page();
    void CreateFourth2Page();
    void CreateSecond3Page();
    void CreateThird3Page();
    void CreateFourth3Page();

/*
    int Dijkstra1(int i, int j);
    void Dijkstra2(int i, int j, Tour *tTour);
    void Dijkstra3(int i, int j, Tour *tTour);
*/
    int passNum;
    int fro, to;//起始城市的标号
    int inq;//选择服务策略
    QString tName;//查询名字

    int ask;

public slots:
    void trans1();
    void trans2();
    void trans3();
    void trans4();
    void trans5();
    void Confirm();
    void trans2_2();
    void trans2_3();
    void trans2_4();
    void trans3_2();
    void trans3_3();
    void trans3_4();
    //void ConfirmOrder();
    void running();

    //void AddPassenger(QString);
    //void SettingStarting(int);
    //void SettingDestination(int);
    //void SettingStopoverCity(int,int);

    void execute();
    void AddStopoverCityAndTime();
    QString GetStopoverCity(int);
    int GetStopoverTime(int);
    void SettingStrategy1();
    void SettingStrategy2();
    void SettingStrategy3();


protected:



private:
    //QWidget *window;
    Widget *win;

    QLabel *label;
    QLabel *labelHint;
    QVBoxLayout *layout;
    QHBoxLayout *layoutLeft;
    QPushButton *buttonRoute;
    QPushButton *buttonState;
    QPushButton *buttonPlanChange;

    QVBoxLayout *firstLayout;
    QWidget *firstWidget;

    QLabel *labelHint2;
    QLabel *labelStarting;
    QLineEdit *lineTourName;
    //QLineEdit  *lineStarting;

    QLabel *labelDestination;
    //QLineEdit *lineDestination;

    QHBoxLayout *secondLayout1;
    QLabel *labelHint3;
    QLabel *labelStopoverCity2_1;
    QComboBox *lineStopoverCity2_1;
    QLabel *labelStopoverTime2_1;
    QSpinBox *lineStopoverTime2_1;

    QLabel *labelStopoverCity2_2;
    QComboBox *lineStopoverCity2_2;
    QLabel *labelStopoverTime2_2;
    QSpinBox *lineStopoverTime2_2;

    QLabel *labelStopoverCity2_3;
    QComboBox *lineStopoverCity2_3;
    QLabel *labelStopoverTime2_3;
    QSpinBox *lineStopoverTime2_3;

    QLabel *labelStopoverCity2_4;
    QComboBox *lineStopoverCity2_4;
    QLabel *labelStopoverTime2_4;
    QSpinBox *lineStopoverTime2_4;

    QLabel *labelStopoverCity2_5;
    QComboBox *lineStopoverCity2_5;
    QLabel *labelStopoverTime2_5;
    QSpinBox *lineStopoverTime2_5;

    QLabel *labelStopoverCity2_6;
    QComboBox *lineStopoverCity2_6;
    QLabel *labelStopoverTime2_6;
    QSpinBox *lineStopoverTime2_6;

    QLabel *labelStopoverCity2_7;
    QComboBox *lineStopoverCity2_7;
    QLabel *labelStopoverTime2_7;
    QSpinBox *lineStopoverTime2_7;

    QLabel *labelStopoverCity2_8;
    QComboBox *lineStopoverCity2_8;
    QLabel *labelStopoverTime2_8;
    QSpinBox *lineStopoverTime2_8;

    QLabel *labelStopoverCity;
    QLineEdit *lineStopoverCity;

    QHBoxLayout *secondLayout2_1;
    QHBoxLayout *secondLayout2_2;
    QHBoxLayout *secondLayout2_3;
    QHBoxLayout *secondLayout2_4;
    QHBoxLayout *secondLayout2_5;
    QHBoxLayout *secondLayout2_6;
    QHBoxLayout *secondLayout2_7;
    QHBoxLayout *secondLayout2_8;
    QVBoxLayout *secondLayout;
    QWidget *secondWidget;

    QPushButton *go3;
    QPushButton *back1;
    QPushButton *back1_2;
    QHBoxLayout *layoutButtonGoBack2;

    QLabel *labelChooseStrategy;
    QRadioButton *strategyTime;
    QRadioButton *strategyValue;
    QRadioButton *strategyValueTime;
    QSpinBox *lineStrategyValueTime;
    QVBoxLayout *layoutStrategy;
    QPushButton *go4;
    QPushButton *back2;
    QHBoxLayout *layoutButtonGoBack3;
    QWidget *thirdWidget;

    QLabel *labelOrder;
    QPushButton *buttonConfirm;
    QPushButton *buttonCancel;
    QHBoxLayout *layoutButtonConfirm;
    QVBoxLayout *fourthLayout;
    QWidget *fourthWidget;

    QTextEdit *textOrderConfirmed;
    QPushButton *buttonReturn;
    QHBoxLayout *layoutButtonReturn;
    QVBoxLayout *fifthLayout;
    QWidget *fifthWidget;

    QLabel *labelSearchTourist1;
    QLineEdit *lineSearchTourist1;

    QLabel *labelSearchTourist2;
    QLineEdit *lineSearchTourist2;

    QPushButton *go2_3;
    QPushButton *back1_1;
    QPushButton *back1_3;
    QHBoxLayout *layoutButtonGoBack2_3;
    QVBoxLayout *layoutSecond2;
    QWidget *second2Widget;

    QLabel *labelHintTour;
    QPushButton *go2_4;
    QPushButton *back2_2;
    QHBoxLayout *layoutButtonGoBack2_4;
    QVBoxLayout *layoutThird2;
    QWidget *third2Widget;

    QLabel *labelLocation;

    QVBoxLayout *layoutFourth2;
    QWidget *fourth2Widget;

    QPushButton *go3_3;
    QHBoxLayout *layoutButtonGoBack3_3;
    QVBoxLayout *layoutSecond3;
    QWidget *second3Widget;

    QLabel *labelStopoverTime;
    QLineEdit *lineStopoverTime;
    QPushButton *go3_4;
    QPushButton *back3_2;
    QHBoxLayout *thirdLayout3;
    QHBoxLayout *layoutButtonGoBack3_4;
    QVBoxLayout *layoutThird3;
    QWidget *third3Widget;

    QPushButton *buttonConfirmReturn;
    QPushButton *buttonCancelReturn;
    QHBoxLayout *layoutButtonConfirmReturn;
    QVBoxLayout *layoutFourth3;
    QWidget *fourth3Widget;

    QComboBox *lineStarting;
    QComboBox *lineDestination;
    QTextEdit *textContent;
    QTextEdit *textSearchContent;

    //QTextEdit *lineTextContent[N];

};


#endif
