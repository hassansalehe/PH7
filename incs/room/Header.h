///////////////////////////////////////////////////////////////////////////////
//
//                   COMP 510, Computer Graphics, Spring 2016
//                              Final project
//                PH7: A virtual Museum Based on OpenGL and Glut
//
//                            (c) 2016 - Hassan & Pirah.
//            Copying without the authors consent is strictly prohibited.
//
///////////////////////////////////////////////////////////////////////////////
//
// Implements the Header of the museum
//
///////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_CLASS
#define HEADER_CLASS

#include "Object.h"
#include "Angel.h"

class Header: public Object {
  private:
    // Vertices of the front header
    point4 vertices[3] = {
      // front wall
      point4( -0.5,  0.5,  0.8, 1.0 ), // bottom left
      point4(  0.5,  0.5,  0.8, 1.0 ), // bottom right
      point4(  0.0,  0.8,  0.8, 1.0 ) // Top
    };

	vec2 tex_coords[3]={ vec2(1.0,  1.0), vec2( 0.0,  0.0), vec2(0.0,  1.0)	};

    void quad() {
      // Initialize colors
      colors[vertexIndex] = earth; points[vertexIndex] = vertices[0]; vertexIndex++;
      colors[vertexIndex] = earth; points[vertexIndex] = vertices[1]; vertexIndex++;
      colors[vertexIndex] = green; points[vertexIndex] = vertices[2]; vertexIndex++;
    }
  void drawLogo() {

	 // GLuint Texture= loadBMP_custom("libs/logo.bmp");
	  // Data read from the header of the BMP file
	  unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	  unsigned int dataPos;     // Position in the file where the actual data begins
	  unsigned int width, height;
	  unsigned int imageSize;   // = width*height*3
	  // Actual RGB data
	  unsigned char * data;
	  // Open the file
	  FILE * file = fopen("libs/logo.bmp","rb");
	  if (!file)
		printf("Image could not be opened\n");
	  if ( fread(header, 1, 54, file)!=54 ) // If not 54 bytes read : problem
		  printf("Not a correct BMP file\n");

	  if ( header[0]!='B' || header[1]!='M' )
		printf("Not a correct BMP file\n");

	  dataPos    = *(int*)&(header[0x0A]);
	  imageSize  = *(int*)&(header[0x22]);
	  width      = *(int*)&(header[0x12]);
	  height     = *(int*)&(header[0x16]);

	  // Some BMP files are misformatted, guess missing information
	  if (imageSize == 0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
	  if (dataPos == 0)      dataPos=54; // The BMP header is done that way

	  // Create a buffer
	  data = new unsigned char [imageSize];

	  // Read the actual data from the file into the buffer
	  fread(data,1,imageSize,file);

	  //Everything is in memory now, the file can be closed
	  fclose(file);

	  // Create one OpenGL texture
	  GLuint textureID;
	  glGenTextures(1, &textureID);

	  // "Bind" the newly created texture : all future texture functions will modify this texture
	  glBindTexture(GL_TEXTURE_2D, textureID);

	  // Give the image to OpenGL
	  glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	  glGenerateMipmap(GL_TEXTURE_2D);

	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  }

  void initializeDataBuffers( GLuint program ){
	drawLogo();// setting texture mapping data

	// Create a vertex array object
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    points_size = sizeof(point4) * numVertices;
    colors_size = sizeof(color4) * numVertices;
    int texture_size = sizeof(vec2) * numVertices;

    // Create and initialize a buffer object
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, points_size + colors_size + texture_size, NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, points_size, points );
    glBufferSubData( GL_ARRAY_BUFFER, points_size, colors_size, colors );
    glBufferSubData( GL_ARRAY_BUFFER, points_size + colors_size, texture_size, tex_coords );

    // set up vertex arrays
    size_t size = 0;
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(size) );

    size += points_size;
    GLuint vColor = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(size) );

    size += colors_size;
    GLuint vTexture = glGetAttribLocation( program, "vTexture" );
    glEnableVertexAttribArray( vTexture );
    glVertexAttribPointer( vTexture, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(size) );
	int TextureFlag = glGetUniformLocation(program, "texture");
    glUniform1i( TextureFlag, 1 );
    glUniform1f( glGetUniformLocation(program, "Shininess"), shininess );

    // Set current program object
    glUseProgram( program );

    // Retrieve transformation uniform variable locations
    ModelView = glGetUniformLocation( program, "ModelView" );
    Projection = glGetUniformLocation( program, "Projection" );

    // Set projection matrix
    mat4  projection = Ortho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    //projection = Perspective( 45.0, 1.0, 0.5, 3.0 );
    glUniformMatrix4fv( Projection, 1, GL_TRUE, projection );

    // Enable hiddden surface removal
    glEnable( GL_DEPTH_TEST );

    // Set state variable "clear color" to clear buffer with.
    glClearColor( 1.0, 1.0, 1.0, 1.0 );
  }

  public:
    /**
     * Initializes the vertices and colors of the empty header object.
     */
    void initialize(GLuint program) {

      // Object identifier
      object_id = 101;

      // set picking color
      isPicking = false;
      pickingColor = color4(1.0, 0.0, 0.0, 1.0); // (255,0,0)

      numVertices = 3; // (21 faces)(2 triangles/face)(3 vertices/triangle)
      points = new point4[numVertices];
      colors = new color4[numVertices];
      normals = new normal3[numVertices];

      // quad generates two triangles for each face and assigns colors
      //    to the vertices
      vertexIndex = 0;
      quad();

      // compute normals
      calculateNormals();

      initializeDataBuffers( program );
    }

   void calculateModelViewMatrix() {
     model_view = parent_model_view;
   }

   /**
     * The general display function launched by the Glut
     */
    void display( GLuint program )
    {
      int TextureFlag = glGetUniformLocation(program, "texture");
	glUniform1i( TextureFlag, 1 );

      Object::display( program );

     TextureFlag = glGetUniformLocation(program, "texture");
     glUniform1i( TextureFlag, 0 );
    }


    void idle( void )
    {
      glutPostRedisplay();
    }

    // no individual rotations
    void rotateLeft(float delta) {}
    void rotateUp(float delta) {}

    void checkIfPicked( unsigned char pixel[4] ) {
      if ( pixel[0] == 255 && pixel[1] == 0 && pixel[2] == 0 ) { // Header
#ifdef DEBUG
        printf("Header selected\n");
#endif
      }
    }
};

#endif // end Header
