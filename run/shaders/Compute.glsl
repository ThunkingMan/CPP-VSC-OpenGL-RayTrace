#version 460 core
layout(local_size_x = 4, local_size_y = 4, local_size_z = 1) in;
layout(rgba32f, binding = 0) uniform image2D ImageOutput;
layout(std430, binding = 1) buffer InputData {
    uint  data[];
};

uniform ivec2 u_ImageCentre;
uniform vec3 u_Look;

void main() {
    vec4 Pixel = vec4(0.5, 0.5, 0.5, 1.0); // base pixel colour for image
    ivec2 PixelCoords = ivec2(gl_GlobalInvocationID.xy); // get index in global work group i.e x,y position
    
    //Axis
    if (PixelCoords.x == u_ImageCentre.x) {
        Pixel = vec4(0.25, 0.25, 0.25, 1.0);    
    }
    if (PixelCoords.y == u_ImageCentre.y) {
        Pixel = vec4(0.25, 0.25, 0.25, 1.0);   
    }
    uint ImageSize = u_ImageCentre.x + u_ImageCentre.y;
    uint CoordSum = PixelCoords.x + PixelCoords.y;
    if (CoordSum == ImageSize){
        Pixel = vec4(0.25, 0.25, 0.25, 1.0);    
    }

    //float TempYf = (u_Look.y * 50);
    //int TempYi = int(TempYf);
    //if (PixelCoords.y == TempYi) {
    //    Pixel = vec4(1.0, 0.0, 0.0, 1.0);
    //}
    
    
    //View Line
    int XView = u_ImageCentre.x + int(u_Look.x * 20);
    int YView = u_ImageCentre.y - int(u_Look.y * 20);
    if (PixelCoords.x == XView && PixelCoords.y == YView) {
        Pixel = vec4(1.0, 0.0, 0.0, 1.0);
    }

    //ivec2 test = abs(pixel_coords - centre);
    //uvec2 test = abs(pixel_coords - u_ImageCentre);
    //float v_length = length(test);
    //if (v_length < 50)
    //{
    //    pixel = vec4(0.0, 1.0, 0.0, 1.0);
    //}
    //if (pixel_coords.x < u_ImageCentre.x)
    //{
    //    if (pixel_coords.x == pixel_coords.y)
    //    {
    //        pixel = vec4(1.0, 0.0, 0.0, 1.0);
    //    }
    //}
    imageStore(ImageOutput, PixelCoords, Pixel); // output to a specific pixel in the image
}