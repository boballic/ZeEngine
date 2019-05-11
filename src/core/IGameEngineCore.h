#pragma once
namespace ZeEngine
{
    class IGameEngineCore
    {
    public:

        virtual ~IGameEngineCore() = default;

        virtual void Initialize() = 0;
        virtual void Update() = 0;
        virtual void Render(float interpolation) = 0;
        virtual void Destroy() = 0;

        virtual bool IsPaused() const = 0;
        virtual bool IsRunning() const = 0;
    };
}