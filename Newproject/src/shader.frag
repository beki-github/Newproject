# version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 Texcoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float visibility;
void main()
{
      FragColor =mix(texture(texture1,Texcoord),texture(texture2,Texcoord),visibility)*vec4(ourColor,1.0f);
};