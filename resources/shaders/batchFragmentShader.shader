#version 410 core

layout(location = 0) out vec4 o_color;

in vec4 v_color;
in vec2 v_textCoord;
in float v_textSlotIdx;

uniform sampler2D u_textures[2];

void main()
{
    int idx = int(v_textSlotIdx);
    vec4 textColor = texture(u_textures[idx], v_textCoord);
    o_color = textColor;
//    o_color = v_color;
}