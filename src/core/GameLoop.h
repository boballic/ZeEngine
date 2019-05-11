#pragma once
#include "IGameLoop.h"

namespace ZeEngine
{
    class GameLoop :
        public IGameLoop
    {
    public:
        GameLoop();
        virtual ~GameLoop();

        // Inherited via IGameLoop
        virtual void Loop(IGameEngineCore& engine) override;
    };
}

