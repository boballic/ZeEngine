#include "CppUnitTest.h"
#include <memory>

#include "FakeEngineCore.h"
#include "FakeGameEngine.h"

#include "core\GameLoop.h"
#include "core\GameEngine.h"
#include "core\GameEngineStateMachine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ZeEngine;
using namespace std;

namespace CoreTests
{
    //class FakeGameState : public IGameState
    //{
    //public:

    //    // Inherited via IGameState
    //    virtual void Initialize(IGameEngine & engine) override
    //    {
    //        _initialize_count++;
    //    }
    //    virtual void PreUpdate(IGameEngine & engine) override
    //    {
    //        _preupdate_count++;
    //    }
    //    virtual void Update(IGameEngine & engine) override
    //    {
    //        _update_count++;
    //    }
    //    virtual void PostUpdate(IGameEngine & engine) override
    //    {
    //        _post_update_count++;
    //    }
    //    virtual void Destroy(IGameEngine & engine) override
    //    {
    //        _destroy_count++;
    //    }
    //    virtual void Render(IGameEngine & engine, float interpolation) override
    //    {
    //        _render_count++;
    //    }

    //    int _initialize_count;
    //    int _preupdate_count;
    //    int _update_count;
    //    int _post_update_count;
    //    int _destroy_count;
    //    int _render_count;
    //};

    //TEST_CLASS(StateTests)
    //{
    //public:

    //    TEST_METHOD(State_ValidatePush_MovesToNextState)
    //    {
    //        GameEngineStateMachine machine;
    //        FakeGameEngine engine;

    //        PushState<FakeGameState>(machine);
    //        auto rawPtr = PushState<FakeGameState>(machine);

    //        machine.Update(engine);

    //        Assert::AreEqual(1, rawPtr->_initialize_count);
    //    }

    //    TEST_METHOD(State_ValidatePush_PreviousStateNotUpdated)
    //    {
    //        GameEngineStateMachine machine;
    //        FakeGameEngine engine;

    //        auto rawPtr = PushState<FakeGameState>(machine);
    //        PushState<FakeGameState>(machine);

    //        machine.Update(engine);

    //        Assert::AreEqual(0, rawPtr->_update_count);
    //    }

    //    TEST_METHOD(State_ValidatePush_ValidateOneState)
    //    {
    //        GameEngineStateMachine machine;
    //        FakeGameEngine engine;

    //        auto rawPtr = PushState<FakeGameState>(machine);
    //        machine.Update(engine);

    //        Assert::AreEqual(1, rawPtr->_initialize_count);
    //    }

    //    TEST_METHOD(State_ValidatePushAndPop_ProperState)
    //    {
    //        GameEngineStateMachine machine;
    //        FakeGameEngine engine;

    //        auto rawPtr = PushState<FakeGameState>(machine);
    //        PushState<FakeGameState>(machine);

    //        machine.Update(engine);
    //        machine.PopState();
    //        machine.Update(engine);

    //        Assert::AreEqual(1, rawPtr->_update_count);
    //    }

    //    TEST_METHOD(State_ValidateNoStates_NoCrash)
    //    {
    //        GameEngineStateMachine machine;
    //        FakeGameEngine engine;

    //        //Test for crash, shouldnt happen
    //        machine.Update(engine);

    //        Assert::IsTrue(true);
    //    }

    //    TEST_METHOD(State_ValidatePopNoStates_NoCrash)
    //    {
    //        GameEngineStateMachine machine;
    //        FakeGameEngine engine;
    //   
    //        machine.PopState();

    //        //Test for crash, shouldnt happen
    //        machine.Update(engine);

    //        Assert::IsTrue(true);
    //    }

    //    template <typename T>
    //    T* PushState(GameEngineStateMachine& machine)
    //    {
    //        auto state = make_unique<T>();
    //        auto rawPtr = state.get();
    //        machine.PushState(move(state));
    //        return rawPtr;
    //    }
    //};
}