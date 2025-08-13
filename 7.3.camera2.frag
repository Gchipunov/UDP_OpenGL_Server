#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in float vvtype;
// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;

void main()
{
 // linearly interpolate between both textures (80% container, 20% awesomeface)
 // FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);

 /// FragColor = mix(texture(texture3, TexCoord), texture(texture2, TexCoord), 0.2);

// FragColor = mix(texture(texture1, TexCoord), texture(texture3, TexCoord), 0.2);
 // FragColor = texture(texture3, TexCoord);
// FragColor = mix(texture(texture3, TexCoord), texture(texture4, TexCoord), 0.2);

vec4 color1=    mix(texture(texture3, TexCoord), texture(texture2, TexCoord), 0.2);
vec4 color2=    mix(texture(texture4, TexCoord), texture(texture1, TexCoord), 0.2);

//FragColor = mix(color2, color1, 0.2);

FragColor = texture(texture3, TexCoord);

}