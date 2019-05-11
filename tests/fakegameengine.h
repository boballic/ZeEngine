#pragma once
#include "core\IGameEngine.h"

class FakeGameEngine : public ZeEngine::IGameEngine
{
public:
    FakeGameEngine();
    ~FakeGameEngine();

    // Inherited via IGameEngine
    virtual void End() override;
    virtual void SetPaused(bool paused) override;
    virtual void PushState(std::unique_ptr<ZeEngine::IGameState> state) override;
    virtual void PopState() override;
};

