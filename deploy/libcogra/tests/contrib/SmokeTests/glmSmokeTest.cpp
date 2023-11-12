/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#pragma warning( push )
#pragma warning( disable: 4310)
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#pragma warning (pop)

#include <gtest/gtest.h>

TEST(GLMSmokeTest, VectorAddition)
{
    glm::vec2 x(10, 20);
    glm::vec2 y(100, 100);
    glm::vec2 z = x + y;
    EXPECT_EQ(z.x, 110);
    EXPECT_EQ(z.y, 120);
}

namespace
{
    bool isInside(const glm::vec4& a)
    {
        return (-a.w < a.x) && (a.x < a.w) && 
               (-a.w < a.y) && (a.y < a.w) && 
               (-a.w < a.z) && (a.z < a.w);
    }
}

TEST(GLMSmokeTest, Frustum)
{
    const float near = -3;
    const float far = -13;
    const float bottom = -2;
    const float top = 1;
    const float left = -2;
    const float right = 3;
    glm::mat4 p = glm::frustum(left, right, bottom, top, -near, -far);
    {
        glm::vec4 a(0.0f, 0.0f, -8.0f, 1.0f);
        glm::vec4 pa = p * a;
        EXPECT_TRUE(isInside(pa));
        glm::vec4 b(-2.0f, 0.0f, -4.0f, 1.0f);
        glm::vec4 pb = p * b;
        EXPECT_TRUE(isInside(pb));
        glm::vec4 c(5.0f, 0.0f, -4.0f, 1.0f);
        glm::vec4 pc = p * c;
        EXPECT_FALSE(isInside(pc));

        pa /= pa.w;
        pb /= pb.w;
        pc /= pc.w;
    }

    {
        glm::vec4 lbn = p * glm::vec4(left, bottom, near, 1.0f);
        lbn /= lbn.w;
        EXPECT_FLOAT_EQ(lbn.x, -1.0f);
        EXPECT_FLOAT_EQ(lbn.y, -1.0f);
        EXPECT_FLOAT_EQ(lbn.z, -1.0f);

        glm::vec4 rbn = p * glm::vec4(right, bottom, near, 1.0f);
        rbn /= rbn.w;
        EXPECT_FLOAT_EQ(rbn.x, 1.0f);
        EXPECT_FLOAT_EQ(rbn.y, -1.0f);
        EXPECT_FLOAT_EQ(rbn.z, -1.0f);

        glm::vec4 ltn = p * glm::vec4(left, top, near, 1.0f);
        ltn /= ltn.w;
        EXPECT_FLOAT_EQ(ltn.x, -1.0f);
        EXPECT_FLOAT_EQ(ltn.y, 1.0f);
        EXPECT_FLOAT_EQ(ltn.z, -1.0f);

        glm::vec4 rtn = p * glm::vec4(right, top, near, 1.0f);
        rtn /= rtn.w;
        EXPECT_FLOAT_EQ(rtn.x, 1.0f);
        EXPECT_FLOAT_EQ(rtn.y, 1.0f);
        EXPECT_FLOAT_EQ(rtn.z, -1.0f);
    }
    {
        const float scale =  far / near;

        glm::vec4 lbf = p * glm::vec4(left * scale, bottom * scale, far, 1.0f);
        lbf /= lbf.w;
        EXPECT_FLOAT_EQ(lbf.x, -1.0f);
        EXPECT_FLOAT_EQ(lbf.y, -1.0f);
        EXPECT_FLOAT_EQ(lbf.z, 1.0f);

        glm::vec4 rbf = p * glm::vec4(right * scale, bottom * scale, far, 1.0f);
        rbf /= rbf.w;
        EXPECT_FLOAT_EQ(rbf.x, 1.0f);
        EXPECT_FLOAT_EQ(rbf.y, -1.0f);
        EXPECT_FLOAT_EQ(rbf.z, 1.0f);

        glm::vec4 ltf = p * glm::vec4(left * scale, top * scale, far, 1.0f);
        ltf /= ltf.w;
        EXPECT_FLOAT_EQ(ltf.x, -1.0f);
        EXPECT_FLOAT_EQ(ltf.y, 1.0f);
        EXPECT_FLOAT_EQ(ltf.z, 1.0f);

        glm::vec4 rtf = p * glm::vec4(right * scale, top * scale, far, 1.0f);
        rtf /= rtf.w;
        EXPECT_FLOAT_EQ(rtf.x, 1.0f);
        EXPECT_FLOAT_EQ(rtf.y, 1.0f);
        EXPECT_FLOAT_EQ(rtf.z, 1.0f);
    }
}

