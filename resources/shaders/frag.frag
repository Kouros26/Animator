#version 460 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

void main()
{
    vec4 texColor1 = texture(texture_diffuse1, TexCoord);
    vec4 texColor2 = texture(texture_diffuse2, TexCoord);
    vec4 texColor3 = texture(texture_diffuse3, TexCoord);
    vec4 specularMap1 = texture(texture_specular1, TexCoord);
    vec4 specularMap2 = texture(texture_specular2, TexCoord);

    vec4 finalDiffuseColor = texColor1 + texColor2 + texColor3;

    vec4 finalSpecularColor = specularMap1 + specularMap2;

    FragColor = (finalDiffuseColor + finalSpecularColor) * vec4(ourColor, 1.0);
}