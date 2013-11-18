uniform sampler2D Coin;

void main(void)
{

     gl_TexCoord[0].t=gl_TexCoord[0].t+(sin(gl_TexCoord[0].x*100.0)*0.01);
     gl_TexCoord[0].s=gl_TexCoord[0].s+(cos(gl_TexCoord[0].y*100.0)*0.01);
     gl_FragColor = vec4(texture2D(Coin, gl_TexCoord[0].st)); 
}