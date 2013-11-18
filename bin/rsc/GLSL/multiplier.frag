uniform sampler2D Coin;

void main(void)
{

     vec4 color=vec4(texture2D(Coin, gl_TexCoord[0].st));
     color.rgb*=(1.0-gl_TexCoord[0].t);
     gl_FragColor = color;  
}