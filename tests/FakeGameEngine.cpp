#include "FakeGameEngine.h"
#include "core\IGameState.h"
#include <memory>

using namespace std;
using namespace ZeEngine;

FakeGameEngine::FakeGameEngine()
{
}


FakeGameEngine::~FakeGameEngine()
{
}

void FakeGameEngine::End()
{
}

void FakeGameEngine::SetPaused(bool paused)
{
}

void FakeGameEngine::PushState(std::unique_ptr<IGameState> state)
{
}

void FakeGameEngine::PopState()
{
}
