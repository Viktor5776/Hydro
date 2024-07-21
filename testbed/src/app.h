#include <core/app/entrypoint.h>

class App : public Hydro::app::Application
{
public:
    App();
private:
    void Update() override;
    void Render() override;
private:
    static constexpr int WIDTH = 1280;
    static constexpr int HEIGHT = 720;
};