#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>

#include "inits.h"

int main(int argc, char const *argv[])
{
    GLFW_Err_callback();
    if (!glfwInit())
        return 1;
    GLFW_versions();

    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "MY Imgui Test", nullptr, nullptr);
    //glfwSetWindowSizeLimits(window, 1280, 720, 1280, 720);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImVec4 clear_color = ImVec4(1,0,0,0.1);

    bool p_open = true;
    bool collapsed = false;
    while (!glfwWindowShouldClose(window) & p_open)
    {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // MainFrame
        {
            int w, h;
            glfwGetWindowSize(window, &w, &h);
            ImVec2 size(w, h);
            ImGui::SetNextWindowSize(size);
            ImGui::Begin("C/C++ ProjectManager", &p_open);

            
            ImVec2 winpos  = ImGui::GetWindowPos();
            int ox, oy;
            glfwGetWindowPos(window, &ox, &oy);
            ImVec2 winsize = ImGui::GetWindowSize();

            glfwSetWindowPos(window, ox + winpos.x, oy + winpos.y);
            glfwSetWindowSize(window, winsize.x, winsize.y);
            ImGui::SetWindowPos(ImVec2(0,0));


            //std::cout << "Pos: " << ox << " - " << winpos.x << " ; " << oy << " - " << winpos.y << std::endl;

            if (!ImGui::IsWindowCollapsed() && collapsed){
                std::cout << "UnCollapsed" << std::endl;
                ImVec2 collapse_size = ImGui::GetWindowSize();
                collapse_size.y += 100;
                glfwSetWindowSize(window, collapse_size.x, collapse_size.y);
            }

            collapsed = ImGui::IsWindowCollapsed();

            if (!collapsed){
                ImGui::Text("Hello World");
                if (ImGui::Button("Configure")){
                    std::cout << "Configure" << std::endl;
                }

                if (ImGui::Button("Build and Debug")){
                    std::cout << "Build and Debug" << std::endl;
                }

                ImGui::BeginTable("ExtraBtns", 3);
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                if (ImGui::Button("Build")){
                    std::cout << "Build" << std::endl;
                }
                ImGui::TableSetColumnIndex(1);
                if (ImGui::Button("Debug")){
                    std::cout << "Debug" << std::endl;
                }
                ImGui::TableSetColumnIndex(2);
                if (ImGui::Button("Run")){
                    std::cout << "Run" << std::endl;
                }
                ImGui::EndTable();
            }

            
            ImGui::End();
        }

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
    

    return 0;
}
