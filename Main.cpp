#include <memory>
#include "World.h"


int main(void)
{
    auto App = std::make_unique<World>();

    App->Init();

    while (!App->ShouldClose())
    {
        App->Tick();

        while (App->ShouldTickFixed())
        {
            App->TickFixed();
        }

        App->Draw();
    }

    App->Exit();


    return 0;
}