#include "Editor/EditorManager.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

#include "Editor/Windows/MainWindow.h"
#include "Editor/Windows/SceneWindow.h"
#include "Editor/Windows/GameWindow.h"
#include "Editor/Windows/ConsoleWindow.h"
#include "Editor/Windows/InspectorWindow.h"
#include "Editor/Windows/HierarchyWindow.h"
#include "Editor/Windows/ProjectWindow.h"

using namespace Galatea;

#pragma region Variables

int				EditorManager::windowPosX	{ 0 };
int				EditorManager::windowPosY	{ 0 };
unsigned int	EditorManager::windowWidth	{ 1024 };
unsigned int	EditorManager::windowHeight	{ 800 };

#pragma endregion


#pragma region Constructors/Destructors

EditorManager::EditorManager() noexcept
	: window{ nullptr }, io{ ImGui::GetIO() }
{}

EditorManager::~EditorManager() noexcept
{
    ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();
}

#pragma endregion

#pragma region External methods

void GLFWDebugCallBack(int, const char* msg) noexcept
{
	std::cout << msg << '\n';
}

#pragma endregion

#pragma region Methods

bool EditorManager::Init(float _version, const char* _glslVersion) noexcept
{
    if (!InitGLFW(_version))
        return false;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

    io.ConfigWindowsMoveFromTitleBarOnly = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(_glslVersion);

    InitWindows();
}

bool EditorManager::InitGLFW(float _version) noexcept
{
    glfwSetErrorCallback(GLFWDebugCallBack);

    if (!glfwInit())
    {
        printf("Error Init GLFW\n");
        return false;
    }

    if (_version)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, (int)_version);						// Major OpenGL version (4.)
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, (int)((_version - (int)_version) * 10));	// Minor OpenGL version (.5)
    }
       
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);							// Active OpenGL Debug

    glfwWindowHint(GLFW_SAMPLES, 16); // TODO Check optimization (enable antialiasing)

    if (!(window = glfwCreateWindow(1024, 800, "Galatea Editor", nullptr, nullptr)))
    {
        printf("Error Create Window\n");
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewInit();		// OpenGL Init

    glEnable(GL_MULTISAMPLE);	//TODO Check Optimization (enable antialiasing)

    glfwSetWindowPosCallback(window, EditorManager::WindowPosCallback);
    glfwSetWindowSizeCallback(window, EditorManager::WindowSizeCallback);

    glfwGetWindowPos(window, &windowPosX, &windowPosY);

    return true;
}

bool EditorManager::InitWindows() noexcept
{
    //editorWindows.push_back(new MainWindow());
    //editorWindows.push_back(new SceneWindow());
    //editorWindows.push_back(new GameWindow());
    //editorWindows.push_back(new ConsoleWindow());
    //editorWindows.push_back(new InspectorWindow());
    //editorWindows.push_back(new HierarchyWindow());
    //editorWindows.push_back(new ProjectWindow());
	return true;
}

void    EditorManager::MainLoop() noexcept
{
    bool isRunning = true;
    while (isRunning)
    {
        //glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        // Update windows
        for (std::vector<EditorWindow*>::iterator it = editorWindows.begin(); it != editorWindows.end(); ++it)
            (*it)->Update(windowPosX, windowPosY, windowWidth, windowHeight);

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.5f, 0.8f, 0.8f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update multiple viewports
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backupCurrentContext);
        }

        glfwSwapBuffers(window);

        // Update Inputs : TODO move?
        if (InputManager::GetInstance().IsKeyPress(GLFW_KEY_ESCAPE) || glfwWindowShouldClose(window))
            isRunning = false;
    }
}

void    EditorManager::WindowPosCallback(GLFWwindow* _window, int _x, int _y) noexcept
{
    EditorManager::windowPosX = _x;
    EditorManager::windowPosY = _y;
}

void    EditorManager::WindowSizeCallback(GLFWwindow* _window, int _width, int _height) noexcept
{
    EditorManager::windowWidth = _width;
    EditorManager::windowHeight = _height;
}

#pragma endregion