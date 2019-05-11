#pragma once
#include <memory>

namespace ZeEngine
{
    class IGameState;
    class IGameEngine
    {
    public:
        virtual ~IGameEngine() = default;

        virtual void End() = 0;
        virtual void SetPaused(bool paused) = 0;

        virtual void PushState(std::unique_ptr<IGameState> state) = 0;
        virtual void PopState() = 0;
    };
}