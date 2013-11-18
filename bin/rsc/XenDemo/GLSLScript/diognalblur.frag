uniform sampler2D tex0;

void main(void){
    vec2 Tex=gl_TexCoord[0].st;
    vec4 Color;
    Color = vec4(texture2D(tex0,Tex.xy)); 
    Color +=vec4(texture2D(tex0,Tex.xy+0.001)); 
    Color +=vec4(texture2D(tex0,Tex.xy+0.002));
    Color +=vec4(texture2D(tex0,Tex.xy+0.003));
    Color +=vec4(texture2D(tex0,Tex.xy+0.004));
    Color +=vec4(texture2D(tex0,Tex.xy+0.005));
    Color +=vec4(texture2D(tex0,Tex.xy+0.006));
    Color +=vec4(texture2D(tex0,Tex.xy+0.007));
    Color = Color / 8;
    gl_FragColor = Color;
}
