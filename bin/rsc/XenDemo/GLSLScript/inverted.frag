uniform sampler2D tex0;

void main(void)
{

     vec4 color=1-vec4(texture2D(tex0, gl_TexCoord[0].st));
     color.a=1.0; 	
     gl_FragColor = color;  
}