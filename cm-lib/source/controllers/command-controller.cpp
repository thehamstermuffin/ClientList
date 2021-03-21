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
                   Client* _newClient,
                   ClientSearch* _clientSearch)
        : commandController(_commandController)
        , databaseController(_databaseController)
        , newClient(_newClient)
        , clientSearch(_clientSearch)
    {
        IDatabaseController* databaseController{nullptr};
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
    }
    //create instances of controllers
    CommandController* commandController{nullptr};

    IDatabaseController* databaseController{nullptr};
    Client* newClient{nullptr};
    Client* selectedClient{nullptr};
    ClientSearch* clientSearch{nullptr};
    QList<Command*> createClientViewContextCommands{};
    QList<Command*> findClientViewContextCommands{};
    QList<Command*> editClientViewContextCommands{};
};

CommandController::CommandController(QObject* parent,
                                     IDatabaseController* databaseController,
                                     Client* newClient,
                                     ClientSearch* clientSearch)
    : QObject(parent)
{
    implementation.reset(new Implementation(this, databaseController, newClient, clientSearch));
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
void CommandController::onCreateClientSaveExecuted()
{
    qDebug() << "You executed the Save command!";

    implementation->databaseController->createRow(implementation->newClient->key(),
                                                  implementation->newClient->id(),
                                                  implementation->newClient->toJson());
    qDebug() << "New client saved.";
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

void CommandController::setSelectedClient(Client *client)
{
    implementation->selectedClient = client;
}

}}
