#pragma once

#include <vector>
#include "core\IGameEngineCore.h"

class FakeEngineCore :
    public ZeEngine::IGameEngineCore
{
public:
    FakeEngineCore(int delay, bool pause, int loops);
    virtual ~FakeEngineCore();

    // Inherited via IGameEngineCore
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render(float interpolation) override;
    virtual void Destroy() override;
    virtual bool IsPaused() const override;
    virtual bool IsRunning() const override;

    int _initialize_count = 0;
    int _render_count = 0;
    int _update_count = 0;
    int _destroy_count = 0;
    float _interpolation = 0;
    bool _running;
    bool _pause;
    std::vector<float> _interpolation_values;

private:
    int _delay { 0 };
    int _loops{ 0 };
    int _total_loops{ 0 };

};

