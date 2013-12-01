#version 330

vertex
{
  layout(location = 0) in vec4 position;

  void main()
  {
    gl_Position = position;
  }
}

fragment
{
  uniform vec4 color;
  
  out vec4 outputColor;
  void main()
  {
    outputColor = color;
  }
}

