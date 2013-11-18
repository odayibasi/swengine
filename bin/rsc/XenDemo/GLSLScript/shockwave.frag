uniform sampler2D tex0;
uniform vec2  center;
uniform float mag;
uniform float width;


#define INNER      0.2

#define OUTER      0.1

#define IREL       0.5 //1-(INNER/OUTER)

#define INTENSITY  15.0


void main(void)
{
   vec4 col = 0.0;
   vec2 tex = gl_TexCoord[0].st;
   vec2 dif = tex - center;
   float d = length(dif) - width;
   if (d < OUTER && d > -INNER){      
     //float t = OUTER - abs(d) * (1.0 - ((d < 0.0) * IREL));
      float f=0.0;
      if(d<0.0){
         f=IREL;
      }
      float t=OUTER-abs(d)* (1.0-f);
      vec2 texCoord=tex - dif * t * mag;
      col = vec4(texture2D(tex0,texCoord.xy));
      col.a = t * INTENSITY;
   }else{
      col = vec4(texture2D(tex0,tex.xy));
   }
   gl_FragColor =col;
}