# version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 Texcoord;
in vec3 normals;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 lightColor;
void main()
{
      FragColor = texture(texture1,Texcoord)*vec4(lightColor,1.0f);
};