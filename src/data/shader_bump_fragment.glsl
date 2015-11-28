
varying vec3 g_lightVec;
varying vec3 g_eyeVec;

uniform sampler2D colorMap;
uniform sampler2D normalMap;

void main (void){
  
  float distSqr = dot(g_lightVec, g_lightVec);
  vec3 lVec = g_lightVec * inversesqrt(distSqr);

  vec3 vVec = normalize(g_eyeVec);
  
  vec4 base = texture2D(colorMap, gl_TexCoord[0].st);
  
  vec3 bump = normalize(texture2D(normalMap, gl_TexCoord[0].st).xyz * 2.0 - 1.0);

  vec4 vAmbient = gl_LightSource[0].ambient * gl_FrontMaterial.ambient;

  float diffuse = max(dot(lVec, bump), 0.0);
  
  vec4 vDiffuse = gl_LightSource[0].diffuse * gl_FrontMaterial.diffuse * diffuse;  

  float specular = pow(clamp(dot(reflect(-lVec, bump), vVec), 0.0, 1.0), gl_FrontMaterial.shininess);
  
  vec4 vSpecular = gl_LightSource[0].specular * gl_FrontMaterial.specular * specular;  
  
  gl_FragColor = ( vAmbient * base + vDiffuse * base + vSpecular);

}
