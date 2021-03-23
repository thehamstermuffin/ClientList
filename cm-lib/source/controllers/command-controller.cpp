#include "command-controller.h"

#include <QList>
#include <QDebug>

using namespace cm::framework;
using namespace cm::models;

namespace cm {
namespace controllers {

class CommandController::Implementation
{
public:
    Implementation(CommandController* _commandController,
                   IDatabaseController* _databaseController,
                   NavigationController* _navigationController,
                   Client* _newClient,
                   ClientSearch* _clientSearch)
        : commandController(_commandController)
        , databaseController(_databaseController)
        , navigationController(_navigationController)
        , newClient(_newClient)
        , clientSearch(_clientSearch)
    {
        IDatabaseController* databaseController{nullptr};
        NavigationController* navigationController{nullptr};
        Client* newClient{nullptr};
        Command* createClientSaveCommand = new Command( commandController, QChar( 0xf0c7 ), "Save" );
        QObject::connect( createClientSaveCommand, &Command::executed,
                          commandController, &CommandController::onCreateClientSaveExecuted );
        createClientViewContextCommands.append( createClientSaveCommand );

        Command* findClientSearchCommand = new Command( commandController, QChar(0xf002), "Search");
        QObject::connect(findClientSearchCommand, &Command::executed,
                         commandController, &CommandController::onFindClientSearchExecuted);
        findClientViewContextCommands.append(findClientSearchCommand);

        Command* editClientSaveCommand = new Command( commandController, QChar(0xf0c7), "Save");
        QObject::connect(editClientSaveCommand, &Command::executed,
                         commandController, &CommandController::onEditClientSaveExecuted);
        editClientViewContextCommands.append(editClientSaveCommand);

        Command* editClientDeleteCommand = new Command( commandController, QChar(0xf235), "Delete");
        QObject::connect(editClientDeleteCommand, &Command::executed,
                         commandController, &CommandController::onEditClientDeleteExecuted);
        editClientViewContextCommands.append(editClientDeleteCommand);

        Command* rssRefreshCommand = new Command( commandController, QChar(0xf021), "Refresh");
        QObject::connect(rssRefreshCommand, &Command::executed,
                         commandController, &CommandController::onRssRefreshExecuted);
        rssViewContextCommands.append(rssRefreshCommand);
    }
    //create instances of controllers
    CommandController* commandController{nullptr};

    IDatabaseController* databaseController{nullptr};
    NavigationController* navigationController{nullptr};
    Client* newClient{nullptr};
    Client* selectedClient{nullptr};
    ClientSearch* clientSearch{nullptr};
    QList<Command*> createClientViewContextCommands{};
    QList<Command*> findClientViewContextCommands{};
    QList<Command*> editClientViewContextCommands{};
    QList<Command*> rssViewContextCommands{};
};

CommandController::CommandController(QObject* parent,
                                     IDatabaseController* databaseController,
                                     NavigationController* navigationController,
                                     Client* newClient,
                                     ClientSearch* clientSearch)
    : QObject(parent)
{
    implementation.reset(new Implementation(this, databaseController, navigationController, newClient, clientSearch));
}

CommandController::~CommandController()
{
}

QQmlListProperty<Command> CommandController::ui_createClientViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->createClientViewContextCommands);
}

QQmlListProperty<Command> CommandController::ui_findClientViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->findClientViewContextCommands);
}

QQmlListProperty<Command> CommandController::ui_editClientViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->editClientViewContextCommands);
}

QQmlListProperty<Command> CommandController::ui_rssViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->rssViewContextCommands);
}
void CommandController::onCreateClientSaveExecuted()
{
    qDebug() << "You executed the Save command!";

    implementation->databaseController->createRow(implementation->newClient->key(),
                                                  implementation->newClient->id(),
                                                  implementation->newClient->toJson());
    qDebug() << "New client saved.";

    implementation->clientSearch->searchText()->setValue(implementation->newClient->id());
    implementation->clientSearch->search();
    implementation->navigationController->goFindClientView();
}

void CommandController::onFindClientSearchExecuted()
{
    qDebug() << "You executed the Search command!";

    implementation->clientSearch->search();
}

void CommandController::onEditClientSaveExecuted()
{
    qDebug() << "You executed the Save command!";

    implementation->databaseController->updateRow(implementation->selectedClient->key(),
                                                  implementation->selectedClient->id(),
                                                  implementation->selectedClient->toJson());

    qDebug() << "Updated client saved!";
}

void CommandController::onEditClientDeleteExecuted()
{
    qDebug() << "You executed the Delete command!";

    implementation->databaseController->deleteRow(implementation->selectedClient->key(),
                                                  implementation->selectedClient->id());
    implementation->selectedClient = nullptr;

    qDebug() << "Client Deleted.";

    implementation->clientSearch->search();

    implementation->navigationController->goDashboardView();
}

void CommandController::setSelectedClient(Client *client)
{
    implementation->selectedClient = client;
}

void CommandController::onRssRefreshExecuted()
{
    qDebug() << "Refreshing RSS";
}

}}
