#include "gtest_wrapper.h"
#include <Core\ecs\Ecs.h>
#include <Core\ioc\Singletons.h>

namespace Ecs
{

    struct Transform {
        float x = 0, y = 0;
    };

    struct Health {
        int hp = 0;
    };

    using namespace hydro;

    class ECSTests : public ::testing::Test {
    protected:
        void SetUp() override
        {
            ioc::Sing().Register<ecs::Ecs>([] {
                return std::make_shared<ecs::Ecs>();
            });
        }
    };

    TEST_F(ECSTests, CreateEntityGivesValidId) {
        auto e = ioc::Sing().Resolve<ecs::Ecs>()->createEntity();
        EXPECT_GT(e.getId(), 0);
    }

    TEST_F(ECSTests, AddAndGetComponent) {
        auto e = ioc::Sing().Resolve<ecs::Ecs>()->createEntity();
        e.addComponent(Transform{ 1.0f, 2.0f });

        auto t = e.getComponent<Transform>();
        ASSERT_NE(t, nullptr);
        EXPECT_FLOAT_EQ(t->x, 1.0f);
        EXPECT_FLOAT_EQ(t->y, 2.0f);
    }

    TEST_F(ECSTests, RemoveComponent) {
        auto e = ioc::Sing().Resolve<ecs::Ecs>()->createEntity();
        e.addComponent(Health{ 100 });
        e.removeComponent<Health>();

        EXPECT_EQ(e.getComponent<Health>(), nullptr);
        EXPECT_FALSE(e.hasComponent<Health>());
    }

    TEST_F(ECSTests, ComponentOverwrite) {
        auto e = ioc::Sing().Resolve<ecs::Ecs>()->createEntity();
        e.addComponent(Transform{ 1.0f, 2.0f });
        e.addComponent(Transform{ 3.0f, 4.0f }); // Overwrite

        auto t = e.getComponent<Transform>();
        ASSERT_NE(t, nullptr);
        EXPECT_FLOAT_EQ(t->x, 3.0f);
        EXPECT_FLOAT_EQ(t->y, 4.0f);
    }

    TEST_F(ECSTests, DestroyEntityCleansUpComponents) {
        auto e = ioc::Sing().Resolve<ecs::Ecs>()->createEntity();
        e.addComponent(Transform{ 1, 2 });
        ioc::Sing().Resolve<ecs::Ecs>()->destroyEntity(e);

        EXPECT_EQ(ioc::Sing().Resolve<ecs::Ecs>()->getComponent<Transform>(e), nullptr);
        EXPECT_FALSE(ioc::Sing().Resolve<ecs::Ecs>()->hasComponent<Transform>(e));
    }

    TEST_F(ECSTests, ReuseEntityId) {
        auto e1 = ioc::Sing().Resolve<ecs::Ecs>()->createEntity();
        auto id1 = e1.getId();
        ioc::Sing().Resolve<ecs::Ecs>()->destroyEntity(e1);

        auto e2 = ioc::Sing().Resolve<ecs::Ecs>()->createEntity();
        auto id2 = e2.getId();

        EXPECT_EQ(id1, id2); // Should reuse ID
    }

}