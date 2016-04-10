#include "mainwindow.h"

Widget::Widget(QStackedWidget *parent)
    : QStackedWidget(parent)
{
    setWindowTitle("Travel Query Search System V1.0");
    CreateFirstPage();
    CreateSecondPage();
    CreateThirdPage();
    CreateFourthPage();
    CreateFifthPage();
    CreateSecond2Page();
    CreateThird2Page();
    CreateFourth2Page();
    CreateSecond3Page();
    CreateThird3Page();
    CreateFourth3Page();
}

Widget::~Widget()
{

}

void Widget::CreateFirstPage()
{

    label = new QLabel("Welcome to the Travel Query Search System V1.0!\n\n");
    labelHint = new QLabel("Please choose the following function:");

    layoutLeft = new QHBoxLayout;
    layoutLeft->addWidget(labelHint);

    buttonRoute = new QPushButton("Search travel route");
    buttonState = new QPushButton("Search tourist state");
    buttonPlanChange = new QPushButton("Change tourist's plan");

    connect(buttonRoute,SIGNAL(clicked()),this,SLOT(trans2()));
    connect(buttonState,SIGNAL(clicked(bool)),this,SLOT(trans2_2()));
    connect(buttonPlanChange,SIGNAL(clicked(bool)),this,SLOT(trans3_2()));

    firstLayout = new QVBoxLayout;
    firstLayout->addWidget(label);
    firstLayout->addLayout(layoutLeft);
    firstLayout->addWidget(buttonRoute);
    firstLayout->addWidget(buttonState);
    firstLayout->addWidget(buttonPlanChange);


    //setFixedHeight(sizeHint().height());


    firstWidget = new QWidget;
    firstWidget->setLayout(firstLayout);
    this->addWidget(firstWidget);

    layout = new QVBoxLayout;
    layout->addWidget(this);

}

void Widget::CreateSecondPage()
{

    labelHint2 = new QLabel(tr("Please input your travel plan:"));
    labelStarting = new QLabel(tr("Starting:"));
    lineStarting = new QLineEdit;
    labelStarting->setBuddy(lineStarting);

    labelDestination = new QLabel(tr("Destination:"));
    lineDestination = new QLineEdit;
    labelDestination->setBuddy(lineDestination);

    secondLayout1 = new QHBoxLayout;
    secondLayout1->addWidget(labelStarting);
    secondLayout1->addWidget(lineStarting);
    secondLayout1->addWidget(labelDestination);
    secondLayout1->addWidget(lineDestination);

    labelHint3 = new QLabel(tr("Please input the stopover cities:"));
    labelStopoverCity = new QLabel(tr("Stopover City:"));
    lineStopoverCity = new QLineEdit;
    labelStopoverCity->setBuddy(lineStopoverCity);

    go3 = new QPushButton(tr("&Go"));
    connect(go3,SIGNAL(clicked()),this,SLOT(trans3()));

    back1 = new QPushButton(tr("&Back"));
    connect(back1,SIGNAL(clicked(bool)),this,SLOT(trans1()));


    layoutButtonGoBack2 = new QHBoxLayout;
    layoutButtonGoBack2->addStretch();
    layoutButtonGoBack2->addWidget(go3);
    layoutButtonGoBack2->addWidget(back1);

    secondLayout2 = new QHBoxLayout;
    secondLayout2->addWidget(labelStopoverCity);
    secondLayout2->addWidget(lineStopoverCity);

    secondLayout = new QVBoxLayout;
    secondLayout->addWidget(label);
    secondLayout->addWidget(labelHint2);
    secondLayout->addLayout(secondLayout1);
    secondLayout->addWidget(labelHint3);
    secondLayout->addLayout(secondLayout2);
    secondLayout->addLayout(layoutButtonGoBack2);



    secondWidget = new QWidget;
    secondWidget->setLayout(secondLayout);
    this->addWidget(secondWidget);

}

void Widget::CreateThirdPage()
{
    labelChooseStrategy = new QLabel(tr("Please choose a following strategy:"));
    strategyTime = new QRadioButton(tr("The shortest time strategy"));
    strategyValue = new QRadioButton(tr("The minimum account strategy"));
    strategyValueTime = new QRadioButton("The minimum account within the limit time strategy");
    lineStrategyValueTime = new QLineEdit;
    //strategyValueTime->set();//wait for adding the lineEdit.

    go4 = new QPushButton(tr("&Go"));
    connect(go4,SIGNAL(clicked()),this,SLOT(trans4()));

    back2 = new QPushButton(tr("&Back"));
    connect(back2,SIGNAL(clicked(bool)),this,SLOT(trans2()));

    layoutButtonGoBack3 = new QHBoxLayout;
    layoutButtonGoBack3->addStretch();
    layoutButtonGoBack3->addWidget(go4);
    layoutButtonGoBack3->addWidget(back2);

    layoutStrategy = new QVBoxLayout;
    layoutStrategy->addWidget(labelChooseStrategy);
    layoutStrategy->addWidget(strategyTime);
    layoutStrategy->addWidget(strategyValue);
    layoutStrategy->addWidget(strategyValueTime);
    layoutStrategy->addWidget(lineStrategyValueTime);
    layoutStrategy->addLayout(layoutButtonGoBack3);

    thirdWidget = new QWidget;
    thirdWidget->setLayout(layoutStrategy);
    this->addWidget(thirdWidget);
    connect(go4,SIGNAL(clicked()),this,SLOT(trans4()));
    connect(back2,SIGNAL(clicked()),this,SLOT(trans2()));
}

void Widget::CreateFourthPage()
{
    labelOrder = new QLabel(tr("According to your travel plan and chosen strategy, "
                               "the route calculated is as following:"));
    buttonConfirm = new QPushButton(tr("Confirm the Order"));
    buttonCancel = new QPushButton(tr("Cancel the order"));

    connect(buttonConfirm,SIGNAL(clicked()),this,SLOT(Confirm()));
    connect(buttonCancel,SIGNAL(clicked()),this,SLOT(trans3()));

    layoutButtonConfirm = new QHBoxLayout;
    layoutButtonConfirm->addStretch();
    layoutButtonConfirm->addWidget(buttonConfirm);
    layoutButtonConfirm->addWidget(buttonCancel);

    fourthLayout = new QVBoxLayout;
    fourthLayout->addWidget(labelOrder);
    fourthLayout->addStretch();//wait for add commands;
    fourthLayout->addLayout(layoutButtonConfirm);

    fourthWidget = new QWidget;
    fourthWidget->setLayout(fourthLayout);
    this->addWidget(fourthWidget);



}

void Widget::CreateFifthPage()
{
    labelOrderConfirmed = new QLabel(tr("Dear No. %d tourist, your order has been confirmed,\n "
                                        "you can continue to search your state and log. Thanks for your use!"));

    buttonReturn = new QPushButton(tr("&Save&Return to Home Page"));
    connect(buttonReturn, SIGNAL(clicked(bool)), this, SLOT(trans1()));

    layoutButtonReturn = new QHBoxLayout;
    layoutButtonReturn->addStretch();
    layoutButtonReturn->addWidget(buttonReturn);

    fifthLayout = new QVBoxLayout;
    fifthLayout->addWidget(labelOrderConfirmed);
    fifthLayout->addStretch();
    fifthLayout->addLayout(layoutButtonReturn);

    fifthWidget = new QWidget;
    fifthWidget->setLayout(fifthLayout);
    this->addWidget(fifthWidget);

}


void Widget::CreateSecond2Page()
{
    labelSearchTourist = new QLabel(tr("Please input the tourist's number you want to search:"));

    lineSearchTourist = new QLineEdit;

    go2_3 = new QPushButton(tr("&Go"));
    connect(go2_3,SIGNAL(clicked(bool)), this,SLOT(trans2_3()));

    layoutButtonGoBack2_3 = new QHBoxLayout;
    layoutButtonGoBack2_3->addStretch();
    layoutButtonGoBack2_3->addWidget(go2_3);
    layoutButtonGoBack2_3->addWidget(back1);

    layoutSecond2 = new QVBoxLayout;
    layoutSecond2->addWidget(labelSearchTourist);
    layoutSecond2->addWidget(lineSearchTourist);
    layoutSecond2->addLayout(layoutButtonGoBack2_3);

    second2Widget = new QWidget;
    second2Widget->setLayout(layoutSecond2);
    this->addWidget(second2Widget);
}

void Widget::CreateThird2Page()
{
    labelHintTour = new QLabel(tr("Dear No. %d tourist:"));
/*
 *
 *Add the chosen information
 *
 */
    go2_4 = new QPushButton(tr("&Enter Real-Time Maps"));
    connect(go2_4,SIGNAL(clicked(bool)), this,SLOT(trans2_4()));

    back2_2 = new QPushButton(tr("&Back"));
    connect(back2_2,SIGNAL(clicked(bool)),this,SLOT(trans2_2()));

    layoutButtonGoBack2_4 = new QHBoxLayout;
    layoutButtonGoBack2_4->addStretch();
    layoutButtonGoBack2_4->addWidget(go2_4);
    layoutButtonGoBack2_4->addWidget(back2_2);

    layoutThird2 = new QVBoxLayout;
    layoutThird2->addWidget(labelHintTour);
    layoutThird2->addLayout(layoutButtonGoBack2_4);

    third2Widget = new QWidget;
    third2Widget->setLayout(layoutThird2);
    this->addWidget(third2Widget);

}

void Widget::CreateFourth2Page()
{
    layoutFourth2 = new QVBoxLayout;
    layoutFourth2->addStretch();
    layoutFourth2->addWidget(back1);

    fourth2Widget = new QWidget;
    fourth2Widget->setLayout(layoutFourth2);
    this->addWidget(fourth2Widget);

}

void Widget::CreateSecond3Page()
{
    go3_3 = new QPushButton(tr("&Go"));
    connect(go3_3,SIGNAL(clicked(bool)), this,SLOT(trans3_3()));

    layoutButtonGoBack3_3 = new QHBoxLayout;
    layoutButtonGoBack3_3->addStretch();
    layoutButtonGoBack3_3->addWidget(go3_3);
    layoutButtonGoBack3_3->addWidget(back1);

    layoutSecond3 = new QVBoxLayout;
    layoutSecond3->addWidget(labelSearchTourist);
    layoutSecond3->addWidget(lineSearchTourist);
    layoutSecond3->addLayout(layoutButtonGoBack3_3);

    second3Widget = new QWidget;
    second3Widget->setLayout(layoutSecond3);
    this->addWidget(second3Widget);

}

void Widget::CreateThird3Page()
{

    labelHint3 = new QLabel(tr("Please input the stopover cities:"));
    labelStopoverCity = new QLabel(tr("Stopover City:"));
    lineStopoverCity = new QLineEdit;
    labelStopoverCity->setBuddy(lineStopoverCity);
    labelStopoverTime = new QLabel(tr("Stopover Time:"));
    lineStopoverTime = new QLineEdit;
    labelStopoverTime->setBuddy(lineStopoverTime);

    go3_4 = new QPushButton(tr("&Go"));
    connect(go3_4,SIGNAL(clicked()),this,SLOT(trans3_4()));

    back3_2 = new QPushButton(tr("&Back"));
    connect(back3_2,SIGNAL(clicked(bool)),this,SLOT(trans3_2()));

    layoutButtonGoBack3_4 = new QHBoxLayout;
    layoutButtonGoBack3_4->addStretch();
    layoutButtonGoBack3_4->addWidget(go3_4);
    layoutButtonGoBack3_4->addWidget(back3_2);

    thirdLayout3 = new QHBoxLayout;
    thirdLayout3->addWidget(labelStopoverCity);
    thirdLayout3->addWidget(lineStopoverCity);
    thirdLayout3->addWidget(labelStopoverTime);
    thirdLayout3->addWidget(lineStopoverTime);

    layoutThird3 = new QVBoxLayout;
    layoutThird3->addWidget(label);
    layoutThird3->addWidget(labelHint2);
    layoutThird3->addLayout(secondLayout1);
    layoutThird3->addWidget(labelHint3);
    layoutThird3->addLayout(thirdLayout3);
    layoutThird3->addLayout(layoutButtonGoBack3_4);


    third3Widget = new QWidget;
    third3Widget->setLayout(layoutThird3);
    this->addWidget(third3Widget);

}

void Widget::CreateFourth3Page()
{
    buttonConfirmReturn = new QPushButton(tr("Confirm the Order"));
    buttonCancelReturn = new QPushButton(tr("Cancel the order"));

    connect(buttonConfirmReturn,SIGNAL(clicked()),this,SLOT(trans1()));//recharge the save function
    connect(buttonCancelReturn,SIGNAL(clicked()),this,SLOT(trans1()));

    layoutButtonConfirmReturn = new QHBoxLayout;
    layoutButtonConfirmReturn->addStretch();
    layoutButtonConfirmReturn->addWidget(buttonConfirmReturn);
    layoutButtonConfirmReturn->addWidget(buttonCancelReturn);

    layoutFourth3 = new QVBoxLayout;
    layoutFourth3->addWidget(labelOrder);
    layoutFourth3->addStretch();//wait for add commands;
    layoutFourth3->addLayout(layoutButtonConfirmReturn);

    fourth3Widget = new QWidget;
    fourth3Widget->setLayout(layoutFourth3);
    this->addWidget(fourth3Widget);
}

/*
void Widget::Go()
{

}

void Widget::Back()
{
    if(this->currentWidget() == secondWidget)
        this->setCurrentWidget(firstWidget);
}
*/
void Widget::trans1()
{
    this->setCurrentWidget(firstWidget);
}

void Widget::trans2()
{
    this->setCurrentWidget(secondWidget);
}

void Widget::trans3()
{
    this->setCurrentWidget(thirdWidget);
}

void Widget::trans4()
{
    this->setCurrentWidget(fourthWidget);
}

void Widget::trans5()
{
    this->setCurrentWidget(fifthWidget);
}

void Widget::Confirm()
{
    if(QMessageBox::Yes == QMessageBox::question(this,
                                                 tr("Question"),
                                                 tr("Do you Confirm your order again?"),
                                                 QMessageBox::Yes | QMessageBox::No,
                                                 QMessageBox::Yes))
    {
        trans5();
    }

}

void Widget::trans2_2()
{
    this->setCurrentWidget(second2Widget);
}

void Widget::trans2_3()
{
    this->setCurrentWidget(third2Widget);
}

void Widget::trans2_4()
{
    this->setCurrentWidget(fourth2Widget);
}

void Widget::trans3_2()
{
    this->setCurrentWidget(second3Widget);
}

void Widget::trans3_3()
{
    this->setCurrentWidget(third3Widget);
}

void Widget::trans3_4()
{
    this->setCurrentWidget(fourth3Widget);
}
