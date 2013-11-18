uniform sampler2D tex0;


void main(void)
{

   vec4 Color;
   Color.a = 1.0f;
   Color.rgb = 0.5f;
   Color -= texture2D( tex0, gl_TexCoord[0].st-0.001)*2.0f;
   Color += texture2D( tex0, gl_TexCoord[0].st+0.001)*2.0f;
   Color.rgb = (Color.r+Color.g+Color.b)/3.0f;
   gl_FragColor=Color;
}