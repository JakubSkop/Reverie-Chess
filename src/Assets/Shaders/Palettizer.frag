uniform sampler2D texture;
uniform vec4 tintColor1;


void main()
{
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    float brightness = pixel.r*0.2 + pixel.g*0.7 + pixel.b*0.1;
    float temp = 4*brightness*(brightness-1)+1;
    float temp2 = pow(2.0, -64.0*pow(brightness-0.64, 2.0));

    gl_FragColor = pixel*brightness*(1-temp2*0.6) + tintColor1*(1-temp) * 0.8 + tintColor1*temp2*0.8;

}