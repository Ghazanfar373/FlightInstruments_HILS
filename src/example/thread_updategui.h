#ifndef THREAD_UPDATEGUI_H
#define THREAD_UPDATEGUI_H

#include <QObject>
#include <QtCore>
#include <QThread>

class Thread_updateGUI : public QThread
{
    Q_OBJECT
public:
    explicit Thread_updateGUI(QObject *parent = 0);

    void run();
    bool stop;

signals:

    void Number_Changed(int);

public slots:
};

#endif // THREAD_UPDATEGUI_H
