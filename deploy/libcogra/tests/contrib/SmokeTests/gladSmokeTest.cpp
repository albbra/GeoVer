/// Cogra --- Coburg Graphics Framework 2017
/// (C) 2017 by Quirin Meyer
/// quirin.meyer@hs-coburg.de
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gtest/gtest.h>

namespace
{
    void error(int /*errnum*/, const char * /*errmsg*/)
    {
        glfwTerminate();
        FAIL();
    }
}

TEST(GLEWSmokeTest, SimpleWindowComesUp)
{
    EXPECT_EQ(glfwInit(), GLFW_TRUE);
    GLFWwindow* window = glfwCreateWindow(640, 480, "GLFW Smoke Test", nullptr, nullptr);
    //EXPECT_NE(window, nullptr);
    glfwSetErrorCallback(error);

    glfwMakeContextCurrent(window);    
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    int frames = 0;
    const int maxFrames = 16;
    while(frames < maxFrames)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
        frames++;
    }
    EXPECT_EQ(frames, maxFrames);
    glfwTerminate();
}
