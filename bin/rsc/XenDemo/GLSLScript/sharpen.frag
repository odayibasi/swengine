uniform sampler2D tex0;

void main(void){
    vec2 Tex=gl_TexCoord[0].st;
    vec4 Color;
    Color = vec4(texture2D(tex0,Tex.xy)); 
    Color -=vec4(texture2D(tex0,Tex.xy+0.001)); 
    Color +=vec4(texture2D(tex0,Tex.xy-0.001));
    gl_FragColor = Color;
}
