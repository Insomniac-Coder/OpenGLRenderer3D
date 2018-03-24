#version 330

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D sampler;

void main()

{
	gl_FragColor = texture2D(sampler, texCoord0) * clamp(dot(-vec3(0,0,1.2), normal0), 0.0, 1.0);
}