#version 120

varying vec2 texCoord0;
varying vec3 normal0;

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

uniform mat4 transform;

void main() {
    
    gl_Position = transform * vec4(position, 1.0);
    texCoord0 = texCoord;
    // Setting to zero means no translation is performed, since light source should be parallel and not move.
    normal0 = (transform * vec4(normal, 0.0)).xyz;
}