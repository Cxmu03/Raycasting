#version 330 core

uniform bool scoped;

in vec3 vColor;

out vec4 FragColor;

void main() {
    vec2 distToCenter = vec2(abs(960.f - gl_FragCoord.x), abs(540.f - gl_FragCoord.y));
    if(distToCenter.x * distToCenter.x + distToCenter.y * distToCenter.y < 20) {
        FragColor = vec4(0.f, 0.f, 0.f, 1.f);
    }
    else {
        FragColor = vec4(vColor.xyz, 1.f);
    }
}