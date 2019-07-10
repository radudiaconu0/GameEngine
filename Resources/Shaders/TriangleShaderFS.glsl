precision mediump float;
varying  vec3 v_color;
uniform sampler2D u_texture0;
uniform sampler2D u_disp;
varying vec2 v_uv;
varying vec3 position;
uniform float big_radius;
uniform float little_radius;
uniform vec3 f_color;
uniform vec3 cam_pos;
uniform float specPower0;
uniform float specPower1;
uniform float specPower2;
uniform float specPower3;
uniform float specPower4;
uniform vec3 direction0;
uniform vec3 direction1;
uniform vec3 direction2;
uniform vec3 direction3;
uniform vec3 direction4;
uniform vec3 specColor0;
uniform vec3 specColor1;
uniform vec3 specColor2;
uniform vec3 specColor3;
uniform vec3 specColor4;
uniform vec3 diffuseColor0;
uniform vec3 diffuseColor1;
uniform vec3 diffuseColor2;
uniform vec3 diffuseColor3;
uniform vec3 diffuseColor4;
uniform float ratio;
uniform vec3 c_amb;
varying vec4 v_norm;
void main()
{
	//gl_FragColor = vec4(v_color, 1.0);
	float dist = distance(cam_pos, position);
	vec4 c_object = texture2D(u_texture0, v_uv);

	if (c_object.a < 0.1) 
		discard;
	vec3 comp_amb = c_object.xyz * c_amb;
	vec4 N = vec4(normalize(v_norm.xyz), 0.0);
	vec4 L = vec4(normalize(direction0.xyz), 0.0);
	vec3 c_diff = c_object.xyz*diffuseColor0 *max(dot(N,-L), 0.0);	vec4 R = vec4(normalize(reflect(L,N).xyz), 0.0);
	vec4 E = vec4(normalize(position - cam_pos), 0.0);
	vec3 Cspec = specColor0 * pow(max(dot(R,E), 0.0), specPower0);
	vec3 c_final = 0.5*comp_amb + (1.0-0.5)*(c_diff+Cspec);
	
		
	float alpha = clamp((dist - little_radius) / (big_radius - little_radius), 0.0, 1.0);
	vec4 color = alpha * vec4(f_color, 1.0) + (1.0 - alpha) * vec4(c_final, c_object.a);
	gl_FragColor = color;
}
