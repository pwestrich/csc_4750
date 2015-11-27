
void main(){

   gl_TexCoord[0] = gl_MultiTexCoord0;  //set TexCoord[0] to be the second set of texture coords (done in BasicObject.cpp)
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

}
