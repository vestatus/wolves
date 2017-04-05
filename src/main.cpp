#include "../inc/graphics/graphics.hpp"
#include "../inc/models/world.hpp"
#include "../inc/models/animals.hpp"
#include <iostream>
#include <cstdio>

int main()
{

    // create the window
    SFMLManager manager("Wolves, hares and grass");
    World world;
    world.generate();
    world.spawnGrass();

    Animal::spawnAnimals(&world);
    
    manager.drawWorld(world);

    // run the main loop
    while (manager.windowIsOpen())
    {
        // handle events
        if (!manager.checkCloseEvent()) {
            
            Animal::takeTurns();


            world.tick();
            
            manager.drawWorld(world);

            // draw it
            manager.render();
        }
    }

    return 0;
}
