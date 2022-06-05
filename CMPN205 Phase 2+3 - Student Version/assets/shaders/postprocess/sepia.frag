#version 330

// The texture holding the scene pixels
uniform sampler2D tex;

// Read "assets/shaders/fullscreen.vert" to know what "tex_coord" holds;
in vec2 tex_coord;
out vec4 frag_color;

void main(){
    // To apply the grayscale effect, we compute the average of the red/blue/green channels
    // and set that average value to all the channels
    vec3 sepia = vec3(1.2, 1.0, 0.8);
    frag_color = texture(tex, tex_coord);
    float gray = dot(frag_color.rgb, vec3(1.0/3.0, 1.0/3.0, 1.0/3.0));
    frag_color.rgb = vec3(gray*sepia);



    // frag_color = texture(tex, tex_coord);
    // frag_color.r = (frag_color.r * 0.393) + (frag_color.g * 0.769) + (frag_color.b * 0.189);
    // frag_color.g = (frag_color.r * 0.349) + (frag_color.g * 0.686) + (frag_color.b * 0.168);
    // frag_color.b = (frag_color.r * 0.272) + (frag_color.g * 0.534) + (frag_color.b * 0.131);
    //float gray = dot(frag_color.rgb, vec3(1.0/3.0, 1.0/3.0, 1.0/3.0));
    //frag_color.rgb = vec3(gray);
}

