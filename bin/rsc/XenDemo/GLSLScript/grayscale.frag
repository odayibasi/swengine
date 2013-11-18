uniform sampler2D tex0;

void main(void)
{

     vec4 texC=vec4(texture2D(tex0, gl_TexCoord[0].st));
     vec4 color=(texC.r+texC.g+texC.b)/3.0;
     color.a=1.0; 	
     gl_FragColor = color;  
}