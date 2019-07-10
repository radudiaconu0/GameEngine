precision mediump float;
varying  vec3 v_color;
uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
varying vec2 v_uv;
varying vec3 position;
uniform float u_Time;
uniform float u_DispMax;

void main()
{
	//gl_FragColor = vec4(v_color, 1.0);
	vec2 disp = texture2D(u_texture2, vec2(v_uv.x, v_uv.y + u_Time)).rg;
	vec2 offset = (disp * 2.0 - 1.0) * u_DispMax;
	vec2 v_uv_displaced = offset + v_uv;
	vec4 c_foc =  texture2D(u_texture1, v_uv_displaced);
	vec4 c_alpha = texture2D(u_texture0, v_uv);
	vec4 color;
	c_foc.a=c_alpha.r*c_foc.a;
	if (c_foc.a < 0.1) 
		discard;
	gl_FragColor = c_foc;
	//gl_FragColor = vec4(1.0, 1.0 , 0.0, 1.0);
}
