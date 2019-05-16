#include <thread>

#include "GameEngine.h"
#include "GameLoop.h"
#include "core/IGameState.h"

using namespace std;

namespace ZeEngine
{
    void GameEngine::Start(unique_ptr<IGameState> initialState)
    {
        _running = true;
        PushState(move(initialState));
        _loop.Loop(*this);
    }

    void GameEngine::End()
    {
        _running = false;
    }

    void GameEngine::SetPaused(bool paused)
    {
        _paused = paused;
    }

    void GameEngine::PushState(unique_ptr<IGameState> state)
    {
        _state.PushState(move(state));
    }

    void GameEngine::PopState()
    {
        _state.PopState();
    }

    bool GameEngine::IsPaused() const
    {
        return _paused;
    }

    bool GameEngine::IsRunning() const
    {
        return _running;
    }

    void GameEngine::Initialize()
    {
        _state.Initialize(*this);
    }
    void GameEngine::Update()
    {
        _state.Update(*this);
    }
    void GameEngine::Render(float interpolation)
    {
        _state.Render(*this, interpolation);
    }
    void GameEngine::Destroy()
    {
        _state.Destroy(*this);
    }
}
