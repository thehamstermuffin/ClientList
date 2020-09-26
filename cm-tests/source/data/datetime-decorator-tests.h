#ifndef DATETIMEDECORATORTESTS_H
#define DATETIMEDECORATORTESTS_H

#include <QtTest>

#include <data/datetime-decorator.h>
#include <test-suite.h>

namespace cm {
namespace data {

class DateTimeDecoratorTests : public TestSuite
{
    Q_OBJECT
public:
    DateTimeDecoratorTests();

private slots:
    void constructor_givenNoParameters_setsDefaultProperties();
    void constructor_givenParameters_setsProperties();
    void setValue_givenNewValue_updatesValueAndEmitsSignal();
    void setValue_givenSameValue_takesNoAction();
    void jsonValue_whenDefaultValues_returnsJson();
    void jsonValue_whenValueSet_returnsJson();
    void update_whenPresentInJson_updatesValue();
    void update_whenNotPresentInJson_updatesValueToDefault();


private:
    QDateTime testDate{QDate(2020, 9, 26), QTime(16, 40, 32)};
};

}}
#endif // DATETIMEDECORATORTESTS_H
