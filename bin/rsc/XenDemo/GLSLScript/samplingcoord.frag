uniform sampler2D tex0;

void main(void)
{

     gl_TexCoord[0].t=gl_TexCoord[0].t+(sin(gl_TexCoord[0].x*100.0)*0.01);
     gl_FragColor = vec4(texture2D(tex0, gl_TexCoord[0].st)); 
}