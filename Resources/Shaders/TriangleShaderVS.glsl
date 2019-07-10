attribute vec3 a_posL;
varying vec3 v_color;
attribute vec3 a_color;
uniform mat4 u_rot;
uniform mat4 model;
attribute vec2 a_uv;
attribute vec2 a_uv2;
varying vec2 v_uv;
varying vec2 v_uv2;
varying vec3 position;
attribute vec4 a_norm;
varying vec4 v_norm;
void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	position = (model*posL).xyz;
	gl_Position = u_rot*posL;
	v_norm = a_norm;
	v_color = a_color;
	v_uv = a_uv;
	v_uv2 = a_uv2;
}
   