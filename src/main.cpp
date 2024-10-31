#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shader.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{
    // 初始化 GLFW
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // 配置 GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                 // 主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                 // 次版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 核心模式

    // 创建窗口对象
    GLFWwindow *window = glfwCreateWindow(500, 500, "Hello World", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 初始化 GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 设置视口
    glViewport(0, 0, 500, 500);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader ourShader("./shaders/main.vs", "./shaders/main.fs");

    // 两个三角形组成一个矩形
    float vertices[] = {
        // 位置 颜色
        -0.5f,
        -0.5f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,

        0.5f,
        -0.5f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,

        0.0f,
        0.5f,
        0.0f,
        0.0f,
        0.0f,
        1.0f,
    };

    /**
     * VBO 用来存储顶点数据
     * VAO 用来存储顶点属性配置
     */
    unsigned int VBO, VAO;                                                     // 顶点缓冲对象 ID 和 顶点数组对象 ID
    glGenBuffers(1, &VBO);                                                     // 创建缓冲对象
    glGenVertexArrays(1, &VAO);                                                // 创建顶点数组对象
    glBindVertexArray(VAO);                                                    // 绑定顶点数组对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO);                                        // 绑定缓冲对象
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 将顶点数据复制到缓冲中

    /**
     * 表示顶点索引位置为0，有 3 个值，每个值为 float 类型，不需要标准化，步长为 6 个 float，偏移量为 0
     * glEnableVertexAttribArray的参数是顶点属性的位置值，这个值是在顶点着色器中使用 layout (location = 0) in vec3 aPos; 定义的
     */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0); // 设置顶点属性指针
    glEnableVertexAttribArray(0);                                                  // 启用顶点属性

    /**
     * 表示顶点索引位置为1，有 3 个值，每个值为 float 类型，不需要标准化，步长为 6 个 float，偏移量为 3 个 float
     * glEnableVertexAttribArray的参数是顶点属性的位置值，这个值是在顶点着色器中使用 layout (location = 1) in vec3 aColor; 定义的
     */
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float))); // 设置顶点属性指针
    glEnableVertexAttribArray(1);                                                                    // 启用顶点属性

    /**
     * 已经将数据存入缓冲对象，不需要对 VBO 进行操作，可以解绑缓冲对象
     * 已经将 VAO 配置好了，不需要对 VAO 进行操作，可以解绑顶点数组对象
     */
    glBindBuffer(GL_ARRAY_BUFFER, 0); // 解绑缓冲对象，保证其他地方不会不小心使用它
    glBindVertexArray(0);             // 解绑顶点数组对象，保证其他地方不会不小心使用它

    // 渲染循环
    while (!glfwWindowShouldClose(window))
    {
        // 输入
        processInput(window);

        // 渲染
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use(); // 使用着色器程序

        // 更新 uniform 颜色
        float timeValue = glfwGetTime(); // 获取时间
        int timeLocation = glGetUniformLocation(ourShader.ID, "time");
        glUniform1f(timeLocation, timeValue);

        glBindVertexArray(VAO);           // 绑定顶点数组对象
        glDrawArrays(GL_TRIANGLES, 0, 3); // 绘制三角形

        // 检查并调用事件，交换缓冲
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 释放资源
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}

// 窗口大小改变时调用
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// 处理输入
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}