uniform sampler2D Coin;
uniform float threshold=0.48;


void main(void)
{

   vec2 coord=gl_TexCoord[0].st;
   vec4 color=vec4(texture2D(Coin, coord));
   
   coord.s+=0.001;
   vec4 rightColor=vec4(texture2D(Coin, coord));
   
   coord.st+=0.001;
   vec4 bottomColor=vec4(texture2D(Coin, coord));
   
   vec4 dRightColor=sqrt(rightColor-color);
   vec4 dBottomColor=sqrt(bottomColor-color);
   
   float deltaRight=dRightColor.r+dRightColor.g+dRightColor.b;
   float deltaBottom=dBottomColor.r+dBottomColor.g+dBottomColor.b;
   
   if(deltaRight>threshold || deltaBottom>threshold){
      gl_FragColor = vec4(0.0,0.0,0.0,1.0); 
    }else{
     gl_FragColor = vec4(1.0);  
   }
}