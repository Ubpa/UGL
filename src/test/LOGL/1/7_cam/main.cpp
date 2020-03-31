#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <UGL/UGL>
#include <UGM/UGM>

#include "../../camera/camera.h"

#include <iostream>

using namespace Ubpa;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(pointf3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
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
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    gl::Shader vs(gl::ShaderType::VertexShader, "../data/shaders/p3t2.vs"); // you can name your shader files however you like
    gl::Shader fs(gl::ShaderType::FragmentShader, "../data/shaders/img.fs"); // you can name your shader files however you like
    gl::Program program(&vs, &fs);

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
    // world space positions of our cubes
    pointf3 cubePositions[] = {
        pointf3(0.0f,  0.0f,  0.0f),
        pointf3(2.0f,  5.0f, -15.0f),
        pointf3(-1.5f, -2.2f, -2.5f),
        pointf3(-3.8f, -2.0f, -12.3f),
        pointf3(2.4f, -0.4f, -3.5f),
        pointf3(-1.7f,  3.0f, -7.5f),
        pointf3(1.3f, -2.0f, -2.5f),
        pointf3(1.5f,  2.0f, -2.5f),
        pointf3(1.5f,  0.2f, -1.5f),
        pointf3(-1.3f,  1.0f, -1.5f)
    };
    gl::VertexArray::Format format;
    gl::VertexBuffer vbo(sizeof(vertices), vertices, gl::BufferUsage::StaticDraw);
    gl::ElementBuffer ebo(gl::BasicPrimitiveType::Triangles, 12, indices);
    format.attrptrs.push_back(vbo.AttrPtr(3, gl::DataType::Float, GL_FALSE, 11 * sizeof(GLfloat), (const void*)(0)));
    format.attrptrs.push_back(vbo.AttrPtr(2, gl::DataType::Float, GL_FALSE, 11 * sizeof(GLfloat), (const void*)(3 * sizeof(float))));
    format.eb = &ebo;
    gl::VertexArray vao({ 0,1 }, format);


    // load and create a texture 
    // -------------------------
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
    
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    program.SetTex("texture0", 0);


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
        gl::ClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
        gl::Clear(gl::BufferSelectBit::ColorBufferBit | gl::BufferSelectBit::DepthBufferBit); // also clear the depth buffer now!

        // bind textures on corresponding texture units
        texture0.Use(0);

        // pass projection matrix to shader (note that in this case it could change every frame)
        transformf projection = transformf::perspective(to_radian(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.f);
        program.SetMatf4("projection", projection);

        // camera/view transformation
        program.SetMatf4("view", camera.GetViewMatrix());

        // render boxes
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            float angle = 20.0f * i + 10.f * (float)glfwGetTime();
            transformf model(cubePositions[i], quatf{ vecf3(1.0f, 0.3f, 0.5f), to_radian(angle) });
            program.SetMatf4("model", model);
            vao.Draw(&program);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
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
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
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