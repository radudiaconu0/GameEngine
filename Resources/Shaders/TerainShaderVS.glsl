attribute vec3 a_posL;
uniform vec3 height;
uniform mat4 u_rot;
attribute vec2 a_uv;
attribute vec2 a_uv2;
varying vec2 v_uv;
varying vec2 v_uv2;
uniform sampler2D u_texture0;
uniform mat4 model;
varying vec3 position;
void main()
{
    vec4 c_blend;
    c_blend = texture2D(u_texture0, a_uv2);
    vec4 posL = vec4(a_posL, 1.0);
	position = (model*posL).xyz;
    posL.y += c_blend.r*height.r+c_blend.g*height.g+c_blend.b*height.b;
    gl_Position = u_rot*posL;
    v_uv = a_uv;
    v_uv2 = a_uv2;
}
   