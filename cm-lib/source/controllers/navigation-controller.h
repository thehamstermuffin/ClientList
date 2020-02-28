#ifndef NAVIGATIONCONTROLLER_H
#define NAVIGATIONCONTROLLER_H

#include <QObject>
#include <models/client.h>
#include <cm-lib_global.h>

namespace cm {
namespace controllers {
class CMLIBSHARED_EXPORT NavigationController : public QObject
{
    Q_OBJECT
public:
    explicit NavigationController(QObject* parent = nullptr)
        : QObject(parent)
    {}
signals:
    void goCreateClientView();
    void goDashboardView();
    void goEditClientView(cm::models::Client* client);
    void goFindClientView();
};
}
}

#endif // NAVIGATIONCONTROLLER_H
