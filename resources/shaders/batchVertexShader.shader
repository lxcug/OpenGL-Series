#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_textCoord;
layout(location = 3) in float a_textSlotIdx;

out vec4 v_color;
out vec2 v_textCoord;
out float v_textSlotIdx;

uniform mat4 u_modelViewProjection;

void main()
{
    gl_Position = u_modelViewProjection * position;
    v_color = a_color;
    v_textCoord = a_textCoord;
    v_textSlotIdx = a_textSlotIdx;
}