#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <UGL/UGL>
#include <UGM/UGM>

#include "../../camera/camera.h"

#include <iostream>

using namespace Ubpa;
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
gl::Texture2D loadTexture(const char *path);
gl::TextureCubeMap loadCubemap(vector<std::string> faces);

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

// camera
Camera camera(pointf3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    gl::Enable(gl::Capability::DepthTest);

    // build and compile shaders
    // -------------------------
    gl::Shader cubemap_vs(gl::ShaderType::VertexShader, "../data/test/LOGL/4/6.2.cubemaps.vs");
    gl::Shader cubemap_fs(gl::ShaderType::FragmentShader, "../data/test/LOGL/4/6.2.cubemaps.fs");
    gl::Shader skybox_vs(gl::ShaderType::VertexShader, "../data/test/LOGL/4/6.2.skybox.vs");
    gl::Shader skybox_fs(gl::ShaderType::FragmentShader, "../data/test/LOGL/4/6.2.skybox.fs");
    gl::Program cubemap_program(&cubemap_vs, &cubemap_fs);
    gl::Program skybox_program(&skybox_vs, &skybox_fs);

    // shader configuration
    // --------------------
    cubemap_program.SetTex("skybox", 0);
    skybox_program.SetTex("skybox", 0);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions      // uv      // normals       // tangent
        -1.f, -1.f, -1.f, 1.f, 0.f,  0.f,  0.f, -1.f, -1.f,  0.f,  0.f,
        -1.f,  1.f, -1.f, 1.f, 1.f,  0.f,  0.f, -1.f, -1.f,  0.f,  0.f,
         1.f, -1.f, -1.f, 0.f, 0.f,  0.f,  0.f, -1.f, -1.f,  0.f,  0.f,
         1.f,  1.f, -1.f, 0.f, 1.f,  0.f,  0.f, -1.f, -1.f,  0.f,  0.f,

        -1.f, -1.f,  1.f, 0.f, 0.f,  0.f,  0.f,  1.f,  1.f,  0.f,  0.f,
         1.f, -1.f,  1.f, 1.f, 0.f,  0.f,  0.f,  1.f,  1.f,  0.f,  0.f,
        -1.f,  1.f,  1.f, 0.f, 1.f,  0.f,  0.f,  1.f,  1.f,  0.f,  0.f,
         1.f,  1.f,  1.f, 1.f, 1.f,  0.f,  0.f,  1.f,  1.f,  0.f,  0.f,

        -1.f, -1.f,  1.f, 1.f, 0.f, -1.f,  0.f,  0.f,  0.f,  0.f,  1.f,
        -1.f,  1.f,  1.f, 1.f, 1.f, -1.f,  0.f,  0.f,  0.f,  0.f,  1.f,
        -1.f, -1.f, -1.f, 0.f, 0.f, -1.f,  0.f,  0.f,  0.f,  0.f,  1.f,
        -1.f,  1.f, -1.f, 0.f, 1.f, -1.f,  0.f,  0.f,  0.f,  0.f,  1.f,

         1.f,  1.f,  1.f, 0.f, 1.f,  1.f,  0.f,  0.f,  0.f,  0.f, -1.f,
         1.f, -1.f,  1.f, 0.f, 0.f,  1.f,  0.f,  0.f,  0.f,  0.f, -1.f,
         1.f,  1.f, -1.f, 1.f, 1.f,  1.f,  0.f,  0.f,  0.f,  0.f, -1.f,
         1.f, -1.f, -1.f, 1.f, 0.f,  1.f,  0.f,  0.f,  0.f,  0.f, -1.f,

         1.f, -1.f,  1.f, 1.f, 1.f,  0.f, -1.f,  0.f,  1.f,  0.f,  0.f,
        -1.f, -1.f,  1.f, 0.f, 1.f,  0.f, -1.f,  0.f,  1.f,  0.f,  0.f,
         1.f, -1.f, -1.f, 1.f, 0.f,  0.f, -1.f,  0.f,  1.f,  0.f,  0.f,
        -1.f, -1.f, -1.f, 0.f, 0.f,  0.f, -1.f,  0.f,  1.f,  0.f,  0.f,

        -1.f,  1.f,  1.f, 0.f, 0.f,  0.f,  1.f,  0.f,  1.f,  0.f,  0.f,
         1.f,  1.f,  1.f, 1.f, 0.f,  0.f,  1.f,  0.f,  1.f,  0.f,  0.f,
        -1.f,  1.f, -1.f, 0.f, 1.f,  0.f,  1.f,  0.f,  1.f,  0.f,  0.f,
         1.f,  1.f, -1.f, 1.f, 1.f,  0.f,  1.f,  0.f,  1.f,  0.f,  0.f,
    };
    unsigned int indices[] = {
         0,  1,  2,  3,  2,  1,
         4,  5,  6,  7,  6,  5,
         8,  9, 10, 11, 10,  9,
        12, 13, 14, 15, 14, 13,
        16, 17, 18, 19, 18, 17,
        20, 21, 22, 23, 22, 21,
    };

    gl::VertexBuffer vbo(sizeof(vertices), vertices, gl::BufferUsage::StaticDraw);
    gl::ElementBuffer ebo(gl::BasicPrimitiveType::Triangles, 12, indices);
    auto posAttrPtr = vbo.AttrPtr(3, gl::DataType::Float, GL_FALSE, 11 * sizeof(GLfloat), (const void*)(0));
    auto normalAttrPtr = vbo.AttrPtr(3, gl::DataType::Float, GL_FALSE, 11 * sizeof(GLfloat), (const void*)(5 * sizeof(float)));
    // cube VAO
    gl::VertexArray::Format cube_format;
    cube_format.attrptrs.push_back(posAttrPtr);
    cube_format.attrptrs.push_back(normalAttrPtr);
    cube_format.eb = &ebo;
    gl::VertexArray cube_vao({ 0,1 }, cube_format);
    // skybox VAO
    gl::VertexArray::Format skybox_format;
    skybox_format.attrptrs.push_back(posAttrPtr);
    skybox_format.eb = &ebo;
    gl::VertexArray skybox_vao({ 0 }, skybox_format);

    // load textures
    // -------------
    vector<std::string> faces
    {
        "../data/textures/skybox/right.jpg",
        "../data/textures/skybox/left.jpg",
        "../data/textures/skybox/top.jpg",
        "../data/textures/skybox/bottom.jpg",
        "../data/textures/skybox/front.jpg",
        "../data/textures/skybox/back.jpg",
    };
    auto cubemap = loadCubemap(faces);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        gl::ClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        gl::Clear(gl::BufferSelectBit::ColorBufferBit | gl::BufferSelectBit::DepthBufferBit); // also clear the depth buffer now!

        // draw scene as normal
        auto projection = transformf::perspective(to_radian(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        cubemap_program.SetMatf4("model", transformf{ pointf3{0,1,0} });
        cubemap_program.SetMatf4("view", camera.GetViewMatrix());
        cubemap_program.SetMatf4("projection", projection);
        cubemap_program.SetVecf3("cameraPos", camera.Position);
        // cubes
        cubemap_program.Active(0, &cubemap);
        cube_vao.Draw(&cubemap_program);

        // draw skybox as last
        gl::DepthFunc(gl::CompareFunc::Lequal); // change depth function so depth test passes when values are equal to depth buffer's content
        auto view = transformf(camera.GetViewMatrix().decompose_mat3()); // remove translation from the view matrix
        skybox_program.SetMatf4("view", view);
        skybox_program.SetMatf4("projection", projection);
        // skybox cube
        skybox_program.Active(0, &cubemap);
        skybox_vao.Draw(&skybox_program);
        gl::DepthFunc(gl::CompareFunc::Less); // set depth function back to default

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera::Movement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera::Movement::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera::Movement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera::Movement::RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera::Movement::UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera::Movement::RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    gl::Viewport({ 0, 0 }, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = static_cast<float>(xpos);
        lastY = static_cast<float>(ypos);
        firstMouse = false;
    }

    float xoffset = static_cast<float>(xpos) - lastX;
    float yoffset = lastY - static_cast<float>(ypos); // reversed since y-coordinates go from bottom to top

    lastX = static_cast<float>(xpos);
    lastY = static_cast<float>(ypos);

    camera.ProcessMouseMovement(static_cast<float>(xoffset), static_cast<float>(yoffset));
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
gl::Texture2D loadTexture(char const * path)
{
    gl::Texture2D tex;
    tex.SetWrapFilter(gl::WrapMode::Repeat, gl::WrapMode::Repeat, gl::MinFilter::Linear, gl::MagFilter::Linear);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        tex.SetImage(0, gl::PixelDataInternalFormat::Rgb, width, height, gl::PixelDataFormat::Rgb, gl::PixelDataType::UnsignedByte, data);
        tex.GenerateMipmap();
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    return tex;
}

// loads a cubemap texture from 6 individual texture faces
// order:
// +X (right)
// -X (left)
// +Y (top)
// -Y (bottom)
// +Z (front) 
// -Z (back)
// -------------------------------------------------------
gl::TextureCubeMap loadCubemap(vector<std::string> faces)
{
    gl::TextureCubeMap tex;
    gl::TextureCubeTarget targets[6] = {
        gl::TextureCubeTarget::TextureCubeMapPositiveX,
        gl::TextureCubeTarget::TextureCubeMapNegativeX,
        gl::TextureCubeTarget::TextureCubeMapPositiveY,
        gl::TextureCubeTarget::TextureCubeMapNegativeY,
        gl::TextureCubeTarget::TextureCubeMapPositiveZ,
        gl::TextureCubeTarget::TextureCubeMapNegativeZ,
    };

    int width, height, nrComponents;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            tex.SetImage(targets[i], 0, gl::PixelDataInternalFormat::Rgb, width, height, gl::PixelDataFormat::Rgb, gl::PixelDataType::UnsignedByte, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }

    tex.SetWrapFilter(gl::WrapMode::ClampToEdge,
        gl::WrapMode::ClampToEdge,
        gl::WrapMode::ClampToEdge,
        gl::MinFilter::Linear,
        gl::MagFilter::Linear);

    return tex;
}