#include "core/IGameState.h"
#include "GameEngineStateMachine.h"

using namespace std;

namespace ZeEngine
{
    void GameEngineStateMachine::PushState(unique_ptr<IGameState> state)
    {
        _states_to_push.emplace_back(move(state));
    }

    void GameEngineStateMachine::PopState()
    {
        _states_to_pop++;
    }

    void GameEngineStateMachine::Initialize(IGameEngine& engine)
    {
        if (!_states.empty())
        {
            _states.top()->Initialize(engine);
        }
    }
    void GameEngineStateMachine::Update(IGameEngine& engine)
    {
        //Pop states 
        for(auto i = 0; i < _states_to_pop; ++i)
        {
            if (!_states.empty())
            {
                _states.top()->Destroy(engine);
                _states.pop();
            }
        }

        //Push states
        for (size_t i = 0; i < _states_to_push.size(); ++i)
        {
            _states.push(move(_states_to_push[i]));
            _states.top()->Initialize(engine);
        }

        _states_to_push.clear();
        _states_to_pop = 0;

        if (!_states.empty())
        {
            _states.top()->PreUpdate(engine);
            _states.top()->Update(engine);
            _states.top()->PostUpdate(engine);
        }
    }
    void GameEngineStateMachine::Render(IGameEngine& engine, float interpolation)
    {
        if (!_states.empty())
        {
            _states.top()->Render(engine, interpolation);
        }
    }
    void GameEngineStateMachine::Destroy(IGameEngine& engine)
    {
        while (!_states.empty())
        {
            _states.top()->Destroy(engine);
            _states.pop();
        }
    }
}
