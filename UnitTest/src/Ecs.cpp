#include "gtest_wrapper.h"
#include <Core\ecs\Ecs.h>
#include <Core\ioc\Singletons.h>

namespace Ecs
{

    struct Transform : public hydro::ecs::IComponent {
        float x = 0, y = 0;
        Transform() = default;
        Transform(float x, float y) : x(x), y(y) {};
    };

    struct Health : public hydro::ecs::IComponent {
        int hp = 0;
        Health() = default;
        Health(int hp) : hp(hp) {};
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

    TEST_F(ECSTests, SingleView) {
        auto reg = ioc::Sing().Resolve<ecs::Ecs>();  // Get registry

        // Create entities with components
        auto e1 = reg->createEntity();
        e1.addComponent(Transform{ 1.0f, 2.0f }); //e1: Transform only

        auto e2 = reg->createEntity();
        e2.addComponent<Health>();  // e2: Health only

        auto e3 = reg->createEntity();
        e3.addComponent<Transform>();  // e3: Transform only

        auto e4 = reg->createEntity();  // e4: No components

        // Get entities with Transform
        auto match = reg->view<Transform>();

        // Verify results
        EXPECT_EQ(match.front(), e1);
        EXPECT_EQ(match.back(), e3);
    }

    TEST_F(ECSTests, MultipleView) {
        auto reg = ioc::Sing().Resolve<ecs::Ecs>();  // Get registry

        // Create entities with components
        auto e1 = reg->createEntity();
        e1.addComponent(Transform{ 1.0f, 2.0f });
        e1.addComponent<Health>();  // e1: Transform + Health

        auto e2 = reg->createEntity();
        e2.addComponent<Health>();  // e2: Health only

        auto e3 = reg->createEntity();
        e3.addComponent<Transform>();  // e3: Transform only

        auto e4 = reg->createEntity();  // e4: No components

        // Get entities with BOTH Transform and Health
        auto match = reg->view<Transform, Health>();

        // Verify results
        EXPECT_EQ(match.front(), e1);
    }

}