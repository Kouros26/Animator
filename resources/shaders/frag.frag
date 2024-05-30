#version 460 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor.rgb = texture(ourTexture, TexCoord).rgb/* * ourColor*/;
    FragColor.a = 1.0;
}