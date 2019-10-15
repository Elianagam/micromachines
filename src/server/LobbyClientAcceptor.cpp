//
// Created by leobellaera on 13/10/19.
//

#include "LobbyClientAcceptor.h"
#include "SocketException.h"
#include "LobbyClientReceptionist.h"

LobbyClientAcceptor::LobbyClientAcceptor(int backlog, const char* port, GamesAdministrator& gamesOrganizer) :
        socketAcceptor(backlog, port),
        gamesOrganizer(gamesOrganizer),
        keepRunning(true) {}

void LobbyClientAcceptor::run() {
    while (keepRunning) {
        try {
            Socket peerSocket = socketAcceptor.accept();
            LobbyClientReceptionist* receptionist = new LobbyClientReceptionist(peerSocket, gamesOrganizer);
            receptionist->start();
            receptionists.push_back(receptionist);
            this->deleteDeadReceptionists();
        } catch(const SocketException& e) {
            //stderr print??!!
            return;
        }
    }
}

void LobbyClientAcceptor::deleteDeadReceptionists() {
    auto it = receptionists.begin();
    while (it != receptionists.end()) {
        if ((*it)->isDead()) {
            ++it;
        } else {
            (*it)->join();
            delete (*it);
            it = receptionists.erase(it);
        }
    }
}

void LobbyClientAcceptor::stop() {
    keepRunning = false;
    int size = receptionists.size();
    for (int i = 0; i < size; i++) {
        receptionists[i]->stop();
        receptionists[i]->join();
        delete receptionists[i];
    }
    socketAcceptor.close();
}

LobbyClientAcceptor::~LobbyClientAcceptor() {}
