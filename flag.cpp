#include <glad/glad.h>

#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>


#include <TextureUtils.h>

#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// math
///normalize
float normalize (float min, float max, float val) { 
return (val - min) / (max - min); 
}


int main()
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
    Shader ourShader("flag.shader.vs", "flag.shader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------


        glm::vec3 flagPositions[] = {

        glm::vec3( 0.0f,  0.0f,  0.0f)
    
    };


std::vector<glm::vec3> vertices1;
std::vector<glm::uvec3> indices1;


int slices = 500;

  for(int j=0; j<=slices; ++j) {
    for(int i=0; i<=slices; ++i) {

    float x = ((float)i/(float)slices)*2-1.0;
      float y = ((float)j/(float)slices)*2-1.0;
      float z = 0.0; ///float z = 0;



// std::cout << "Vert x y z: " << x << " " << y << " " << z << " " << std::endl;
      vertices1.push_back(glm::vec3(x, y, z));

      ///*
// std::cout << "Vert UV x, y: " << normalize(-1, 1, x) << " " << normalize(-1, 1, y) << " " << std::endl;
vertices1.push_back(glm::vec3(normalize(-1, 1, x), normalize(-1, 1, y), 0));
       


    }
  }

  for(int j=0; j<slices; ++j) {
    for(int i=0; i<slices; ++i) {

      int row1 = j * (slices+1);
      int row2 = (j+1) * (slices+1);

      indices1.push_back(glm::uvec3(row1+i, row1+i+1, row2+i+1));
      indices1.push_back(glm::uvec3(row1+i, row2+i+1, row2+i));

    }
  }
    


    ///* unsigned int VBO, VAO;

    unsigned int VBO, VAO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    ///* 
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData( GL_ARRAY_BUFFER, vertices1.size()*sizeof(glm::vec3), vertices1.data(), GL_STATIC_DRAW );


///* 
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices1.size()*sizeof(glm::uvec3), indices1.data(), GL_STATIC_DRAW );


// position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //5 * sizeof(float)
    glEnableVertexAttribArray(0);
// texture coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // (1, 2 ; 5 * sizeof(float)
    glEnableVertexAttribArray(1);

GLint lenght1 = (GLint)indices1.size()*3;

    // load and create a texture 
    // -------------------------
    unsigned int texture1, texture2;
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

    bool hasAlpha;

    char filename[] = "flag1.png"; 

    bool success1 = loadPngImage(filename, width, height, hasAlpha, &textureImage);

    unsigned char *data = textureImage;



        std::cout << "Image loaded " << width << " " << height << " alpha " << hasAlpha << std::endl;



    if (success1) //if (data)
    {

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }






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


    GLubyte *textureImage1;



    char filename1[] = "flaglogo1.png"; 
    success1 = loadPngImage(filename1, width, height, hasAlpha, &textureImage1);


    data = textureImage1;



        std::cout << "Image loaded " << width << " " << height << " alpha " << hasAlpha << std::endl;



    if (success1) //if (data)
    {


        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }


    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);


unsigned int framenum = 0;
float sinewave = 0;


//for camera tests
// ///-1.164 1.513 2.272 // ///-60.0(-65.0) -35.0
// ///-1.50 2.26 2.72 // ///-70,0 -30.0
// std::cout << "   camera Yaw; " << camera.Yaw << "   camera Pitch; " << camera.Pitch << " " << std::endl;
camera.SetValues (glm::vec3(-1.50f, 2.26f, 2.72f), -70.0, -35.0);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {

framenum++;
// float sinewave = 0;
//if framenum % 5 = 0
// if (framenum % 10 == 0) 
sinewave = sin(framenum*0.001); /// can try: sin(framenum)/2 + 0,5

        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
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

        // activate shader
        ourShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);
        
// std::cout << "sinewave : " << sinewave << std::endl;

float framenum1 = framenum;
ourShader.setFloat("sinewave", sinewave);
ourShader.setFloat("framenum", framenum1);

        // render boxes
        glBindVertexArray(VAO);
///*

             // calculate the model matrix for each object and pass it to shader before drawing
             glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
             model = glm::translate(model, flagPositions[0]);
             float angle = 20.0f * 1; //= 20.0f * i;
             //model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
             ourShader.setMat4("model", model);


///* Wireframe mode
// glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

             glDrawElements(GL_TRIANGLES, lenght1, GL_UNSIGNED_INT, 0);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

///* 
    glDeleteBuffers(1, &EBO);

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
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
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

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}