// common for my both computers
#version 130

in  vec4 color;
uniform int ObjectID;

void main()
{

  if( gl_FrontFacing || ObjectID == 123 )
    gl_FragColor = color;
  else
    gl_FragColor = vec4(1.0, 0.8, 0.8, 0.0);
//    gl_FragColor = vec4(0.556863, 0.137255, 0.137255, 1.0);
}

