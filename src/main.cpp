#include "../inc/graphics/graphics.hpp"
#include "../inc/models/world.hpp"
#include "../inc/models/animals/animals.hpp"
#include <iostream>
#include <cstdio>

int main()
{
    BufferedLogger mainLogger("main");

    // create the window
    SFMLManager manager("Wolves, hares and grass");
    mainLogger.log("manager created", "SUCC");

    bool simulationRunning = true;

    Button button = Button(840, 0, 160, 40, "Pause", [&simulationRunning](Button* btn){
        simulationRunning = ! simulationRunning;
        btn->text = simulationRunning ? "Pause" : "Start";
    });
    button.save();

    mainLogger.log("buttons created", "SUCC");

    World world;
    mainLogger.log("creating world", "INFO");
    world.generate();
    mainLogger.log("spawning grass", "INFO");
    world.spawnGrass();


    button = Button(840, 40, 160, 40, "Restart", [&world, &manager](Button* btn){
        world.generate(); 
        world.spawnGrass(); 
        Animal::spawnAnimals(&world); 
        manager.drawWorld(world);
    });
    button.save();

    mainLogger.log("buttons created", "SUCC");

    Animal::spawnAnimals(&world);
    

    mainLogger.log("drawing the world for the first time", "INFO");
    manager.drawWorld(world);

    // run the main loop
    while (manager.windowIsOpen())
    {
        manager.checkEvent();
        // handle events

        if (!manager.checkCloseEvent()) {
            
            if (simulationRunning) {
                Animal::takeTurns();
                world.tick();
            }
            
            manager.drawWorld(world);

            // draw it
            manager.render();
        }
    }


    mainLogger.log("exiting successfully", "SUCC");

    return 0;
}
