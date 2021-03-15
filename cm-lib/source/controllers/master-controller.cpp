#include "master-controller.h"

using namespace cm::models;

namespace cm {
namespace controllers {

class MasterController::Implementation
{
public:
    Implementation(MasterController* _masterController) : masterController(_masterController)
    {
        databaseController = new DatabaseController(masterController);
        navigationController = new NavigationController(masterController);
        newClient = new Client(masterController);
        commandController = new CommandController(masterController, databaseController, newClient);
    }
    DatabaseController* databaseController{nullptr};
    MasterController* masterController{nullptr};
    CommandController* commandController{nullptr};
    NavigationController* navigationController{nullptr};
    Client* newClient{nullptr};
    QString welcomeMessage = "Welcome to the Client Management system!";
};

MasterController::MasterController(QObject* parent) : QObject(parent)
{
    implementation.reset(new Implementation(this));
}

MasterController::~MasterController()
{
}

NavigationController* MasterController::navigationController()
{
    return implementation->navigationController;
}

CommandController* MasterController::commandController()
{
    return implementation->commandController;
}

DatabaseController *MasterController::databaseController()
{
    return implementation->databaseController;
}

const QString& MasterController::welcomeMessage() const
{
    return implementation->welcomeMessage;
}

Client* MasterController::newClient()
{
    return implementation->newClient;
}

}}

