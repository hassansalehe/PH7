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
// Implements the basic functionalities of an object.
// Each object performs the following operations.
// 1. Initialization - initializing the object vertices, colors, textures, and other attributes
// 2. Sending this information to the GPU
// 3. Displaing the object
// 4. Manipulating the object.
// 5. Its model-view and transformation matrices will be calculated using the parent's matrices.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef OBJECT_CLASS
#define OBJECT_CLASS

#include <vector>
#include "Angel.h"

typedef vec4  color4;
typedef vec4  point4;
typedef vec3  normal3;

class Object {
protected:

  // for holding the children of the object
  vector<Object*> children;
public:
  GLuint object_id;
  GLuint objectID;
  int autoOnOff=0;

  // Model-view and projection matrices uniform location
  GLuint  ModelView, Projection;

  // for reflection and shading
  GLuint ReflectionModel;
  GLuint HS_reflection_model = 300;

  GLuint ShadingModel;
  GLuint HS_shading_model = 273;

  // model view matrices
  mat4 model_view        = Identity();
  mat4 my_model_view     = Identity();
  mat4 parent_model_view = Identity();

  GLuint vao;
  GLuint buffer;

  size_t points_size;
  size_t colors_size;
  size_t normals_size;

  int numVertices;
  point4 * points;
  color4 * colors;
  normal3 * normals;

  int vertexIndex;
  float scaleFactor = 1.0;

  // Array of rotation angles (in degrees) for each coordinate axis
  enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };
  int  Axis = Yaxis;
  GLfloat  Theta[NumAxes] = { 5.0, 0.0, 0.0 };
  GLfloat  Distance[NumAxes] = { 0.0, 0.0, 0.0 };

  color4 blue   = color4( 0.0, 0.0, 1.0, 1.0 );  // blue
  color4 black  = color4( 0.0, 0.0, 0.0, 1.0 );  // black
  color4 red    = color4( 1.0, 0.0, 0.0, 1.0 );  // red
  color4 yellow = color4( 1.0, 1.0, 0.0, 1.0 );  // yellow
  color4 green  = color4( 0.0, 1.0, 0.0, 1.0 );  // green
  color4 earth  = color4(125.0/255, 68.0/255, 29.0/255, 1.0 );

  // fields for picking
  int isPicking;
  color4 pickingColor;

public:

  /**
   * appends a child object to this node
   */
  void appendChild(Object * child) {
    children.push_back( child );
  }


  /**
   * pushes all child nodes to a queue
   */
  void pushChildrenToQueue(queue<Object*> & queue) {

    for(Object* childObject : children) {
      queue.push( childObject );
    }
  }


  /**
   * Sends the model view matrix of this object to
   * to all its child nodes in the object tree
   */
  void sendModeViewToChildren() {
    for(Object* childObject : children) {
      childObject->getParentModelView( model_view );
    }
  }


  /**
   * A function to receive parent matrix
   */
  void getParentModelView(mat4 p_model_view ) {
    parent_model_view = p_model_view;
  }


  /**
   * Implement this function in an object for
   * for custom transformations of individual
   * objects. See the wrong rotation of skull
   */
  virtual void calculateModelViewMatrix()  = 0;
  //virtual void move();


  void changeShading() {
    HS_shading_model = (HS_shading_model == 273 ? 274: 273);
    glUniform1i(ShadingModel, HS_shading_model); // send to the shaders(GPU)
    glutPostRedisplay();
  }


  void changeReflection() {
    HS_reflection_model = HS_reflection_model == 300? 301 : 300;
    glUniform1i(ReflectionModel, HS_reflection_model);
    glutPostRedisplay();
  }


  /**
   * For initializing the vertices of an object
   * and sending them to the GPU
   */
  virtual void initialize(GLuint program) = 0;


  /**
   * The general display function launched by the Glut
   */
  void display( GLuint program )
  {
    // bind vertex array
    glBindVertexArray( vao );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    // calculate model view here use this to calculate
    // custom transformations
    calculateModelViewMatrix();

    // Send values for picking
      GLuint picking = glGetUniformLocation( program, "PickingEnabled" );
      glUniform1i( picking, isPicking );
      GLuint uniColor = glGetUniformLocation( program, "pickingColor" );
      glUniform4fv( uniColor, 1, pickingColor );

    // send object id
    objectID = glGetUniformLocation( program, "ObjectID" );
    glUniform1i(objectID, object_id);

    // send the shading model (phong vs gouraud)
    ShadingModel = glGetUniformLocation( program, "HS_shading_model" );
    glUniform1i( ShadingModel, HS_shading_model );

    // send current reflection model
    ReflectionModel = glGetUniformLocation( program, "HS_reflection_model" );
    glUniform1i( ReflectionModel, HS_reflection_model );

    // send model view
    glUniformMatrix4fv( ModelView, 1, GL_TRUE, model_view );
    glDrawArrays( GL_TRIANGLES, 0, numVertices );

    // reverse the object identifier
    glUniform1i(objectID, 0);

    // release vertex handler
    glBindVertexArray( 0 );
  }


  /**
   * The reshape function.
   */
  void reshape( int w, int h )
  {
    glViewport( 0, 0, w, h );

    mat4  projection;

    //switch(projectionOption) {
    //   case HS_ORTHOGRAPHIC:

    if (w <= h)
      projection = Ortho(-1.0, 1.0, -1.0 * (GLfloat) h / (GLfloat) w,
                         1.0 * (GLfloat) h / (GLfloat) w, -1.0, 1.0 );
    else  projection = Ortho(-1.0* (GLfloat) w / (GLfloat) h, 1.0 *
        (GLfloat) w / (GLfloat) h, -1.0, 1.0, -1.0, 1.0);
    //break;
    //   case HS_PERSPECTIVE:
    //      GLfloat aspect = GLfloat(w)/h;
    //      projection = Perspective( 45.0, aspect, 1.0, -1.0 );
    //      break;
    //}

    glUniformMatrix4fv( Projection, 1, GL_TRUE, projection );
  }


  /**
   * the idle function
   */
  virtual void idle() = 0;

  virtual void rotateLeft( GLfloat delta ) = 0;

  virtual void rotateUp(  GLfloat delta ) = 0;

  virtual void zoomOut(GLfloat delta) {
    scaleFactor += delta;
  }


  /**
   * For zooming in the object
   */
  virtual void zoomIn(GLfloat delta) {
    scaleFactor -= delta;
  }


  /**
   * For moving toward the museum if delta > 0
   * and moving away if delta < 0
   */
  void moveForward(  GLfloat delta ) {
    printf("moving room\n");
       Distance[Zaxis] += delta;
       scaleFactor += delta;

       glutPostRedisplay();
  }
  
  void toggleAuto(){
	if(autoOnOff==0)
	  autoOnOff=1;
	else
	  autoOnOff=0;
  }


  /**
   * Resets all parameters to defult.
   */
  virtual void reset() {
    scaleFactor = 1.0;

    Theta[Xaxis] = 5.0; Theta[Yaxis] = Theta[Zaxis] = 0.0;
    Distance[Xaxis] = Distance[Yaxis] = Distance[Zaxis] = 0.0;
  }

  void calculateNormals() {

    int triangles = numVertices / 3;
    for(int i = 0; i < triangles; i++) {

      point4 p0 = points[3*i + 0];
      point4 p1 = points[3*i + 1];
      point4 p2 = points[3*i + 2];

      normal3 n = normalize( cross((p1-p0), (p2-p0)) );

      normals[3*i + 0] = n;
      normals[3*i + 1] = n;
      normals[3*i + 2] = n;
    }

    // find the average normal of each normal of a point
    for(int i = 0; i < numVertices; i++) {

      vec3 p = vec3(0.0, 0.0, 0.0);
      int count = 0;

      for(int j = 0; j < numVertices; j++) {
        if(points[i] == points[j]) {
          p += normals[j];
          count++;
        }
      }

      // normalize the sum of neighbor normals
      normals[i] = normalize( p );
    }
  }

  virtual void checkIfPicked( unsigned char pixel[4] ) = 0;

  void enablePicking() {
    isPicking = true;
  }

  void disablePicking() {
    isPicking = false;
  }

  inline mat4 Identity()
  {
    mat4 c;
    for(int i=0; i<4; i++) for(int j=0; j<4; j++) c[i][j]=0.0;
    for(int i=0; i<4; i++) c[i][i] = 1.0;
    return c;
  }

};

#endif // end object class
