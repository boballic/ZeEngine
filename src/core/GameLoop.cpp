#include "GameLoop.h"
#include "IGameEngineCore.h"

#include <algorithm>
#include <chrono>
#include <thread>

namespace ZeEngine
{
    using namespace std;
    using namespace std::chrono;

    GameLoop::GameLoop()
    {
    }

    GameLoop::~GameLoop()
    {
        
    }

    void GameLoop::Loop(IGameEngineCore& engine)
    {
        constexpr int kTicksPerSecond = 25;
        const auto kSkipTicksMS = 1000 / kTicksPerSecond;
        constexpr auto kSkipTicks = milliseconds(kSkipTicksMS);
        constexpr int kMaxFrameSkip = 5;

        auto next_game_tick = high_resolution_clock::now();

        int loops;
        float interpolation;

        engine.Initialize();

        while (engine.IsRunning())
        {
            loops = 0;
            while (high_resolution_clock::now() > next_game_tick && loops < kMaxFrameSkip)
            {
                if (!engine.IsPaused())
                {
                    engine.Update();
                }

                //Constant update time
                next_game_tick += kSkipTicks;
                loops++;
            }

            interpolation = (float) ((duration_cast<milliseconds>(high_resolution_clock::now() - next_game_tick).count()) + kSkipTicksMS) / kSkipTicksMS;
            
            engine.Render(interpolation);
        }

        engine.Destroy();
    }
}
