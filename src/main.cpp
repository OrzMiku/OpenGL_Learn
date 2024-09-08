#include <GLFW/glfw3.h>

int main(void)
{
    GLFWwindow* window;

    // 初始化 GLFW 库
    if (!glfwInit())
        return -1;

    // 创建一个窗口对象，其参数依次为：宽、高、窗口标题、显示模式、共享窗口
    window = glfwCreateWindow(500, 500, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // 将窗口的 OpenGL 上下文设置为当前上下文
    glfwMakeContextCurrent(window);

    // 循环渲染
    while (!glfwWindowShouldClose(window))
    {
        // 设置清空颜色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // 清空颜色缓冲
        glClear(GL_COLOR_BUFFER_BIT);

        // 绘制一个矩形
        glRectf(-0.5f, -0.5f, 0.5f, 0.5f);

        // 交换缓冲区
        glfwSwapBuffers(window);

        // 检查是否有事件触发
        glfwPollEvents();
    }

    // 释放窗口资源
    glfwTerminate();
    return 0;
}