#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define MAX_FGETS_COUNT 140 // There will be a problem if a shader line contains more characters than this

void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam)
{
    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    printf("---------------\n");
    printf("Debug message ( %u ): %s \n", id, message);

    switch (source)
    {
    case GL_DEBUG_SOURCE_API:             printf("Source: API"); break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   printf("Source: Window System"); break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER: printf("Source: Shader Compiler"); break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:     printf("Source: Third Party"); break;
    case GL_DEBUG_SOURCE_APPLICATION:     printf("Source: Application"); break;
    case GL_DEBUG_SOURCE_OTHER:           printf("Source: Other"); break;
    } printf("\n");

    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:               printf("Type: Error"); break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: printf("Type: Deprecated Behaviour"); break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  printf("Type: Undefined Behaviour"); break;
    case GL_DEBUG_TYPE_PORTABILITY:         printf("Type: Portability"); break;
    case GL_DEBUG_TYPE_PERFORMANCE:         printf("Type: Performance"); break;
    case GL_DEBUG_TYPE_MARKER:              printf("Type: Marker"); break;
    case GL_DEBUG_TYPE_PUSH_GROUP:          printf("Type: Push Group"); break;
    case GL_DEBUG_TYPE_POP_GROUP:           printf("Type: Pop Group"); break;
    case GL_DEBUG_TYPE_OTHER:               printf("Type: Other"); break;
    } printf("\n");

    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:         printf("Severity: high"); break;
    case GL_DEBUG_SEVERITY_MEDIUM:       printf("Severity: medium"); break;
    case GL_DEBUG_SEVERITY_LOW:          printf("Severity: low"); break;
    case GL_DEBUG_SEVERITY_NOTIFICATION: printf("Severity: notification"); break;
    } printf("\n");
    printf("\n");
}

typedef struct ShaderProgramSource
{
    char* VertexSource;
    char* FragmentSource;
} ShaderProgramSource;

/*const char* readFile(char* filepath) {
	char* buffer = '\0';
	long length;
	FILE* f = fopen(filepath, "rb");

	if (f != NULL) {
		fseek(f, 0, SEEK_END); // Will fail with files of size > 4GB
		length = ftell(f);
		fseek(f, 0, SEEK_SET);
		buffer = malloc(length + 1);
		if (buffer) {
			fread(buffer, 1, length, f);
		}
		fclose(f);
		buffer[length] = '\0';
	}

	return buffer;
}*/

static ShaderProgramSource ParseShader(const char* filepath)
{
    FILE* f = fopen(filepath, "rb");
    // char* buffer = readFile(filepath);
    
    // Open stream using filepath
    // 

    typedef enum ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    } ShaderType;

    char* line;
    char* ss[2];
    ShaderType type = NONE;
    while (fgets(line, 120, f))
    {
        if(strncmp(line, "#shader ", 8)) {
            if(strcmp(line, "#shader vertex")) {
                type = VERTEX;
            } else if(strcmp(line, "shader fragment")) {
                type = FRAGMENT;
            }
        } else {
            strcat(ss[(int)type], line); // Am I sure that this will keep the \n ?
        }
    }
    ShaderProgramSource out = { .VertexSource = ss[0], .FragmentSource = ss[1] };
    return out;
}

static unsigned int CompileShader(unsigned int type, const char* src)
{
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);
    
    /* Error handling */
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(sizeof(char) * length);
        glGetShaderInfoLog(id, length, &length, message);
        printf("Failed to compile %s shader\n", (type == GL_VERTEX_SHADER ? "Vertex":"Fragment"));
        printf("%s\n", message);
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(char* vertexShader, char* fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

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
        printf("glewInit failed, something is seriously wrong.\n");
    }

    /* Sets the debug messages to run a certain callback function */
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(glDebugOutput, NULL);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);

    printf("%s\n", glGetString(GL_VERSION));

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

    ShaderProgramSource source = ParseShader("res/shaders/basic.shader");
    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);

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