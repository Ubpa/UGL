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
unsigned int loadTexture(const char *path);

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
    gl::Shader p3t2_vs(gl::ShaderType::VertexShader, "../data/shaders/p3t2.vs"); // you can name your shader files however you like
    gl::Shader p2t2_vs(gl::ShaderType::VertexShader, "../data/shaders/p2t2.vs"); // you can name your shader files however you like
    gl::Shader img_fs(gl::ShaderType::FragmentShader, "../data/shaders/img.fs"); // you can name your shader files however you like
    gl::Program obj_program(&p3t2_vs, &img_fs);
    gl::Program screen_program(&p2t2_vs, &img_fs);
    obj_program.SetTex("texture0", 0);
    screen_program.SetTex("texture0", 0);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float cube_vertices[] = {
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
    unsigned int cube_indices[] = {
         0,  1,  2,  3,  2,  1,
         4,  5,  6,  7,  6,  5,
         8,  9, 10, 11, 10,  9,
        12, 13, 14, 15, 14, 13,
        16, 17, 18, 19, 18, 17,
        20, 21, 22, 23, 22, 21,
    };
    float plane_vertices[] = {
        // positions          // texture Coords 
         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
         5.0f, -0.5f, -5.0f,  2.0f, 2.0f
    };
    unsigned int plane_indices[] = {
        0, 3, 1, 2, 1, 3
    };
    float quad_vertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
    unsigned int quad_indices[] = {
        2, 3, 1, 0, 1, 3
    };
    // cube VAO
    gl::VertexArray::Format cube_format;
    gl::VertexBuffer cube_vbo(sizeof(cube_vertices), cube_vertices, gl::BufferUsage::StaticDraw);
    gl::ElementBuffer cube_ebo(gl::BasicPrimitiveType::Triangles, 12, cube_indices);
    cube_format.attrptrs.push_back(cube_vbo.AttrPtr(3, gl::DataType::Float, GL_FALSE, 11 * sizeof(GLfloat), (const void*)(0)));
    cube_format.attrptrs.push_back(cube_vbo.AttrPtr(2, gl::DataType::Float, GL_FALSE, 11 * sizeof(GLfloat), (const void*)(3 * sizeof(float))));
    cube_format.eb = &cube_ebo;
    gl::VertexArray cube_vao({ 0,1 }, cube_format);
    // plane VAO
    gl::VertexArray::Format plane_format;
    gl::VertexBuffer plane_vbo(sizeof(plane_vertices), plane_vertices, gl::BufferUsage::StaticDraw);
    gl::ElementBuffer plane_ebo(gl::BasicPrimitiveType::Triangles, 2, plane_indices);
    plane_format.attrptrs.push_back(plane_vbo.AttrPtr(3, gl::DataType::Float, GL_FALSE, 5 * sizeof(GLfloat), (const void*)(0)));
    plane_format.attrptrs.push_back(plane_vbo.AttrPtr(2, gl::DataType::Float, GL_FALSE, 5 * sizeof(GLfloat), (const void*)(3 * sizeof(float))));
    plane_format.eb = &plane_ebo;
    gl::VertexArray plane_vao({ 0,1 }, plane_format);
    // screen quad VAO
    gl::VertexArray::Format quad_format;
    gl::VertexBuffer quad_vbo(sizeof(quad_vertices), quad_vertices, gl::BufferUsage::StaticDraw);
    gl::ElementBuffer quad_ebo(gl::BasicPrimitiveType::Triangles, 2, quad_indices);
    quad_format.attrptrs.push_back(quad_vbo.AttrPtr(3, gl::DataType::Float, GL_FALSE, 4 * sizeof(GLfloat), (const void*)(0)));
    quad_format.attrptrs.push_back(quad_vbo.AttrPtr(2, gl::DataType::Float, GL_FALSE, 4 * sizeof(GLfloat), (const void*)(2 * sizeof(float))));
    quad_format.eb = &quad_ebo;
    gl::VertexArray quad_vao({ 0,1 }, quad_format);

    // load textures
    // -------------
    gl::Texture2D texture0;
    texture0.SetWrapFilter(gl::WrapMode::Repeat, gl::WrapMode::Repeat, gl::MinFilter::Linear, gl::MagFilter::Linear);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char* data = stbi_load("../data/textures/checkerboard.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        texture0.SetImage(0, gl::PixelDataInternalFormat::Rgb, width, height, gl::PixelDataFormat::Rgb, gl::PixelDataType::UnsignedByte, data);
        texture0.GenerateMipmap();
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // shader configuration
    // --------------------
    obj_program.SetInt("texture0", 0);
    screen_program.SetInt("texture0", 0);

    // framebuffer configuration
    // -------------------------
    gl::FrameBuffer fb;
    gl::Texture2D fb_tex;
    fb_tex.SetImage(0, gl::PixelDataInternalFormat::Rgb, SCR_WIDTH, SCR_HEIGHT, gl::PixelDataFormat::Rgb, gl::PixelDataType::UnsignedByte, nullptr);
    fb_tex.SetWrapFilter(gl::WrapMode::Repeat, gl::WrapMode::Repeat, gl::MinFilter::Linear, gl::MagFilter::Linear);
    fb.Attach(gl::FramebufferAttachment::ColorAttachment0, &fb_tex);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    gl::RenderBuffer rb;
    rb.SetStorage(gl::FramebufferInternalFormat::Depth24Stencil8, SCR_WIDTH, SCR_HEIGHT);// use a single renderbuffer object for both a depth AND stencil buffer.
    fb.Attach(gl::FramebufferAttachment::DepthAttachment, &rb);// now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (!fb.IsComplete()) {
        cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
        return 1;
    }

    // draw as wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
        // bind to framebuffer and draw scene as we normally would to color texture 
        fb.Bind();
        gl::Enable(gl::Capability::DepthTest); // enable depth testing (is disabled for rendering screen-space quad)

        // make sure we clear the framebuffer's content
        gl::ClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        gl::Clear(gl::BufferSelectBit::ColorBufferBit | gl::BufferSelectBit::DepthBufferBit); // also clear the depth buffer now!

        auto view = camera.GetViewMatrix();
        transformf projection = transformf::perspective(to_radian(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        obj_program.SetMatf4("view", view);
        obj_program.SetMatf4("projection", projection);
        // cubes
        obj_program.Active(0, &texture0);
        obj_program.SetMatf4("model", transformf{ pointf3{-1.0f, 0.0f, -1.0f} });
        cube_vao.Draw(&obj_program);
        obj_program.SetMatf4("model", transformf{ pointf3{2.0f, 0.0f, 0.0f} });
        cube_vao.Draw(&obj_program);
        
        // floor
        obj_program.SetMatf4("model", transformf::eye());
        plane_vao.Draw(&obj_program);

        // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
        gl::FrameBuffer::BindReset();
        gl::Disable(gl::Capability::DepthTest); // disable depth test so screen-space quad isn't discarded due to depth test.
        // clear all relevant buffers
        gl::ClearColor({ 1.0f, 1.0f, 1.0f, 1.0f });// set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
        gl::Clear(gl::BufferSelectBit::ColorBufferBit);

        screen_program.Active(0, &fb_tex); // use the color attachment texture as the texture of the quad plane
        quad_vao.Draw(&screen_program);


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
