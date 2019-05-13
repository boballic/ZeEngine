#pragma once
#include <memory>
#include <vector>
#include <stack>

#include "IGameEngine.h"
namespace ZeEngine
{
    class IGameState;
    class GameEngineStateMachine
    {
    public:
        void PushState(std::unique_ptr<IGameState> state);
        void PopState();

        void Initialize(IGameEngine& engine);
        void Update(IGameEngine& engine);
        void Render(IGameEngine& engine, float interpolation);
        void Destroy(IGameEngine& engine);

    private:
        std::stack<std::unique_ptr<IGameState>> _states;
        std::vector <std::unique_ptr<IGameState>> _states_to_push;
        int _states_to_pop {0};
    };
}

