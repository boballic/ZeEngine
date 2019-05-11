#pragma once
#include <stack>

#include "GameLoop.h"
#include "IGameState.h"
#include "IGameEngine.h"
#include "IGameEngineCore.h"
#include "GameEngineStateMachine.h"

namespace ZeEngine
{
    class IGameState;
    class GameEngine : public IGameEngine, public IGameEngineCore
    {
    public: 
        GameEngine(const GameEngine& rhs) = delete;
        GameEngine& operator=(const GameEngine& rhs) = default;

        // Inherited via IGameEngine
        virtual void Start(std::unique_ptr<IGameState> initialState);
        virtual void End() override;
        virtual void PushState(std::unique_ptr<IGameState> state) override;
        virtual void PopState() override;

        virtual void SetPaused(bool paused) override;
        virtual bool IsPaused() const override;
        virtual bool IsRunning() const override;

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void Render(float interpolation) override;
        virtual void Destroy() override;

    private:
        bool _running {false};
        bool _paused {false};
        GameLoop _loop;
        GameEngineStateMachine _state;
    };
}

