#include <gtc/type_ptr.hpp>
#include <iostream>

#include "engine.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "performance.h"
#include "stb_image.h"


Engine::~Engine()
{}

Engine::Engine()
{}

/// <summary>
/// Prepare and render given skybox
/// </summary>
/// <param name="skybox">Skybox to render</param>
void Engine::render_skybox(const Skybox& skybox) const
{
    int nb_vertices = skybox.prepare_for_render();

    glDrawArrays(GL_TRIANGLES, 0, nb_vertices);

    skybox.restore();
}

/// <summary>
/// Prepare and render given scene. All scene objects, as well as scene skybox, are being rendered
/// </summary>
/// <param name="scene">Scene to render</param>
void Engine::render(const Scene& scene) const
{
    Performance::reset_vertex_count();
    Performance::reset_index_count();

    for (auto obj : scene.objects)
    {
        obj->prepare_material();

        for (const auto mesh : obj->get_model()->get_meshes())
        {
            int nb_indices = mesh.prepare_for_render(*obj->get_material());

            glDrawElements(GL_TRIANGLES, nb_indices, GL_UNSIGNED_INT, 0);

            Performance::increment_index_count(mesh.indices.size());
            Performance::increment_vertex_count(mesh.vertices.size());
        }
    }

    render_skybox(*scene.skybox);
}

/// <summary>
/// Initialize ImGui frame and draw UI
/// </summary>
void Engine::draw_ui(bool ui_active)
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
            static double count = 0.0f;
            static double framerate = 0.0f;
            count += io.DeltaTime;
            if (count > .1f)
            {
                count = 0.0f;
                framerate = io.Framerate;
            }
            ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / framerate, framerate);
            //ImGui::Text("%d vertices, %d indices (%d triangles)", io.MetricsRenderVertices, io.MetricsRenderIndices, io.MetricsRenderIndices / 3);
            ImGui::Text("%d vertices, %d indices (%d triangles)", Performance::get_vertex_count(), Performance::get_index_count(), Performance::get_index_count() / 3);
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
