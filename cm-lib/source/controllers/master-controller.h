#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QObject>

class MasterController : public QObject
{
    Q_OBJECT
public:
    explicit MasterController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MASTERCONTROLLER_H
