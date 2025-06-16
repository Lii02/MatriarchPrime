#version 320 es
precision mediump float;

out vec4 outColor;

in VS_OUT {
    vec2 texCoords;
    vec3 normals;
} vsIn;

layout (std140, binding = 1) uniform PixelUniform {
    int type;
    vec4 color;
};

void main() {
    outColor = color * vec4(vsIn.texCoords, 0, 1);
}