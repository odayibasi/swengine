void main(void){
   gl_Position = ftransform();
   gl_TexCoord[0].xy = gl_MultiTexCoord0.xy;
}


