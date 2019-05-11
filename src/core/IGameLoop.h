#pragma once
namespace ZeEngine
{
    class IGameEngineCore;
    class IGameLoop
    {
    public:
        virtual ~IGameLoop() = default;
        virtual void Loop(IGameEngineCore& engine) = 0;
    };
}