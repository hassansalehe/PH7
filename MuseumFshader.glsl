// common for my both computers
#version 400

in vec4 color;
uniform int ObjectID;

// for object picking
uniform bool PickingEnabled;
uniform vec4 pickingColor;

// Properties of sun
uniform vec4 sunAmbient;
uniform vec4 sunDiffuse;
uniform vec4 sunSpecular;
uniform vec4 sunPosition;
uniform float Shininess;

// per-fragment interpolated values from the vertex shader
in vec3 fN;
in vec3 fV;
in vec3 fL;

// constants for the reflection model
const int MODIFIED_PHONG_REFLECTION_MODEL = 300;
const int PHONG_REFLECTION_MODEL = 301;
uniform int HS_reflection_model;

// constants to check for the shading model
const int PHONG_SHADING_MODEL = 273;
const int GOURAUD_SHADING_MODEL = 274;
uniform int HS_shading_model;

void main()
{
  if( PickingEnabled ) {
    gl_FragColor = pickingColor;
    return;
  }

  if(ObjectID == 100) {
    if ( HS_shading_model == PHONG_SHADING_MODEL ) {
      vec4 material_ambient = color; // vec4( 1.0, 0.0, 1.0, 1.0 );
      vec4 material_diffuse = color; //vec4( 1.0, 0.8, 0.0, 1.0 );
      vec4 material_specular = color; // vec4( 1.0, 0.0, 1.0, 1.0 );

      vec4 ambient  = sunAmbient * material_ambient;
      vec4 diffuse  = sunDiffuse * material_diffuse;
      vec4 specular = sunSpecular * material_specular;

      // Phong shading (done in a fragments shader):
      // 1. Find vertex normals
      // 2. Interpolate vertex normals across polygons
      // 3. Apply modified Phong model at each fragment to find shades

      vec4 outColor = vec4(0.0, 0.0, 0.0, 1.0);

      // Normalize the input lighting vectors
      vec3 N = normalize(fN);
      vec3 V = normalize(fV);
      vec3 L = normalize(fL);

      float Kd = max(dot(L, N), 0.0);
      diffuse = Kd*diffuse;

      float Ks = 0.0;
      // applying the modified phong model
      if( HS_reflection_model == MODIFIED_PHONG_REFLECTION_MODEL ) {
        // this is the modified phong model
        vec3 H = normalize( L + V ); // halfway
        Ks = pow(max(dot(N, H), 0.0), Shininess);
      }
      else if( HS_reflection_model == PHONG_REFLECTION_MODEL ) {
        vec3 R = normalize( - reflect(L, N) );
        Ks = pow(max(dot(R, V), 0.0), Shininess);
      }

      specular = Ks*specular;

      // discard the specular highlight if the light's behind the vertex
      if( dot(L, N) < 0.0 ) {
        specular = vec4(0.0, 0.0, 0.0, 1.0);
      }

      //vec4 ambient = Ambient1Product;

      outColor =  outColor + ambient + diffuse + specular;
      outColor.a = 1.0;
      gl_FragColor = outColor;
    }
    else if ( HS_shading_model == GOURAUD_SHADING_MODEL ) {
      // If Gouraud (smooth) shading (done in a vertex shader):
      // 1. Find average normal at each vertex (vertex normals)
      // 2. Apply (modified) Phong model at each vertex
      // 3. Interpolate vertex shades across each polygon

      gl_FragColor = color;
    }
  }
  else if( gl_FrontFacing || ObjectID == 123 )
    gl_FragColor = color;
  else
    gl_FragColor = vec4(1.0, 0.8, 0.8, 0.0);
//    gl_FragColor = vec4(0.556863, 0.137255, 0.137255, 1.0);
}

