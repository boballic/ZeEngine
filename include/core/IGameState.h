#pragma once
namespace ZeEngine
{
    class IGameEngine;
    class IGameState
    {
    public:
        virtual ~IGameState() = default;

        virtual void Initialize(IGameEngine& engine) = 0;
        virtual void PreUpdate(IGameEngine& engine) = 0;
        virtual void Update(IGameEngine& engine) = 0;
        virtual void PostUpdate(IGameEngine& engine) = 0;
        virtual void Destroy(IGameEngine& engine) = 0;
        virtual void Render(IGameEngine& engine, float interpolation) = 0;
    };
}