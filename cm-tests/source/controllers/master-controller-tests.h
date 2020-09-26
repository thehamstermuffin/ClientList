#ifndef MASTERCONTROLLERTESTS_H
#define MASTERCONTROLLERTESTS_H

#include <QtTest>

#include <controllers/master-controller.h>
#include <test-suite.h>

namespace cm {
namespace controllers {

class MasterControllerTests : public TestSuite
{
    Q_OBJECT
public:
    MasterControllerTests();

private slots:
    //@brief called before the first test function is executed
    void initTestCase();
    //@brief called after the last test function was executed
    void cleanupTestCase();
    //@brief called before the each test function is executed
    void init();
    //@brief called every test function is executed
    void cleanup();

private slots:
    void welcomeMessage_returnsCorrectMessage();

private:
    MasterController masterController;
};

}}
#endif // MASTERCONTROLLERTESTS_H
