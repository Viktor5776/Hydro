#include <core/app/Entrypoint.h>
#include <core/utility/Timer.h>


class App : public Hydro::app::Application
{
public:
    App();
private:
    void Update() override;
    void Render() override;
private:
    Hydro::utlity::Timer timer;
    static constexpr int WIDTH = 1280;
    static constexpr int HEIGHT = 720;

    int index = 0;
    float acc = 0;
};