#include <iostream>
#include "../include/CImg.h"

int main() {
    // Create a black image with dimensions 800x600 and 3 color channels (RGB)
    cimg_library::CImg<unsigned char> image(800, 600, 1, 3, 0);

    // Create a display window for the image
    cimg_library::CImgDisplay display(image, "Black Window");

    // Wait until the window is closed by the user
    while (!display.is_closed()) {
        // Display the image in the window
        display.display(image);
        // Handle any user interactions/events
        display.wait();
    }

    return 0;
}