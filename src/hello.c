#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main() {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) return -1;

    /* Create a GLFW debug context */
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (GLEW_OK != glewInit())
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        // std::cout << "glewInit failed, something is seriously wrong." << std::endl;
    }

    /* Sets the debug messages to run a certain callback function */
    // glEnable(GL_DEBUG_OUTPUT);
    // glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    // glDebugMessageCallback(glDebugOutput, nullptr);
    // glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

    // std::cout << glGetString(GL_VERSION) << std::endl;

    /* Best to initialize the triangles to be drawn outside of the game loop */
    /*float triangle_positions[] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };*/
    float square_positions[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };
    unsigned int square_indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // TRIANGLE
   /* unsigned int triangle_buffer;
    glGenBuffers(1, &triangle_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, triangle_buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), triangle_positions, GL_STATIC_DRAW);
    
    glVEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    */
    
    // SQUARE
    unsigned int square_buffer;
    glGenBuffers(1, &square_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, square_buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), square_positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    unsigned int index_buffer_object;
    glGenBuffers(1, &index_buffer_object);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_object);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), square_indices, GL_STATIC_DRAW);


    // ShaderProgramSource source = ParseShader("res/shaders/basic.shader");
    
    // unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    // glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Draw the bound buffer */

        /* Without an index buffer TRIANGLE */
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        /* With an index buffer SQUARE */
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL); // Since the index buffer is already bound to the element array buffer it does not need to be passed as an argument here
        //TODO added error here
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    // glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}