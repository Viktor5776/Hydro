#include "BaseRuntime.h"
#include "../log/Log.h"
#include "../ioc/Container.h"
#include "../win/SDLWindow.h"
#include "../input/SDLInput.h"
#include "../scene/Components.h"
#include "../scene/Entity.h"
#include "SDL3/SDL.h"

namespace hydro::runtime
{
    BaseRuntime::BaseRuntime(const std::string& name)
        :
        scene_("Scene")
    {

        scene_.Deserialize("firstScene.json");

        //Init with SDL Window manager
        ioc::Get().Register<win::IWindow>([=] {
            return std::make_shared<win::SDLWindow>(std::pair{ 100,100 }, std::pair{ 640,360 }, name);
        });

        ioc::Get().Register<input::IInput>([] {
            return std::make_shared<input::SDLInput>();
        });
    }

    int BaseRuntime::Run()
    {
        auto pWin = ioc::Get().Resolve<win::IWindow>();
        auto pInput = std::dynamic_pointer_cast<input::SDLInput>(ioc::Get().Resolve<input::IInput>());

        pInput->LoadBindingsFromFile("BaseInputBindings.json");

        auto v = scene_.GetAllEntitiesWith<TagComponent>();
        for (auto e : v) {
            auto t = v.get<TagComponent>(e);
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

            //Test
            std::ostringstream ss;
            ss << std::fixed << std::setprecision(2); // 2 decimal places

            auto mouse = pInput->GetMouseState();

            // Position
            ss << "Position: [" << mouse.position.x << ", " << mouse.position.y << "] ";

            // Delta (movement)
            ss << "Delta: [" << mouse.delta.x << ", " << mouse.delta.y << "] ";

            // Scroll
            ss << "Scroll: [" << mouse.scroll.x << ", " << mouse.scroll.y << "] ";

            // Window state
            ss << (mouse.isInWindow ? "(In Window)" : "(Out of Window)");

            pWin->SetName(ss.str());

            if (pInput->IsActionPressed("Mouse4")) {
                pWin->SetPos({ 1,1 });
            }
        }

        return 0;
    }

}