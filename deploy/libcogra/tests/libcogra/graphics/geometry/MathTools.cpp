/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <iostream>
#include <cogra/graphics/geometry/MathTools.h>
#include <gtest/gtest.h>

using namespace cogra::graphics::geometry;

namespace
{
    template<class T>
    void expectMatrixFloatEqual(const T& a, const T& b, const typename T::value_type eps = 1.0f / (65536.0f))
    {
        for(auto i = 0; i < a.length(); i++)
        {
            for(auto j = 0; j < a[i].length(); j++)
            {
                EXPECT_EQ(std::abs(a[i][j] - b[i][j]) < eps, true);
            }
        }
    }
}

TEST(PerspectiveMatrixInverseTests, PerspectiveInverseTimesPerspective_IsIdentity_VaryFovy)
{
    const float aspect = 16.0f / 9.0f;
    const float near = 1.0f / 256.0f;
    const float far = 256.0f;

    for(auto d = 10.0f; d < 300.0f; d += 10.0f)
    {
        const float fovy = glm::radians(d);
        const auto p = glm::perspective(fovy, aspect, near, far);
        const auto pinv = perspectiveInverse<float>(fovy, aspect, near, far);
        const auto shouldBeId = p * pinv;
        expectMatrixFloatEqual(shouldBeId, glm::mat4());
    }
}

TEST(PerspectiveMatrixInverseTests, PerspectiveInfiniteInverseTimesPerspectiveInfinite_IsIdentity_VaryFovy)
{
    const float aspect = 16.0f / 9.0f;
    const float near = 1.0f / 256.0f;

    for(auto d = 10.0f; d < 300.0f; d += 10.0f)
    {
        const float fovy = glm::radians(d);
        const auto p = glm::infinitePerspective(fovy, aspect, near);
        const auto pinv = perspectiveInfinityInverse<float>(fovy, aspect, near);
        const auto shouldBeId = p * pinv;
        expectMatrixFloatEqual(shouldBeId, glm::mat4());
    }
}

TEST(PerspectiveMatrixInverseTests, PerspectiveInverseTimesPerspective_IsIdentity_VaryNearAndFarPlane)
{
    const float aspect = 16.0f / 9.0f;
    const float fovy = glm::radians(30.0f);

    for(auto near = 0.1f; near < 4.00; near += 0.1f)
    {
        for(auto far = near + 0.1f; far < 4.0f; far += 0.1f)
        {
            const auto p = glm::perspective(fovy, aspect, near, far);
            const auto pinv = perspectiveInverse<float>(fovy, aspect, near, far);
            const auto shouldBeId = p * pinv;
            expectMatrixFloatEqual(shouldBeId, glm::mat4());
        }
    }
}

TEST(PerspectiveMatrixInverseTests, PerspectiveInfiniteInverseTimesPerspectiveInfinite_IsIdentity_VaryNear)
{
    const float fovy = glm::radians(30.0f);
    const float aspect = 16.0f / 9.0f;

    for(auto near = 0.1f; near < 4.00; near += 0.1f)
    {
        const auto p = glm::infinitePerspective(fovy, aspect, near);
        const auto pinv = perspectiveInfinityInverse<float>(fovy, aspect, near);
        const auto shouldBeId = p * pinv;
        expectMatrixFloatEqual(shouldBeId, glm::mat4());
    }
}

TEST(PerspectiveMatrixInverseTests, PerspectiveInverseTimesPerspective_IsIdentity_VaryAspect)
{
    const float fovy = glm::radians(30.0f);
    const float near = 1.0f / 256.0f;
    const float far = 256.0f;

    for(auto aspect = 0.1f; aspect < 4.0f; aspect += 0.1f)
    {
        const auto p = glm::perspective(fovy, aspect, near, far);
        const auto pinv = perspectiveInverse<float>(fovy, aspect, near, far);
        const auto shouldBeId = p * pinv;
        expectMatrixFloatEqual(shouldBeId, glm::mat4());
    }
}

TEST(PerspectiveMatrixInverseTests, PerspectiveInfiniteInverseTimesPerspectiveInfinite_IsIdentity_VaryAspect)
{
    const float fovy = glm::radians(30.0f);
    const float near = 1.0f / 256.0f;

    for(auto aspect = 0.1f; aspect < 4.0f; aspect += 0.1f)
    {
        const auto p = glm::infinitePerspective(fovy, aspect, near);
        const auto pinv = perspectiveInfinityInverse<float>(fovy, aspect, near);
        const auto shouldBeId = p * pinv;
        expectMatrixFloatEqual(shouldBeId, glm::mat4());
    }
}
