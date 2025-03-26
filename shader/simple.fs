#version 330 core

uniform vec4 color;//vs로 부터 최종 입력된 변수를 uniform으로
out vec4 fragColor;//최종 출력 색상

void main() {
    fragColor = color;
}