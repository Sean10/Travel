#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedLayout>
#include <QStackedWidget>
#include <QLineEdit>
#include <QRadioButton>
#include <QDialog>
#include <QMessageBox>
#include <QApplication>
#include <QLabel>
#include <QThread>

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
    QLineEdit  *lineStarting;

    QLabel *labelDestination;
    QLineEdit *lineDestination;

    QHBoxLayout *secondLayout1;
    QLabel *labelHint3;
    QLabel *labelStopoverCity2_1;
    QLineEdit *lineStopoverCity2_1;
    QLabel *labelStopoverTime2_1;
    QLineEdit *lineStopoverTime2_1;

    QLabel *labelStopoverCity;
    QLineEdit *lineStopoverCity;

    QHBoxLayout *secondLayout2;
    QVBoxLayout *secondLayout;
    QWidget *secondWidget;

    QPushButton *go3;
    QPushButton *back1;
    QHBoxLayout *layoutButtonGoBack2;

    QLabel *labelChooseStrategy;
    QRadioButton *strategyTime;
    QRadioButton *strategyValue;
    QRadioButton *strategyValueTime;
    QLineEdit *lineStrategyValueTime;
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

    QLabel *labelOrderConfirmed;
    QPushButton *buttonReturn;
    QHBoxLayout *layoutButtonReturn;
    QVBoxLayout *fifthLayout;
    QWidget *fifthWidget;

    QLabel *labelSearchTourist;
    QLineEdit *lineSearchTourist;
    QPushButton *go2_3;
    //QPushButton *back1;
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
};


#endif // MAINWINDOW_H
