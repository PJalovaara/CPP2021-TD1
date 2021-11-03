#include "game.hpp"
#include "tower.hpp"


Game::Game(){
    // Creating a scene 
    scene = new QGraphicsScene(this);

    // Set the scene
    setScene(scene); // Visualize this scene

    // Create a new tower
    Tower* t = new Tower();

    // Add tower to the scene
    scene->addItem(t);
}