#include <gtc/type_ptr.hpp>
#include <iostream>

#include "engine.h"
#include "stb_image.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


bool Engine::ui_active = true;

Engine::Engine(const int width, const int height) : width(width), height(height)
{
}

void Engine::init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "Solar System", NULL, NULL);
    if (window == nullptr)
    {
        std::cerr << "Failed to create GFLW window.\n";
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD.\n";
        return;
    }
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    /*glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);*/

    glClearColor(.25, .1, .65, 1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);

    // Initialize ImGui context
    IMGUI_CHECKVERSION();
	ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();
    ImGui::GetStyle().Colors[ImGuiCol_Text] = ImVec4(0.00f, 1.00f, 0.00f, 1.00f);

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460 core");

    skybox = new Skybox("resources/skybox/");
    skybox->init();
}

void Engine::render_skybox()
{
    skybox->render();
}

bool Engine::should_render() const
{
    return !glfwWindowShouldClose(window);
}

/// <summary>
/// Initialize ImGui frame and draw UI
/// </summary>
void Engine::draw_ui()
{
    // Initialize ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Draw UI
    if (ui_active)
    {
        //ImGui::ShowDemoWindow();

        // Copied from ImGui simple overlay in demo window
        static int location = 1;
        ImGuiIO& io = ImGui::GetIO();
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
        if (location >= 0)
        {
            const float PAD = 10.0f;
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
            ImVec2 work_size = viewport->WorkSize;
            ImVec2 window_pos, window_pos_pivot;
            window_pos.x = (location & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
            window_pos.y = (location & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
            window_pos_pivot.x = (location & 1) ? 1.0f : 0.0f;
            window_pos_pivot.y = (location & 2) ? 1.0f : 0.0f;
            ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
            window_flags |= ImGuiWindowFlags_NoMove;
        }
        else if (location == -2)
        {
            // Center window
            ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
            window_flags |= ImGuiWindowFlags_NoMove;
        }
        ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
        if (ImGui::Begin("Metrics", &ui_active, window_flags))
        {
            //IMGUI_DEMO_MARKER("Examples/Simple Overlay");
            ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::Text("%d vertices, %d indices (%d triangles)", io.MetricsRenderVertices, io.MetricsRenderIndices, io.MetricsRenderIndices / 3);
            ImGui::Text("%d visible windows, %d active allocations", io.MetricsRenderWindows, io.MetricsActiveAllocations);
            ImGui::Separator();
            if (ImGui::IsMousePosValid())
                ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
            else
                ImGui::Text("Mouse Position: <invalid>");
            if (ImGui::BeginPopupContextWindow())
            {
                if (ImGui::MenuItem("Custom", NULL, location == -1)) location = -1;
                if (ImGui::MenuItem("Center", NULL, location == -2)) location = -2;
                if (ImGui::MenuItem("Top-left", NULL, location == 0)) location = 0;
                if (ImGui::MenuItem("Top-right", NULL, location == 1)) location = 1;
                if (ImGui::MenuItem("Bottom-left", NULL, location == 2)) location = 2;
                if (ImGui::MenuItem("Bottom-right", NULL, location == 3)) location = 3;
                if (&ui_active && ImGui::MenuItem("Close")) ui_active = false;
                ImGui::EndPopup();
            }
        }
        ImGui::End();
    }
}

/// <summary>
/// Render ImGui frame
/// </summary>
void Engine::render_ui()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool Engine::should_render_ui() const
{
    return ui_active;
}

void Engine::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Engine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
        ui_active = !ui_active;

    std::vector move = { GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_D, GLFW_KEY_A, GLFW_KEY_SPACE, GLFW_KEY_LEFT_CONTROL };
    if (std::find(move.cbegin(), move.cend(), key) != move.cend())
        Scene::get_instance()->get_camera()->process_keyboard(key, action);
}

void Engine::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    Scene::get_instance()->get_camera()->process_mouse(xpos, ypos);
}

