#include "controller.h"

float Controller::get0to1(const float &current, const float &factor)
{
    float result = current + (1/factor);
    if(result > 1)
        return 1;
    else
        return result;
}
float Controller::get1to0(const float &current, const float &factor)
{
    float result = current - (1/factor);
    if(result < 0)
        return 0;
    else
        return result;
}

QString Controller::getHours(const char* lbl, const int &secs)
{
    QString str(lbl);
    auto pmins = secs % 3600;
    auto psecs = pmins % 60;
    auto hrs = (secs - pmins)/3600;
    auto mins = (pmins-psecs)/60;

    str.append(QString::number(hrs));
    str.append(":");
    str.append(QString::number(mins));
    str.append(":");
    str.append(QString::number(psecs));
    return str;
}

void Controller::Update()
{
    switch (m_stage) {
    case Stage::Active:
    {
        m_activeSecs += 1;
        break;
    }
    case Stage::Inactive:
    {
        m_inactiveSecs += 1;
        break;
    }
    case Stage::Working:
    {
        m_workingSecs += 1;
        m_R = get0to1(m_R, TIMEOUT);
        m_G = get1to0(m_G, TIMEOUT);
        emit updateColor();
        if(m_R >= 1)
        {
            setStage(Stage::Inactive);
        }
        break;
    }
    default:
    {

    }
    }

}

void Controller::setStage(const Stage &stage)
{
    m_stage = stage;
    switch (m_stage) {
    case Stage::Active:
    {
        m_R = 0;
        m_G = 1;
        m_height = LARGE_H;
        m_width = LARGE_W;
        m_pos = POS_CNTR;
        m_bottomMargin = 0;
        m_active = getHours("Active: ", m_activeSecs);
        m_inactive = getHours("Inactive: ", m_inactiveSecs);
        m_working = getHours("Working: ", m_workingSecs);
        emit updateSize();
        emit updateColor();
        break;
    }
    case Stage::Inactive:
    {
        m_R = 1;
        m_G = 0;
        m_height = LARGE_H;
        m_width = LARGE_W;
        m_pos = POS_CNTR;
        m_bottomMargin = 0;
        m_active = getHours("Active: ", m_activeSecs);
        m_inactive = getHours("Inactive: ", m_inactiveSecs);
        m_working = getHours("Working: ", m_workingSecs);
        emit updateSize();
        emit updateColor();
        break;
    }
    case Stage::Working:
    {
        m_R = 0;
        m_G = 1;
        m_height = SMALL_H;
        m_width = SMALL_W;
        m_pos = POS_CRNR;
        m_bottomMargin = TASKBAR_HEIGHT;
        m_active = "";
        m_inactive = "";
        m_working = "";
        emit updateSize();
        emit updateColor();
        break;
    }
    default:{

    }
    }
}


void Controller::moveStage()
{
    switch (m_stage) {
    case Stage::Active:
    {
        setStage(Stage::Working);
        break;
    }
    case Stage::Inactive:
    {
        setStage(Stage::Active);
        break;
    }
    case Stage::Working:
    {
        setStage(Stage::Active);
        break;
    }
    default:{

    }
    }
}

Controller::Controller(QObject *parent) :
    QObject(parent),
    m_R(0),
    m_G(1),
    m_B(0),
    m_height(SMALL_H),
    m_width(SMALL_W),
    m_stage(Working),
    m_inactiveSecs(0),
    m_activeSecs(0),
    m_workingSecs(0),
    m_pos(1),
    m_bottomMargin(0),
    m_active(""),
    m_inactive(""),
    m_working("")
{
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(Update()));
    m_timer->start(1000);
}
