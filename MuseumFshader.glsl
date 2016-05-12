varying  vec4 color;

void main()
{
  if(gl_FrontFacing )
    gl_FragColor = color;
  else
    gl_FragColor = vec4(1.0, 0.8, 0.8, 0.0);
//    gl_FragColor = vec4(0.556863, 0.137255, 0.137255, 1.0);
}

