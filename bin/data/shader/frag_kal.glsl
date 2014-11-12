uniform sampler2D tex;
uniform float time;
uniform vec2 resol;

varying vec3 e;
varying vec3 n;

void main() {

    vec3 rr = reflect( e, n );
    rr = e - 2. * dot( n, e ) * n;
    float m = 2. * sqrt( pow( rr.x, 2. ) + pow( rr.y, 2. ) + pow( rr.z + 1., 2. ) );
    vec2 uv = rr.xy / m + .5;

    float t = .001 * time + .3;
    mat2 r  = mat2(cos(t),sin(t),-sin(t),cos(t));
    vec4 p  = abs(4.-8.*gl_FragCoord.xyxz / resol.x) ;
    vec4 c  = p*.1;
    p.yx   *=r;
    p.yx   *=uv;
    
    for (float d=.2;d<2.;d+=.2) {
	p -= .5*d;
	for (int i=0;i<60;i++) 
            p.xy=r*(p.xy+sign(p.yx)*vec2(-.1,2.6));
	c += .03*p;
    }
    gl_FragColor =c;
}
