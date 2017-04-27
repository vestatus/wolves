#include "../inc/graphics/graphics.hpp"
#include "../inc/models/world.hpp"
#include "../inc/models/animals/animals.hpp"
#include <iostream>
#include <cstdio>

int main()
{

    // create the window
    SFMLManager manager("Wolves, hares and grass");
    Button button = Button(100, 100, 80, 20, "Click me!", [cout](){cout << "clicked\n";});
    button.save();



    World world;
    world.generate();
    world.spawnGrass();

    Animal::spawnAnimals(&world);
    
    manager.drawWorld(world);

    // run the main loop
    while (manager.windowIsOpen())
    {
        manager.checkEvent();
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
