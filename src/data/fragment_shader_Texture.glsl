uniform sampler2D image_1;
uniform sampler2D image_2;

void main(){

   vec2 st = gl_TexCoord[0].st;
   vec3 color_1 = texture2D(image_1, st).rgb;
   vec3 color_2 = texture2D(image_2, st).rgb;
   vec3 color_diff = color_1 - color_2;
   gl_FragColor = vec4(color_diff, 1.0);
   
}
