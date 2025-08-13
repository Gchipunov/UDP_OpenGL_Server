//#include <glad/glad.h>
#include <GL/glew.h>
//#include <GL/freeglut.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include <GL/glext.h>
#include <GLFW/glfw3.h>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include <learnopengl/shader_m.h>
#include "shader_m.h"

#include <vector>

#include <iostream>

// https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/7.4.camera_class/camera_class.cpp
// 


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

unsigned int iNumTrianglesDraw = 54;

// camera
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);

//glm::vec3 cameraPos = glm::vec3(7.35f, -6.92, 4.95f);

//glm::vec3 cameraPos = glm::vec3(5.0f,  -5.0f, 3.0f);
//yaw: -93.800102, pitch: -10.300071, camera.x: -0.222370, camera.y: -0.661427, camera.z: 5.455092
glm::vec3 cameraPos = glm::vec3(-0.222370f, -0.661427f, 5.455092f);

glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
//float yaw = -180.0f;
float pitch = -10.0f;
// 
//float yaw = 63.0f;  // Set initial yaw to 63.0   , from blender and bard
//float pitch = 46.96f; // Set initial pitch to 46.96 , from blender and bard



float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

std::vector <float> mainVertices; 

int AddCube(float x, float y, float z)
{

    // set up vertex data (and buffer(s)) and configure vertex attributes
   // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };


    return 36;
}

int main(int argc, char** argv)
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL - Camera 1", NULL, NULL);
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
    //if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
   // {
    //    std::cout << "Failed to initialize GLAD" << std::endl;
   //     return -1;
   // }
    printf("glewInit\n\n");
    glewInit();

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("7.3.camera2.vs", "7.3.camera2.frag");

    // Define the vertices for a quad
// Each vertex has 3 components: x, y, z
// We'll define a simple square centered at the origin
// with a side length of 2.0 (from -1.0 to 1.0)
//
// The order is critical for CCW:
//
//      3 (top-left) --- 2 (top-right)
//         |                |
//         |                |
//      0 (bottom-left) -- 1 (bottom-right)
//
// Note: OpenGL uses a right-handed coordinate system by default.

    GLfloat quad_vertices[] = {
        // Bottom-left vertex
        -1.0f, -1.0f, 0.0f,

        // Bottom-right vertex
         1.0f, -1.0f, 0.0f,

         // Top-right vertex
          1.0f,  1.0f, 0.0f,

          // Top-left vertex
          -1.0f,  1.0f, 0.0f
    };

    // If you are using indices to draw the quad, this is how you would set them up.
    // This is more efficient as you don't duplicate vertex data.
    // We'll draw two triangles to form the quad.
    //
    // Triangle 1: 0, 1, 2
    // Triangle 2: 0, 2, 3
    //
    // Notice how both triangles maintain a CCW winding order.
    //
    GLuint quad_indices[] = {
        0, 1, 2,  // First triangle
        0, 2, 3   // Second triangle
    };
    float verticesPlane1[] = {
        // refine as triangles
        0.0f, -5.0f, 0.0f,  0.0f, 0.0f, //      3 (top-left)
         0.0f, 0.0f, 0.0f,  0.0f, 0.0f, //  2 (top-right)
         5.0f, -5.0f, 0.0f,  0.0f, 0.0f, //  0 (bottom-left)
           5.0f, 0.0f, 0.0f,  0.0f, 0.0f // 1 (bottom-right)
    };
    float verticesPlaneTriangles1[] = {
        // refine as triangles 1
        5.0f, -5.0f, 0.0f,  0.0f, 0.0f, //  0 (bottom-left)
        5.0f, 0.0f, 0.0f,  0.0f, 0.0f, // 1 (bottom-right)
        0.0f, 0.0f, 0.0f,  0.0f, 0.0f, //  2 (top-right)

        5.0f, -5.0f, 0.0f,  0.0f, 0.0f, //  0 (bottom-left)
        0.0f, 0.0f, 0.0f,  0.0f, 0.0f, //  2 (top-right)
        0.0f, -5.0f, 0.0f,  0.0f, 0.0f, //      3 (top-left)    
    };

    float verticesPlane2[] = {
        // refine as triangles
         0.0f, 0.0f, 0.0f,  0.0f, 0.0f, //      3 (top-left)
         0.0f, 5.0f, 0.0f,  0.0f, 0.0f, //  2 (top-right)
         5.0f, 0.0f, 0.0f,  0.0f, 0.0f, //  0 (bottom-left)
           5.0f, 5.0f, 0.0f,  0.0f, 0.0f // 1 (bottom-right)
    };

    float verticesPlaneTriangle2[] = {
        // refine as triangles
         5.0f, 0.0f, 0.0f,  0.0f, 0.0f, //  0 (bottom-left)
         5.0f, 5.0f, 0.0f,  0.0f, 0.0f, // 1 (bottom-right)
         0.0f, 5.0f, 0.0f,  0.0f, 0.0f, //  2 (top-right)

         5.0f, 0.0f, 0.0f,  0.0f, 0.0f, //  0 (bottom-left)
         0.0f, 5.0f, 0.0f,  0.0f, 0.0f, //  2 (top-right)
         0.0f, 0.0f, 0.0f,  0.0f, 0.0f, //      3 (top-left)
    };


    float verticesPlane3[] = {
        // refine as triangles
        -5.0f, 0.0f, 0.0f,  0.0f, 0.0f, //      3 (top-left)
       -5.0f, 5.0f, 0.0f,  0.0f, 0.0f,  //  2 (top-right)
        0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  //  0 (bottom-left)
          0.0f, 5.0f, 0.0f,  0.0f, 0.0f // 1 (bottom-right)
    };

    float verticesPlaneTriangle3[] = {
       0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  //  0 (bottom-left)
       0.0f, 5.0f, 0.0f,  0.0f, 0.0f, // 1 (bottom-right)
       -5.0f, 5.0f, 0.0f,  0.0f, 0.0f,  //  2 (top-right)

       0.0f, 0.0f, 0.0f,  0.0f, 0.0f,  //  0 (bottom-left)
       -5.0f, 5.0f, 0.0f,  0.0f, 0.0f,  //  2 (top-right)
        // refine as triangles
       -5.0f, 0.0f, 0.0f,  0.0f, 0.0f, //      3 (top-left)
      
   
    };

// Triangle 1: 0, 1, 2
// Triangle 2: 0, 2, 3
    float verticesUDPCube[] = {
        // face 1
         -2.0f , -2.0f , 2.0f ,  0.0f, 0.0f,  // top - left  , 3 (top-left) 
         -2.0f , -1.0f , 2.0f ,  0.0f, 0.0f,  // top -right , 2 (top-right)

         -1.0f, -2.0f, 2.0f, 0.0f, 0.0f, // bottom - left , 0 (bottom-left)
          -1.0f, -1.0f, 2.0f, 0.0f, 0.0f, // bottom - right , 1 (bottom-right)
        
          // face 2
        -1.0f, -2.0f , 2.0f, 0.0f, 0.0f,  // top - left
        -1.0f, -1.0f, 2.0f, 0.0f, 0.0f, // top - right

        -1.0f, -2.0f, 1.0f, 0.0f, 0.0f, // bottom -left
        -1.0f , -1.0f , 2.0f, 0.0f, 0.0f, // bottom - right
        
        // face 3
        -1.0f, -1.0f, 2.0f, 0.0f, 0.0f, // top - left
        -2.0f, -1.0f, 2.0f, 0.0f, 0.0f, // top - right

        -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, // bottom - left
        -2.0f, -1.0f, 1.0f, 0.0f, 0.0f, // bottom - right

        // face 4 
        -2.0f, -2.0f, 2.0f, 0.0f, 0.0f, // top - left
        -1.0f, -2.0f, 2.0f, 0.0f, 0.0f, // top - right

        -2.0f, -2.0f, 1.0f, 0.0f, 0.0f, // bottom - left
        -1.0f, -2.0f, 1.0f, 0.0f, 0.0f, // bottom - right

        // face 5
        -2.0f, -1.0f, 2.0f , 0.0f, 0.0f, // top - left
        -2.0f, -2.0f, 2.0f, 0.0f, 0.0f, // top - right

        -2.0f, -1.0f, 1.0f, 0.0f, 0.0f, // bottom - left
        -2.0f, -2.0f, 1.0f, 0.0f, 0.0f, // bottom - right

        // face 6
        -1.0f, -2.0f, 1.0f, 0.0f, 0.0f, // top - left
        -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, // top - right

        -2.0f, -2.0f, 1.0f, 0.0f, 0.0f, // bottom - left
        -2.0f, -1.0f, 1.0f, 0.0f, 0.0f, // bottom - right
    };

    // Triangle 1: 0, 1, 2
    // Triangle 2: 0, 2, 3
    float verticesUDPCubeTriangleFullDemo[] = {
        // face 1
                 -1.0f, -2.0f, 2.0f, 0.0f, 0.0f, // bottom - left , 0 (bottom-left)
// mainVertices.push_back(-1.0f); 


          -1.0f, -1.0f, 2.0f,  1.0f, 0.0f, // bottom - right , 1 (bottom-right)
           -2.0f , -1.0f , 2.0f ,  1.0f, 1.0f,  // top -right , 2 (top-right)
             -1.0f, -2.0f, 2.0f,  0.0f, 0.0f, // bottom - left , 0 (bottom-left)
            -2.0f , -1.0f , 2.0f ,  1.0f, 1.0f,  // top -right , 2 (top-right)
         -2.0f , -2.0f , 2.0f ,  0.0f, 1.0f, // top - left  , 3 (top-left) 



         // face 2
       -1.0f, -2.0f , 1.0f,  0.051009f, 0.636836f,  // bottom -left, 0 (bottom-left)
       -1.0f , -1.0f , 2.0f, 0.051009f, 0.386836f, // bottom - right, 1 (bottom-right)
       -1.0f, -1.0f , 2.0f, 0.301009f, 0.386836f, // top - right, 2 (top-right)

       -1.0f, -2.0f, 1.0f, 0.051009f, 0.636836f, // bottom -left, 0 (bottom-left)
       -1.0f, -1.0f, 2.0f, 0.301009f, 0.386836f, // top - right, 2 (top-right)
       -1.0f, -2.0f , 2.0f, 0.301009f, 0.636836f,  // top - left, 3 (top-left)

       // Triangle 1: 0, 1, 2
       // Triangle 2: 0, 2, 3
       // face 3
       -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, // bottom - left, 0 (bottom-left)
       -2.0f, -1.0f, 1.0f, 0.0f, 0.0f, // bottom - right, 1 (bottom-right)
       -2.0f, -1.0f, 2.0f, 0.0f, 0.0f, // top - right, 2 (top-right)

       -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, // bottom - left, 0 (bottom-left)
       -2.0f, -1.0f, 2.0f, 0.0f, 0.0f, // top - right, 2 (top-right)
       -1.0f, -1.0f, 2.0f, 0.0f, 0.0f, // top - left, 3 (top-left)




       // face 4 
       -2.0f, -2.0f, 1.0f, 0.0f, 0.0f, // bottom - left, 0 (bottom-left)
       -1.0f, -2.0f, 1.0f, 0.0f, 0.0f, // bottom - right, 1 (bottom-right)
       -1.0f, -2.0f, 2.0f, 0.0f, 0.0f, // top - right, 2 (top-right)

       -2.0f, -2.0f, 1.0f, 0.0f, 0.0f, // bottom - left, 0 (bottom-left)
       -1.0f, -2.0f, 2.0f, 0.0f, 0.0f, // top - right, 2 (top-right)
       -2.0f, -2.0f, 2.0f, 0.0f, 0.0f, // top - left, 3 (top-left)



       // Triangle 1: 0, 1, 2
       // Triangle 2: 0, 2, 3
       // face 5
       -2.0f, -1.0f, 1.0f, 0.0f, 0.0f, // bottom - left, 0 (bottom-left)
       -2.0f, -2.0f, 1.0f, 0.0f, 0.0f, // bottom - right, 1 (bottom-right)
       -2.0f, -2.0f, 2.0f, 0.0f, 0.0f, // top - right, 2 (top-right)
       -2.0f, -1.0f, 1.0f, 0.0f, 0.0f, // bottom - left, 0 (bottom-left)
       -2.0f, -2.0f, 2.0f, 0.0f, 0.0f, // top - right, 2 (top-right)
       -2.0f, -1.0f, 2.0f , 0.0f, 0.0f, // top - left, 3 (top-left)




       // face 6

       -2.0f, -2.0f, 1.0f, 0.0f, 0.0f, // bottom - left, 0 (bottom-left)
       -2.0f, -1.0f, 1.0f, 0.0f, 0.0f, // bottom - right, 1 (bottom-right)
       -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, // top - right, 2 (top-right)

       -2.0f, -2.0f, 1.0f, 0.0f, 0.0f, // bottom - left, 0 (bottom-left)
       -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, // top - right, 2 (top-right)
       -1.0f, -2.0f, 1.0f, 0.0f, 0.0f, // top - left, 3 (top-left)

       // add our planes
            // refine as triangles 1
        5.0f, -5.0f, 0.0f,  0.0f, 1.0f, //  0 (bottom-left)
        5.0f, 0.0f, 0.0f,  1.0f, 1.0f, // 1 (bottom-right)
        0.0f, 0.0f, 0.0f,  1.0f, 0.0f, //  2 (top-right)

        5.0f, -5.0f, 0.0f,  0.0f, 1.0f, //  0 (bottom-left)
        0.0f, 0.0f, 0.0f,  1.0f, 0.0f, //  2 (top-right)
        0.0f, -5.0f, 0.0f,  0.0f, 0.0f, //      3 (top-left)    

        // refine as triangles
    5.0f, 0.0f, 0.0f,  0.0f, 1.0f, //  0 (bottom-left)
    5.0f, 5.0f, 0.0f,  1.0f, 1.0f, // 1 (bottom-right)
    0.0f, 5.0f, 0.0f,  1.0f, 0.0f, //  2 (top-right)

    5.0f, 0.0f, 0.0f,  0.0f, 1.0f, //  0 (bottom-left)
    0.0f, 5.0f, 0.0f,  1.0f, 0.0f, //  2 (top-right)
    0.0f, 0.0f, 0.0f,  0.0f, 0.0f, //      3 (top-left)

    // triangle3
       0.0f, 0.0f, 0.0f,  0.0f, 1.0f,  //  0 (bottom-left)
       0.0f, 5.0f, 0.0f,  1.0f, 1.0f, // 1 (bottom-right)
       -5.0f, 5.0f, 0.0f,  1.0f, 0.0f,  //  2 (top-right)

       0.0f, 0.0f, 0.0f,  0.0f, 1.0f,  //  0 (bottom-left)
       -5.0f, 5.0f, 0.0f,  1.0f, 0.0f,  //  2 (top-right)
       // refine as triangles
      -5.0f, 0.0f, 0.0f,  0.0f, 0.0f, //      3 (top-left)



    };


    // Triangle 1: 0, 1, 2
   // Triangle 2: 0, 2, 3
    float verticesUDPCubeTriangle[] = {
        // face 1
                 -1.0f, -2.0f, 2.0f, 0.0f, 0.0f, // bottom - left , 0 (bottom-left)
          -1.0f, -1.0f, 2.0f,  1.0f, 0.0f, // bottom - right , 1 (bottom-right)
           -2.0f , -1.0f , 2.0f ,  1.0f, 1.0f,  // top -right , 2 (top-right)
             -1.0f, -2.0f, 2.0f,  0.0f, 0.0f, // bottom - left , 0 (bottom-left)
            -2.0f , -1.0f , 2.0f ,  1.0f, 1.0f,  // top -right , 2 (top-right)
         -2.0f , -2.0f , 2.0f ,  0.0f, 1.0f, // top - left  , 3 (top-left) 



         // face 2
       -1.0f, -2.0f , 1.0f,  0.051009f, 0.636836f,  // bottom -left, 0 (bottom-left)
       -1.0f , -1.0f , 2.0f, 0.051009f, 0.386836f, // bottom - right, 1 (bottom-right)
       -1.0f, -1.0f , 2.0f, 0.301009f, 0.386836f, // top - right, 2 (top-right)

       -1.0f, -2.0f, 1.0f, 0.051009f, 0.636836f, // bottom -left, 0 (bottom-left)
       -1.0f, -1.0f, 2.0f, 0.301009f, 0.386836f, // top - right, 2 (top-right)
       -1.0f, -2.0f , 2.0f, 0.301009f, 0.636836f,  // top - left, 3 (top-left)

       // Triangle 1: 0, 1, 2
       // Triangle 2: 0, 2, 3
       // face 3
       -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, // bottom - left, 0 (bottom-left)
       -2.0f, -1.0f, 1.0f, 0.0f, 0.0f, // bottom - right, 1 (bottom-right)
       -2.0f, -1.0f, 2.0f, 0.0f, 0.0f, // top - right, 2 (top-right)

       -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, // bottom - left, 0 (bottom-left)
       -2.0f, -1.0f, 2.0f, 0.0f, 0.0f, // top - right, 2 (top-right)
       -1.0f, -1.0f, 2.0f, 0.0f, 0.0f, // top - left, 3 (top-left)




       // face 4 
       -2.0f, -2.0f, 1.0f, 0.0f, 0.0f, // bottom - left, 0 (bottom-left)
       -1.0f, -2.0f, 1.0f, 0.0f, 0.0f, // bottom - right, 1 (bottom-right)
       -1.0f, -2.0f, 2.0f, 0.0f, 0.0f, // top - right, 2 (top-right)

       -2.0f, -2.0f, 1.0f, 0.0f, 0.0f, // bottom - left, 0 (bottom-left)
       -1.0f, -2.0f, 2.0f, 0.0f, 0.0f, // top - right, 2 (top-right)
       -2.0f, -2.0f, 2.0f, 0.0f, 0.0f, // top - left, 3 (top-left)



       // Triangle 1: 0, 1, 2
       // Triangle 2: 0, 2, 3
       // face 5
       -2.0f, -1.0f, 1.0f, 0.0f, 0.0f, // bottom - left, 0 (bottom-left)
       -2.0f, -2.0f, 1.0f, 0.0f, 0.0f, // bottom - right, 1 (bottom-right)
       -2.0f, -2.0f, 2.0f, 0.0f, 0.0f, // top - right, 2 (top-right)
       -2.0f, -1.0f, 1.0f, 0.0f, 0.0f, // bottom - left, 0 (bottom-left)
       -2.0f, -2.0f, 2.0f, 0.0f, 0.0f, // top - right, 2 (top-right)
       -2.0f, -1.0f, 2.0f , 0.0f, 0.0f, // top - left, 3 (top-left)




       // face 6

       -2.0f, -2.0f, 1.0f, 0.0f, 0.0f, // bottom - left, 0 (bottom-left)
       -2.0f, -1.0f, 1.0f, 0.0f, 0.0f, // bottom - right, 1 (bottom-right)
       -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, // top - right, 2 (top-right)

       -2.0f, -2.0f, 1.0f, 0.0f, 0.0f, // bottom - left, 0 (bottom-left)
       -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, // top - right, 2 (top-right)
       -1.0f, -2.0f, 1.0f, 0.0f, 0.0f, // top - left, 3 (top-left)

       // add our planes
    };


    float verticesUDPCubeTriangleAnoutherCopyofvertices[] = {  // undefined yet
        // face 1
       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
       -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

       -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    glm::vec3 cubePositions2[] = {
      glm::vec3(0.0f,  0.0f,  0.0f),
      /*
      glm::vec3(2.0f,  5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f),
      glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),
      glm::vec3(-1.7f,  3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),
      glm::vec3(1.5f,  2.0f, -2.5f),
      glm::vec3(1.5f,  0.2f, -1.5f),
      glm::vec3(-1.3f,  1.0f, -1.5f)
      */
    };


    mainVertices.push_back(-1.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); // bottom - left ); mainVertices.push_back( 0 (bottom-left)
    mainVertices.push_back(-1.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(2.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); // bottom - right ); mainVertices.push_back( 1 (bottom-right)
    mainVertices.push_back(-2.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(2.0f); mainVertices.push_back(1.0f); mainVertices.push_back(1.0f); // top -right ); mainVertices.push_back( 2 (top-right)
    mainVertices.push_back(-1.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); // bottom - left ); mainVertices.push_back( 0 (bottom-left)
    mainVertices.push_back(-2.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(2.0f); mainVertices.push_back(1.0f); mainVertices.push_back(1.0f); // top -right ); mainVertices.push_back( 2 (top-right)
    mainVertices.push_back(-2.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); // top - left  ); mainVertices.push_back( 3 (top-left) 



    // face 2
    mainVertices.push_back(-1.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.051009f); mainVertices.push_back(0.636836f); // bottom -left); mainVertices.push_back( 0 (bottom-left)
    mainVertices.push_back(-1.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.051009f); mainVertices.push_back(0.386836f); // bottom - right); mainVertices.push_back( 1 (bottom-right)
    mainVertices.push_back(-1.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.301009f); mainVertices.push_back(0.386836f); // top - right); mainVertices.push_back( 2 (top-right)

    mainVertices.push_back(-1.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.051009f); mainVertices.push_back(0.636836f); // bottom -left); mainVertices.push_back( 0 (bottom-left)
    mainVertices.push_back(-1.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.301009f); mainVertices.push_back(0.386836f); // top - right); mainVertices.push_back( 2 (top-right)
    mainVertices.push_back(-1.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.301009f); mainVertices.push_back(0.636836f); // top - left); mainVertices.push_back( 3 (top-left)

    // Triangle 1: 0); mainVertices.push_back( 1); mainVertices.push_back( 2
    // Triangle 2: 0); mainVertices.push_back( 2); mainVertices.push_back( 3
    // face 3
    mainVertices.push_back(-1.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); // bottom - left); mainVertices.push_back( 0 (bottom-left)
    mainVertices.push_back(-2.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); // bottom - right); mainVertices.push_back( 1 (bottom-right)
    mainVertices.push_back(-2.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); // top - right); mainVertices.push_back( 2 (top-right)

    mainVertices.push_back(-1.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); // bottom - left); mainVertices.push_back( 0 (bottom-left)
    mainVertices.push_back(-2.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); // top - right); mainVertices.push_back( 2 (top-right)
    mainVertices.push_back(-1.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); // top - left); mainVertices.push_back( 3 (top-left)




    // face 4 
    mainVertices.push_back(-2.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); // bottom - left); mainVertices.push_back( 0 (bottom-left)
    mainVertices.push_back(-1.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); // bottom - right); mainVertices.push_back( 1 (bottom-right)
    mainVertices.push_back(-1.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); // top - right); mainVertices.push_back( 2 (top-right)

    mainVertices.push_back(-2.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); // bottom - left); mainVertices.push_back( 0 (bottom-left)
    mainVertices.push_back(-1.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); // top - right); mainVertices.push_back( 2 (top-right)
    mainVertices.push_back(-2.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); // top - left); mainVertices.push_back( 3 (top-left)



    // Triangle 1: 0); mainVertices.push_back( 1); mainVertices.push_back( 2
    // Triangle 2: 0); mainVertices.push_back( 2); mainVertices.push_back( 3
    // face 5
    mainVertices.push_back(-2.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); // bottom - left); mainVertices.push_back( 0 (bottom-left)
    mainVertices.push_back(-2.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); // bottom - right); mainVertices.push_back( 1 (bottom-right)
    mainVertices.push_back(-2.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); // top - right); mainVertices.push_back( 2 (top-right)
    mainVertices.push_back(-2.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); // bottom - left); mainVertices.push_back( 0 (bottom-left)
    mainVertices.push_back(-2.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); // top - right); mainVertices.push_back( 2 (top-right)
    mainVertices.push_back(-2.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(2.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); // top - left); mainVertices.push_back( 3 (top-left)




    // face 6

    mainVertices.push_back(-2.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); // bottom - left); mainVertices.push_back( 0 (bottom-left)
    mainVertices.push_back(-2.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); // bottom - right); mainVertices.push_back( 1 (bottom-right)
    mainVertices.push_back(-1.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); // top - right); mainVertices.push_back( 2 (top-right)

    mainVertices.push_back(-2.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); // bottom - left); mainVertices.push_back( 0 (bottom-left)
    mainVertices.push_back(-1.0f); mainVertices.push_back(-1.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); // top - right); mainVertices.push_back( 2 (top-right)
    mainVertices.push_back(-1.0f); mainVertices.push_back(-2.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); // top - left); mainVertices.push_back( 3 (top-left)

    // add our planes
         // refine as triangles 1
    mainVertices.push_back(5.0f); mainVertices.push_back(-5.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); //  0 (bottom-left)
    mainVertices.push_back(5.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(1.0f); // 1 (bottom-right)
    mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); //  2 (top-right)

    mainVertices.push_back(5.0f); mainVertices.push_back(-5.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); //  0 (bottom-left)
    mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); //  2 (top-right)
    mainVertices.push_back(0.0f); mainVertices.push_back(-5.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); //      3 (top-left)    

    // refine as triangles
    mainVertices.push_back(5.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); //  0 (bottom-left)
    mainVertices.push_back(5.0f); mainVertices.push_back(5.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(1.0f); // 1 (bottom-right)
    mainVertices.push_back(0.0f); mainVertices.push_back(5.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); //  2 (top-right)

    mainVertices.push_back(5.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); //  0 (bottom-left)
    mainVertices.push_back(0.0f); mainVertices.push_back(5.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); //  2 (top-right)
    mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); //      3 (top-left)

    // triangle3
    mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); //  0 (bottom-left)
    mainVertices.push_back(0.0f); mainVertices.push_back(5.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(1.0f); // 1 (bottom-right)
    mainVertices.push_back(-5.0f); mainVertices.push_back(5.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); //  2 (top-right)

    mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); //  0 (bottom-left)
    mainVertices.push_back(-5.0f); mainVertices.push_back(5.0f); mainVertices.push_back(0.0f); mainVertices.push_back(1.0f); mainVertices.push_back(0.0f); //  2 (top-right)
    // refine as triangles
    mainVertices.push_back(-5.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); mainVertices.push_back(0.0f); //      3 (top-left)



    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
 //   glBufferData(GL_ARRAY_BUFFER, sizeof(verticesUDPCubeTriangleFullDemo), verticesUDPCubeTriangleFullDemo, GL_STATIC_DRAW);

 //   glBufferData(GL_ARRAY_BUFFER, sizeof(verticesUDPCubeTriangleFullDemo), verticesUDPCubeTriangleFullDemo, GL_DYNAMIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, mainVertices.size() * sizeof(float), mainVertices.data(), GL_DYNAMIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // load and create a texture 
    // -------------------------
    
    unsigned int texture1, texture2, texture3, texture4;

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
   // -------------------------------------------------------------------------------------------
    ourShader.use(); // nneeded before the texture init for correctly numbering the textures
    //with setInt
    ourShader.setInt("texture1", 0);
    // 
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    std::string containerPath = "assets/container.jpg";

    unsigned char* data = stbi_load(containerPath.c_str(), &width, &height, &nrChannels, 0);

  //  unsigned char* data = stbi_load(FileSystem::getPath("resources/textures/container.jpg").c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

   

    ourShader.setInt("texture2", 1);
    // texture 2
    // ---------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    std::string awesomefacePath = "assets/awesomeface.png";


   // data = stbi_load(FileSystem::getPath("resources/textures/awesomeface.png").c_str(), &width, &height, &nrChannels, 0);
    data = stbi_load(awesomefacePath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

  

    ourShader.setInt("texture3", 2);
    // texture 3
    // ---------
    glGenTextures(1, &texture3);
    glBindTexture(GL_TEXTURE_2D, texture3);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    std::string udpdevcube = "assets/cube_textures_512x512_3.png";


    // data = stbi_load(FileSystem::getPath("resources/textures/awesomeface.png").c_str(), &width, &height, &nrChannels, 0);
    data = stbi_load(udpdevcube.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


  
    ourShader.setInt("texture4", 3);
    // texture 4
  // ---------
    glGenTextures(1, &texture4);
    glBindTexture(GL_TEXTURE_2D, texture4);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    std::string plane_dev = "assets/plane_dev_512x512.png";


    // data = stbi_load(FileSystem::getPath("resources/textures/awesomeface.png").c_str(), &width, &height, &nrChannels, 0);
    data = stbi_load(plane_dev.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    
   

   // ourShader.setInt("texture1", texture1);
  //  ourShader.setInt("texture2", texture2);
  //  ourShader.setInt("texture3", texture3);
  //  ourShader.setInt("texture4", texture4);

   // ourShader.setInt("texture1", 1);
   // ourShader.setInt("texture2", 2);
   // ourShader.setInt("texture3", 3);
   // ourShader.setInt("texture4", 4);
    printf("texture3:%d\n", texture3);
        printf("texture3:%d\n", texture3);;
    //exit(0);

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
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, texture3);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, texture4);

        // activate shader
        ourShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        ourShader.setMat4("view", view);

        // render boxes
        glBindVertexArray(VAO);
      //  for (unsigned int i = 0; i < 10; i++)
        for (unsigned int i = 0; i < 1; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMat4("model", model);
            
            glDrawArrays(GL_TRIANGLES, 0, iNumTrianglesDraw);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;



    // TIP switch math to use blender coordinate system, will be easier to tranfer over assets and scenes
    // yaw
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        yaw += 1 ;
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        yaw -= 1;


    // pitch
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
        pitch += 1;
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        pitch -= 1;


    // x
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        cameraPos.x += 1;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        cameraPos.x -= 1;

    // y
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        cameraPos.y += 1;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        cameraPos.y -= 1;

    // z
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPos.z += 1;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        cameraPos.z -= 1;

    printf("yaw: %f, pitch: %f, camera.x: %f, camera.y: %f, camera.z: %f \n ", yaw, pitch , cameraPos.x , cameraPos.y, cameraPos.z);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}