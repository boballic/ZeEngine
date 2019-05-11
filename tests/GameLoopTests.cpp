#include "FakeEngineCore.h"
#include "core\GameLoop.h"

using namespace ZeEngine;

namespace CoreTests
{		
	/*TEST_CLASS(GameLoopTests)
	{
	public:

        TEST_METHOD(Start_Loop_ValidateInitializeCalled)
        {
            auto core = Loop(0);
            Assert::AreEqual(core._initialize_count, 1);
        }

        TEST_METHOD(Start_Loop_ValidateUpdateCalled)
        {
            auto core = Loop(0);
            Assert::AreEqual(core._update_count, 1);
        }

        TEST_METHOD(Start_Loop_ValidateRenderCalled)
        {
            auto core = Loop(0);
            Assert::AreEqual(core._render_count, 1);
        }
		TEST_METHOD(Start_Loop_ValidateDestroyCalled)
		{
            auto core = Loop(0);
            Assert::AreEqual(core._destroy_count, 1);
		}

        TEST_METHOD(Start_Loop_ValidateRenderWithDelay)
        {
            auto core = Loop(25);
            Assert::IsTrue(core._interpolation >= 0.0f && core._interpolation <= 1.0f);
        }

        TEST_METHOD(Start_Loop_ValidateRenderDelayInterpolation)
        {
            auto core = Loop(25, false, 10);

            for (auto interpolation : core._interpolation_values)
            {
                Assert::IsTrue(interpolation >= 0.0f && interpolation <= 1.0f);
            }
        }

        TEST_METHOD(Start_Loop_ValidateRenderNoDelayInterpolation)
        {
            auto core = Loop(0, false, 10);

            for (auto interpolation : core._interpolation_values)
            {
                Assert::IsTrue(interpolation >= 0.0f && interpolation <= 1.0f);
            }
        }

        TEST_METHOD(Start_Loop_ValidatePauseNoUpdate)
        {
            auto core = Loop(0, true, 0);
            Assert::AreEqual(core._update_count, 0);
        }

    private:
        FakeEngineCore Loop(int delay, bool pause = false, int loops = 1)
        {
            GameLoop l;
            FakeEngineCore core(delay, pause, loops);
            l.Loop(core);
            return core;
        }
	};*/
}