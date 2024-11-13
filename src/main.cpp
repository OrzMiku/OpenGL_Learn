#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include "shader.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// 窗口大小
const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // GLFW 初始化和配置
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                 // 主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                 // 次版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 核心模式

    // 创建窗口对象
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Learn_OpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // 设置窗口图标
    GLFWimage images[1];
    images[0].pixels = stbi_load("assets/textures/block.png", &images[0].width, &images[0].height, 0, 4);
    glfwSetWindowIcon(window, 1, images);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // GLAD 初始化
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 创建着色器程序
    Shader ourShader("assets/shaders/main.vs", "assets/shaders/main.fs");

    // 顶点数据
    float vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // 右上
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,  // 右下
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // 左下
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f   // 左上
    };

    unsigned int indices[] = {
        0, 1, 3, // 第一个三角形
        1, 2, 3, // 第二个三角形
    };

    /**
     * VBO 用来存储顶点数据
     * VAO 用来存储顶点属性配置
     * EBO 用来存储索引数据
     */
    unsigned int VBO, VAO, EBO;                                                      // 顶点缓冲对象 ID 顶点数组对象 ID 索引缓冲对象 ID
    glGenVertexArrays(1, &VAO);                                                      // 创建顶点数组对象
    glGenBuffers(1, &VBO);                                                           // 创建缓冲对象
    glGenBuffers(1, &EBO);                                                           // 创建索引缓冲对象
    glBindVertexArray(VAO);                                                          // 绑定顶点数组对象
    glBindBuffer(GL_ARRAY_BUFFER, VBO);                                              // 绑定缓冲对象
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);                                      // 绑定索引缓冲对象
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);       // 将顶点数据复制到缓冲中
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // 将索引数据复制到缓冲中

    /**
     * 表示顶点索引位置为0，有 3 个值，每个值为 float 类型，不需要标准化，步长为 8 个 float，偏移量为 0
     * glEnableVertexAttribArray的参数是顶点属性的位置值，这个值是在顶点着色器中使用 layout (location = 0) in vec3 aPos; 定义的
     */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0); // 设置顶点属性指针
    glEnableVertexAttribArray(0);                                                  // 启用顶点属性

    /**
     * 表示顶点索引位置为1，有 3 个值，每个值为 float 类型，不需要标准化，步长为 8 个 float，偏移量为 3 个 float
     * glEnableVertexAttribArray的参数是顶点属性的位置值，这个值是在顶点着色器中使用 layout (location = 1) in vec3 aColor; 定义的
     */
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float))); // 设置顶点属性指针
    glEnableVertexAttribArray(1);                                                                    // 启用顶点属性

    /**
     * 表示顶点索引位置为2，有 2 个值，每个值为 float 类型，不需要标准化，步长为 8 个 float，偏移量为 6 个 float
     * glEnableVertexAttribArray的参数是顶点属性的位置值，这个值是在顶点着色器中使用 layout (location = 2) in vec2 aTexCoord; 定义的
     */
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    /**
     * 已经将数据存入缓冲对象，不需要对 VBO 进行操作，可以解绑缓冲对象
     * 已经将 VAO 配置好了，不需要对 VAO 进行操作，可以解绑顶点数组对象
     */
    glBindBuffer(GL_ARRAY_BUFFER, 0); // 解绑缓冲对象，保证其他地方不会不小心使用它
    glBindVertexArray(0);             // 解绑顶点数组对象，保证其他地方不会不小心使用它

    // 材质
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // 绑定纹理
    // 设置纹理环绕方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // x 轴
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // y 轴
    // 设置纹理过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // 缩小
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);              // 放大
    // 加载纹理
    int width, height, nrChannels;
    unsigned char *data = stbi_load("assets/textures/block.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        // 生成纹理
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); // 生成纹理
        glGenerateMipmap(GL_TEXTURE_2D);                                                            // 生成多级渐远纹理
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    // 渲染循环
    while (!glfwWindowShouldClose(window))
    {
        // 输入
        processInput(window);

        // 渲染
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use(); // 使用着色器程序

        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);

        glm::mat4 transform = glm::mat4(1.0f);
        // 第一个矩形绘制
        transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        ourShader.setMat4("transform", transform);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // 第二个矩形绘制
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));
        float scaleAmount = sin(glfwGetTime());
        transform = glm::scale(transform, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
        ourShader.setMat4("transform", transform);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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