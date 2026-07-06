#include "Tuff.Backend/Backend.h"
#include "Tuff.Backend/GLFW/GLFW.h"
#include "Tuff.Core/Common/Common.h"
#include "Tuff.Core/Editor/Camera/Camera.h"
#include "Tuff.Core/Editor/Grid/Grid.h"

int main() {
    
    if (!Tuff::Backend::Init(API::OPENGL, 1920, 1080, "Tuff Sandbox")) {
        return -1;
    }
    
    Tuff::Core::Editor::Camera::Init();
    Tuff::Core::Editor::Grid::Init();
    
    while (Tuff::Backend::GLFW::WindowIsOpen()) {
        Tuff::Backend::BeginFrame();
        
        Tuff::Core::Editor::Camera::Update();
        Tuff::Core::Editor::Grid::Update();
        
        Tuff::Backend::EndFrame();
    }
    
}