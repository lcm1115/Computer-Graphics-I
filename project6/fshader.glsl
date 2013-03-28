/*
** File:        fshader.glsl
** Author:      Liam Morris
** Description: Implements lighting portion of shading routine. Computes all
**              components of lighting and stores them in uniform variables.
*/
// Vectors computed in vshader.glsl
varying vec3 A;
varying vec3 C;
varying vec3 B;

// Components of lighting
uniform vec4 ambient;
uniform vec4 diffuse;
uniform vec4 specular;
uniform float specexp;


void main()
{
    // Normalize vectors
    vec3 B2 = normalize (B);
    vec3 A2 = normalize (A);

    // Compute terms in the illumination equation
    float Kdiffuse = dot(A2, B2);
    if (Kdiffuse < 0.0) {
      Kdiffuse = 0.0;
    }
    vec4 diff = Kdiffuse * diffuse;
    
    vec3 reflected = normalize(reflect(-A2, B2));
    float d = dot(reflected, C);
    if (d < 0.0) {
      d = 0.0;
    }

    // Compute specular component of lighting.
    float Kspecular = pow(d, specexp);
    vec4 spec = Kspecular * specular;
    if(dot(A, B) < 0.0) 
        spec = vec4(0.0, 0.0, 0.0, 1.0);

    // Get color.
    vec4 color = ambient + diff + spec; 
    color.a = 1.0;

    gl_FragColor = color;
}
