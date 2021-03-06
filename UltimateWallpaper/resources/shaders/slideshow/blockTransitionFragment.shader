﻿#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 texCoords;
flat in float transition;

uniform float u_brightnessFilter;
uniform float u_highAmplitude;
uniform sampler2D u_tex0;
uniform sampler2D u_tex1;

vec3 rgb2hsv(vec3 c)
{
	vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
	vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
	vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

	float d = q.x - min(q.w, q.y);
	float e = 1.0e-10;
	return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsv2rgb(vec3 c)
{
	vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
	vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
	return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main() {
	vec3 tex0Color = texture(u_tex0, texCoords).rgb;
	vec3 tex1Color = texture(u_tex1, texCoords).rgb;

	vec3 hsv = rgb2hsv(vec3(tex0Color * (1. - transition) + tex1Color * transition));
	hsv.b *= 1.f + u_highAmplitude * (1.f + pow(hsv.b, u_brightnessFilter));
	color = vec4(hsv2rgb(hsv), 1.f);

};