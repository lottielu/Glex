#include "Pyramid.h"

Pyramid::Pyramid(float x, float y, float z) : model_matrix(glm::mat4(1.0))
{
  // model coordinates, origin at centre.
  GLfloat vertex_buffer [] {


		  -0.5 +x, -0.5 +y, -0.5 +z //0
	    , -0.5 +x, -0.5 +y,  0.5 +z //1

	    ,  0.5 +x, -0.5 +y,  0.5 +z //2
	    ,  0.5 +x, -0.5 +y, -0.5 +z //3

		,  0.0 +x,  0.5 +y,  0.0 +z //4
  };

  GLfloat vertex_buffer_length = sizeof(vertex_buffer);
  GLfloat g_colour_buffer_data[] =
  {
		  0.0,1.0,1.0,
		  0.0,1.0,1.0,
		  0.0,1.0,1.0,

		  0.0,1.0,1.0,
		  0.0,1.0,1.0,
		  0.0,1.0,1.0,

		  0.0,1.0,1.0,
		  0.0,1.0,1.0,
		  0.0,1.0,1.0

  };

  colour_buffer_length = sizeof(g_colour_buffer_data);

//  element_buffer_length = 36;
  GLuint element_buffer []  {
		  //bottom
		  	 0, 1, 3
		  	, 1, 2, 3
		  	//left
		  	,0 , 4, 1
		  	// front
		  	,0 , 4, 3
		  	// back
		  	, 1, 4, 2
		  	// right
		  	,2, 4, 3
  };

  element_buffer_length= sizeof(element_buffer);
  // Transfer buffers to the GPU
  //

  // create buffer
  glGenBuffers(1, &vertex_buffer_token);

  // immediately bind the buffer and transfer the data
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_token);
  glBufferData(GL_ARRAY_BUFFER, vertex_buffer_length, vertex_buffer, GL_STATIC_DRAW);

  glGenBuffers(1, &colour_buffer_token);
  glBindBuffer(GL_ARRAY_BUFFER,colour_buffer_token);
  glBufferData(GL_ARRAY_BUFFER, colour_buffer_length, g_colour_buffer_data, GL_STATIC_DRAW);

  glGenBuffers(1, &element_buffer_token);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_token);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, element_buffer_length, element_buffer, GL_STATIC_DRAW);
  //rotateX(90.0f);
}

Pyramid::~Pyramid() {
}

#ifdef DEBUG
#define checkGLError() checkError(__FILE__, __LINE__)
#else
// define symbol to be nothing
#define checkGLError()
#endif

void Pyramid::checkError(std::string file, int line) {
  GLenum gl_error = glGetError();
  if(GL_NO_ERROR != gl_error) {
    std::cerr << "GL error in " << file << " at line " << line << " error: " << gl_error << std::endl;
    exit(-1);
  }
}

void Pyramid::Draw(GLuint program_token) {
  if(!glIsProgram(program_token)) {
    std::cerr << "Drawing Pyramid with invalid program" << std::endl;
    return;
  }

  GLint validation_ok;
  glValidateProgram(program_token);
  glGetProgramiv(program_token, GL_VALIDATE_STATUS, &validation_ok);
  if(!validation_ok) {
    GLint maxLength = 0;
    glGetProgramiv(program_token, GL_INFO_LOG_LENGTH, &maxLength);

    //The maxLength includes the NULL character
    std::vector<char> errorLog(maxLength);
    glGetProgramInfoLog(program_token, maxLength, &maxLength, &errorLog[0]);

    std::cerr << "Invalid program " << program_token << " with error code " << validation_ok << std::endl;
    for(auto c: errorLog) {
      std::cerr << c;
    }
    exit(-1);
  }

  GLuint position_attrib = glGetAttribLocation(program_token, "position");
  checkGLError();

  GLuint model_uniform = glGetUniformLocation(program_token, "model");
  checkGLError();

  glUseProgram(program_token);
  checkGLError();


  glUniformMatrix4fv(model_uniform,1,false, glm::value_ptr(model_matrix));

  // use the previously transferred buffer as the vertex array.  This way
  // we transfer the buffer once -- at construction -- not on every frame.
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_token);
  glVertexAttribPointer(
                        position_attrib,               /* attribute */
                        3,                             /* size */
                        GL_FLOAT,                      /* type */
                        GL_FALSE,                      /* normalized? */
                        0,                             /* stride */
                        (void*)0                       /* array buffer offset */
                        );
  glEnableVertexAttribArray(1);

  checkGLError();

  glBindBuffer(GL_ARRAY_BUFFER, colour_buffer_token);
  glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,(void*)0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_token);
  glDrawElements(
                 GL_TRIANGLES,
                 element_buffer_length,
                 GL_UNSIGNED_INT,
                 (GLvoid*) 0
                 );

  checkGLError();

  glDisableVertexAttribArray(position_attrib);
}

void Pyramid::rotateX(float angle)
{
	glm::vec3 unit_x_axis(0.0,1.0,0.0);
	model_matrix = glm::rotate(this->model_matrix, angle, unit_x_axis);
}
