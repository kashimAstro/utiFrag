varying vec3  normal; 

void main(){
        vec3 N = normalize(normal); 
        gl_FragColor = vec4((N + vec3(1., 1., 1.)) / 2.0,1.0);
}
