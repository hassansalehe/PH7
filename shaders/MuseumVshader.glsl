// common for my both computers
#version 130

in vec4 vPosition;
in vec4 vColor;
in vec3 vNormal;
in vec2 vTexture;

out vec4 color;
out vec2 UV;
uniform mat4 ModelView;
uniform mat4 Projection;

uniform int ObjectID;

// for object picking
uniform bool PickingEnabled;
uniform int texture;
uniform vec4 pickingColor;

// Properties of the sun
// Properties of sun
uniform vec4 sunAmbient;
uniform vec4 sunDiffuse;
uniform vec4 sunSpecular;
uniform vec4 sunPosition;
uniform float Shininess;

// output values that will be interpretated per-fragment
out vec3 fN;
out vec3 fV;
out vec3 fL; // light1 send to shader

// constants to check for the shading model
const int PHONG_SHADING_MODEL = 273;
const int GOURAUD_SHADING_MODEL = 274;
uniform int HS_shading_model;

// for the reflection model
// constants for the reflection model
const int MODIFIED_PHONG_REFLECTION_MODEL = 300;
const int PHONG_REFLECTION_MODEL = 301;
uniform int HS_reflection_model;

void main() {

  //////////////////////////////
  gl_Position = Projection * ModelView * vPosition;

  if (PickingEnabled) {
    color = pickingColor;
    return;
  }

  if (ObjectID < 300) {
    if (HS_shading_model == PHONG_SHADING_MODEL) {
      // Phong shading (done in a fragments shader):
      // 1. Find vertex normals
      // 2. Interpolate vertex normals across polygons
      // 3. Apply modified Phong model at each fragment to find shades

      // normal direction in camera coordinates:
      fN = ( ModelView * vec4(vNormal, 0.0) ).xyz;

      //viewer direction in camera coordinates:
      fV = ( ModelView * vPosition ).xyz;

      fL = sunPosition.xyz; // sun direction
      if ( sunPosition.w != 0.0 ) {
        fL = sunPosition.xyz - fV;  //fixed light source
      }
      color = vColor;
    } else if (HS_shading_model == GOURAUD_SHADING_MODEL) {

      vec4 AmbientProduct  = sunAmbient * vColor;
      vec4 DiffuseProduct  = sunDiffuse * vColor;
      vec4 SpecularProduct = sunSpecular * vColor;

      color = vec4(0.0, 0.0, 0.0, 1.0);

      // Transform vertex  position into eye coordinates
      vec3 pos = (ModelView * vPosition).xyz;

      vec3 L = normalize( sunPosition.xyz - pos ); //light direction
      vec3 V = normalize( -pos ); // viewer direction

      // Transform vertex normal into eye coordinates
      vec3 N = normalize( ModelView*vec4(vNormal, 0.0) ).xyz;

      float Ks = 0.0;
      // applying the modified phong model

      if (HS_reflection_model == MODIFIED_PHONG_REFLECTION_MODEL) {
        // this is the modified phong model
        vec3 H = normalize( L + V ); // halfway vector
        Ks = pow(max(dot(N, H), 0.0), Shininess);
      } else if (HS_reflection_model == PHONG_REFLECTION_MODEL) {
        vec3 R = normalize( - reflect(L, N) );
        Ks = pow(max(dot(R, V), 0.0), Shininess);
      }

      // Compute terms in the illumination equation
      vec4 ambient = AmbientProduct;

      //set diffuse to 0 if light is behind the surface point:
      float Kd = max( dot(L, N), 0.0 );
      vec4  diffuse = Kd*DiffuseProduct;

      vec4  specular = Ks * SpecularProduct;

      // ignore also specular component if light is
      // behind the surface point
      if ( dot(L, N) < 0.0 ) {
        specular = vec4(0.0, 0.0, 0.0, 1.0);
      }

      color = color + ambient + diffuse + specular;
      color.a = 1.0;
    }
  }

  if (texture == 1) {
    UV = vTexture;
  } else {
    color = vColor;
  }
}
