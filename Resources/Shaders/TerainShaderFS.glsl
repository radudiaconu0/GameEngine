precision mediump float;
varying vec2 v_uv;
varying vec2 v_uv2;
uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform sampler2D u_texture3;
varying vec3 position;
uniform float big_radius;
uniform float little_radius;
uniform vec3 f_color;
uniform vec3 cam_pos;

void main()
{
	//gl_FragColor = vec4(v_color, 1.0);
	//vec4 color = texture2D(u_texture0, v_uv);
	// if (color.a < 0.1) 
	// 	discard;
	vec4 c_blend;
	c_blend = texture2D(u_texture0, v_uv2);
	vec4 c_rock;
	c_rock = texture2D(u_texture1, v_uv);
	vec4 c_grass;
	c_grass = texture2D(u_texture2, v_uv);
	vec4 c_dirt;
	c_dirt = texture2D(u_texture3, v_uv);
	vec4 c_final;
	float dist = distance(cam_pos, position);
	c_final = c_blend.x*c_rock + c_blend.y*c_grass+ c_blend.z*c_dirt;
	float alpha = clamp((dist-little_radius)/(big_radius-little_radius) , 0.0, 1.0);
	vec4 color = alpha*vec4(f_color,1.0) + (1.0-alpha)*c_final;
	c_final.a = 1.0;
	gl_FragColor = color;
}
