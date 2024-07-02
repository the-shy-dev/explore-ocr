#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <iostream>

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <image_path>\n";
        return 1;
    }

    char* imagePath = argv[1];
    char* outText;

    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init(NULL, "eng")) {
        std::cerr << "Could not initialize tesseract.\n";
        return 1;
    }

    // Open input image with leptonica library
    Pix* image = pixRead(imagePath);
    if (!image) {
        std::cerr << "Could not open input image: " << imagePath << "\n";
        return 1;
    }

    // Calculate the rectangle dimensions (90% of the image area)
    int width = pixGetWidth(image);
    int height = pixGetHeight(image);
    int rectWidth = width * 0.9;
    int rectHeight = height * 0.9;
    int rectLeft = (width - rectWidth) / 2;
    int rectTop = (height - rectHeight) / 2;

    api->SetImage(image);
    // Restrict recognition to a sub-rectangle of the image
    api->SetRectangle(rectLeft, rectTop, rectWidth, rectHeight);
    // Get OCR result
    outText = api->GetUTF8Text();
    std::cout << "OCR output:\n" << outText << "\n";

    // Destroy used object and release memory
    api->End();
    delete api;
    delete[] outText;
    pixDestroy(&image);

    return 0;
}
