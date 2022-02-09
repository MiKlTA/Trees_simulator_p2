#include "window.h"



Window *Window::m_instance = nullptr;



Window * Window::inst()
{
    if (m_instance == nullptr)
    {
        m_instance = new Window;
    }
    return m_instance;
}



glm::vec2 Window::comvertToWorldCoods(glm::ivec2 p)
{
    int height, width;
    glfwGetWindowSize(m_window, &width, &height);
    
    glm::vec2 t(p.x, height - p.y);
    t.x /= (width * 1.0f);
    t.y /= (height * 1.0f);
    
    glm::vec2 screenSize = m_viewSize * m_camScale;
    t *= screenSize;
    
    t += m_camPos - screenSize / 2.0f;
    return t;
}



void Window::startWindowCycle()
{
    glClearColor(0.1f, 0.05f, 0.15f, 1.0f);
    
    while (!glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();
        handleInputCameraMove();
        
        if (!m_paused)
            m_simcore->update();
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        m_simcore->render(m_viewMat, m_projMat);
        
        glfwSwapBuffers(m_window);
    }
}



// private:



Window::Window()
    : m_window(),
      m_monSize(),
      
      m_camPos(),
      m_camScale(),
      m_viewMat(),
      m_viewSize(),
      m_projMat(),
      m_mousePos(0.0f),
      
      m_simcore(),
      m_paused(true)
{
    glfwInit();
    
    {int x, y;
    glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(),
                           &x, &y, &m_monSize.x, &m_monSize.y);}
    m_window = glfwCreateWindow(
                m_monSize.x, m_monSize.y,
                "M is the b!",
                nullptr, nullptr
                );
    
    glfwSetKeyCallback(m_window, keyCallback);
    glfwSetCursorPosCallback(m_window, cursorPosCallback);
    glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
    
    glfwMakeContextCurrent(m_window);
    glfwMaximizeWindow(m_window);
    glfwSwapInterval(1);
    
    glewExperimental = true;
    glewInit();
    
    m_viewSize = glm::vec2(m_monSize.x/(m_monSize.y * 1.0f), 1.0f);
    m_camScale = defaultCamScale();
    updProjMat();
    m_camPos = defaultCamPos();
    updViewMat();
    
    m_simcore = new SimulationCore(this);
}

Window::~Window()
{
    delete m_simcore;
}



void Window::handleInputCameraMove()
{
    float dr = dCamPos() * m_camScale;
    
    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
    {
        m_camPos.x += dr;
        updViewMat();
    }
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
    {
        m_camPos.x -= dr;
        updViewMat();
    }
    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
    {
        m_camPos.y += dr;
        updViewMat();
    }
    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
    {
        m_camPos.y -= dr;
        updViewMat();
    }
    if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        m_camScale *= kCamScale();
        updProjMat();
    }
    if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS)
    {
        m_camScale /= kCamScale();
        updProjMat();
    }
}



void Window::updViewMat()
{
    m_viewMat = glm::translate(glm::mat4(1.0f), -glm::vec3(m_camPos, 0.0f));
}

void Window::updProjMat()
{
    m_projMat = glm::ortho(
                -m_viewSize.x/2.f * m_camScale, m_viewSize.x/2.f * m_camScale,
                -m_viewSize.y/2.f * m_camScale, m_viewSize.y/2.f * m_camScale
                           );
}



void Window::keyCallback(
        GLFWwindow *aWindow, int key, int scancode, int action, int mods
        )
{
    Window *w = Window::inst();
    
    switch (key)
    {
    case GLFW_KEY_Z:
        switch (action)
        {
        case GLFW_PRESS:
            w->m_camScale = defaultCamScale();
            w->updProjMat();
            w->m_camPos = defaultCamPos();
            w->updViewMat();
            break;
        }
    case GLFW_KEY_P:
        switch (action)
        {
        case GLFW_PRESS:
            w->m_paused = !w->m_paused;
            break;
        }
    }
    
    w->m_simcore->onKeyPress(key, action, mods);
}

void Window::cursorPosCallback(GLFWwindow *, double x, double y)
{
    Window *w = Window::inst();
    
    Window::inst()->m_mousePos = glm::vec2(x, y);
    w->m_simcore->onMouseMove(int(x), int(y));
}

void Window::mouseButtonCallback(
        GLFWwindow* window, int button, int action, int mods
        )
{
    Window *w = Window::inst();
    
    w->m_simcore->onMouseButtonPress(button, action, mods);
}
