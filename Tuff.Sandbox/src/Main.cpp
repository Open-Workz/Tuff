#include "Sandbox/Sandbox.h"
#include "Tuff.Backend/Backend.h"
#include "Tuff.Backend/GLFW/GLFW.h"
#include "Tuff.Core/Common/Common.h"

int main() {
    
    if (!Tuff::Backend::Init(API::OPENGL, 1920, 1080, "Tuff Sandbox")) {
        return -1;
    }
    
    Sandbox::Init();
    
    while (Tuff::Backend::GLFW::WindowIsOpen()) {
        Tuff::Backend::BeginFrame();
        
        Sandbox::Update();
        Sandbox::Render();
        
        Tuff::Backend::EndFrame();
    }
    
}