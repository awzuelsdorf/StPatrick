#include <CImg.h>
#include <cstdlib>
using namespace cimg_library;

#define min(x, y) (x) < (y) ? (x) : (y)

void irishify(const CImg<unsigned char> &inputImage, const char *outputFileName) {
    CImg<unsigned char> outputImage(inputImage.width(), inputImage.height(),
                                    inputImage.depth(), 3);

    size_t x = 0, y = 0, z = 0;
    size_t widthOfImage = inputImage.width();
    size_t heightOfImage = inputImage.height();
    size_t depthOfImage = inputImage.depth();

    for (; x < widthOfImage / 3; x += 1) {
        for (y = 0; y < heightOfImage; y += 1) {
            for (z = 0; z < depthOfImage; z += 1) {
                outputImage(x, y, z, 0) = (char)0;
                outputImage(x, y, z, 1) = min(inputImage(x, y, z, 1) + 100, 255);
                outputImage(x, y, z, 2) = (char)0;
            }
        }
    }

    for (; x < 2 * widthOfImage / 3; x += 1) {
        for (y = 0; y < heightOfImage; y += 1) {
            for (z = 0; z < depthOfImage; z += 1) {
                outputImage(x, y, z, 0) = min(inputImage(x, y, z, 0) + 100, 255);
                outputImage(x, y, z, 1) = min(inputImage(x, y, z, 1) + 100, 255);
                outputImage(x, y, z, 2) = min(inputImage(x, y, z, 2) + 100, 255);
            }
        }
    }

    for (; x < widthOfImage; x += 1) {
        for (y = 0; y < heightOfImage; y += 1) {
            for (z = 0; z < depthOfImage; z += 1) {
                outputImage(x, y, z, 0) = (char)255;
                outputImage(x, y, z, 1) = inputImage(x, y, z, 1);
                outputImage(x, y, z, 2) = (char)0;
            }
        }
    }

    outputImage.save(outputFileName);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <original profile picture> <irish-ified profile picture>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    try {
        CImg<unsigned char> inputImage(argv[1]);
        irishify(inputImage, argv[2]);
    } catch (CImgIOException &ex) {
        fprintf(stderr, "Failed to open \"%s\". Irish-ified profile picture not created :(\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

