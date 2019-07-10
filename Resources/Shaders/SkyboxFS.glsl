precision mediump float;
uniform samplerCube u_texture0;
varying vec3 v_coord;
void main()
{

	gl_FragColor=textureCube(u_texture0, v_coord);
	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
