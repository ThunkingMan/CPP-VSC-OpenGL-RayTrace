#version 460 core
layout(local_size_x = 4, local_size_y = 4, local_size_z = 1) in;
layout(rgba32f, binding = 0) uniform image2D img_output;

void main() {
    vec4 pixel = vec4(0.5, 0.5, 0.5, 1.0); // base pixel colour for image
    ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy); // get index in global work group i.e x,y position
    if (pixel_coords.x < 100) {
        pixel.x += 0.25;
    }
    if (pixel_coords.y < 100) {
        pixel.y += 0.25;    
    }
    ivec2 centre = ivec2(512, 512);
    ivec2 test = abs(pixel_coords - centre);
    float v_length = length(test);
    if (v_length < 50)
    {
        pixel = vec4(0.0, 1.0, 0.0, 1.0);
    }
    imageStore(img_output, pixel_coords, pixel); // output to a specific pixel in the image
}