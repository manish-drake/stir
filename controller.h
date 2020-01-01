#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>
enum Stage{
    Inactive,
    Active,
    Working
};

class Controller : public QObject
{
    Q_OBJECT
    const int SMALL_H = 20;
    const int SMALL_W = 100;
    const int LARGE_H = 700;
    const int LARGE_W = 1000;
    const int POS_CRNR = 1;
    const int POS_CNTR = 2;
    const float TIMEOUT = 3600;
    const int TASKBAR_HEIGHT = 50;


    QTimer* m_timer;
    float m_R, m_G, m_B;
    int m_height, m_width;
    Stage m_stage;
    void setStage(const Stage &stage);
    int m_inactiveSecs, m_activeSecs, m_workingSecs;
    int m_pos;
    static float get0to1(const float& current, const float& factor);
    static float get1to0(const float &current, const float &factor);
    int m_bottomMargin;
    QString m_active, m_inactive, m_working;
    QString getHours(const char *lbl, const int &secs);
public:
    Q_INVOKABLE void moveStage();
    Q_PROPERTY(float R READ R CONSTANT)
    float R()
    {
        return m_R;
    }
    Q_PROPERTY(float G READ G CONSTANT)
    float G()
    {
        return m_G;
    }
    Q_PROPERTY(float B READ B CONSTANT)
    float B()
    {
        return m_B;
    }

    Q_PROPERTY(int height READ height CONSTANT)
    int height()
    {
        return m_height;
    }
    Q_PROPERTY(int width READ width CONSTANT)
    int width()
    {
        return m_width;
    }
    Q_PROPERTY(int pos READ pos CONSTANT)
    int pos()
    {
        return m_pos;
    }
    Q_PROPERTY(int bottomMargin READ bottomMargin CONSTANT)
    int bottomMargin()
    {
        return m_bottomMargin;
    }
    Q_PROPERTY(QString active READ active CONSTANT)
    QString active()
    {
        return m_active;
    }
    Q_PROPERTY(QString inactive READ inactive CONSTANT)
    QString inactive()
    {
        return m_inactive;
    }
    Q_PROPERTY(QString working READ working CONSTANT)
    QString working()
    {
        return m_working;
    }
    explicit Controller(QObject *parent = nullptr);

signals:
    void updateColor();
    void updateSize();
public slots:
    void Update();
};

#endif // CONTROLLER_H
