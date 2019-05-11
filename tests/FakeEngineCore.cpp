#include <chrono>
#include <thread>

#include "FakeEngineCore.h"

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

FakeEngineCore::FakeEngineCore(int delay, bool pause, int loops) : _running(true), _delay(delay), _pause(pause), _loops(loops)
{
}


FakeEngineCore::~FakeEngineCore()
{
}

void FakeEngineCore::Initialize()
{
    _initialize_count++;
}

void FakeEngineCore::Update()
{
    sleep_for(milliseconds(_delay));
    _total_loops++;
    _update_count++;
}

void FakeEngineCore::Render(float interpolation)
{
    _interpolation = interpolation;
    _interpolation_values.push_back(interpolation);

    _render_count++;

    if (_total_loops >= _loops)
    {
        _running = false;
    }
}

void FakeEngineCore::Destroy()
{
    _destroy_count++;
}

bool FakeEngineCore::IsPaused() const
{
    return _pause;
}

bool FakeEngineCore::IsRunning() const
{
    return _running;
}
