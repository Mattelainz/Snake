#include "GameApplication.hpp"
#include <iostream>

GameApplication::GameApplication() {
    graphics.initialize();
}

GameApplication::~GameApplication() {
    // Il cleanup viene gestito automaticamente dal distruttore di GraphicsManager
}

int GameApplication::run() {
    try {
        // Mostra il menu principale
        MainMenu menu(&graphics);
        MenuChoice choice = menu.show();
        
        // Gestisce la scelta dell'utente
        switch (choice) {
            case MenuChoice::PLAY: {
                // Avvia il gioco
                Game game(&graphics, 100, 50);
                game.run();
                break;
            }
            case MenuChoice::SETTINGS:
                // TODO: Implementare le impostazioni in futuro
                break;
            case MenuChoice::EXIT:
                break;
        }
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Errore durante l'esecuzione: " << e.what() << std::endl;
        return 1;
    }
}