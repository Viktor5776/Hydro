#include "BaseRuntime.h"
#include "../log/Log.h"
#include "../ioc/Container.h"
#include "../win/SDLWindow.h"
#include "../input/SDLInput.h"
#include  "../ioc/Singletons.h"
#include "../ecs/Ecs.h"
#include "SDL3/SDL.h"

#include <iostream>

namespace hydro::runtime
{
    class Player : public ecs::IScript
    {
        int t = 0;

        void Start() override
        {
            t = 10;
        }

        void Update() override
        {
            t--;
        }
    };

    BaseRuntime::BaseRuntime(const std::string& name)
    {
        //Init with SDL Window manager
        ioc::Get().Register<win::IWindow>([=] {
            return std::make_shared<win::SDLWindow>(std::pair{ 100,100 }, std::pair{ 640,360 }, name);
        });

        ioc::Get().Register<input::IInput>([] {
            return std::make_shared<input::SDLInput>();
        });

        ioc::Sing().Register<ecs::Ecs>([] {
            return std::make_shared<ecs::Ecs>();
        });
    }

    int BaseRuntime::Run()
    {
        auto pWin = ioc::Get().Resolve<win::IWindow>();
        auto pInput = std::dynamic_pointer_cast<input::SDLInput>(ioc::Get().Resolve<input::IInput>());

        pInput->LoadBindingsFromFile("BaseInputBindings.json");




        auto ecs = ioc::Sing().Resolve<ecs::Ecs>();

        auto e = ecs->createEntity();
        e.addComponent<Player>();


        for (auto script : ecs->GetScripts()) {
            script->Start();
        }

        bool quiting = false;
        while (!quiting) {
            
            pInput->Update();

            SDL_Event event;

            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) {
                    quiting = true;
                }

                pInput->UpdateEvent(event);
            }

            //Run systems
            for (auto script : ecs->GetScripts()) {
                script->Update();
            }

        }

        return 0;
    }

}