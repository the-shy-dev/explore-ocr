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
  char *outText;
  tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
  // Initialize tesseract-ocr with English, without specifying tessdata path
  if (api->Init(NULL, "eng")) {
      fprintf(stderr, "Could not initialize tesseract.\n");
      exit(1);
  }
  Pix *image = pixRead(imagePath);
  api->SetImage(image);
  api->Recognize(0);
  tesseract::ResultIterator* ri = api->GetIterator();
  tesseract::PageIteratorLevel level = tesseract::RIL_WORD;
  if (ri != 0) {
    do {
      const char* word = ri->GetUTF8Text(level);
      float conf = ri->Confidence(level);
      int x1, y1, x2, y2;
      ri->BoundingBox(level, &x1, &y1, &x2, &y2);
      printf("word: '%s';  \tconf: %.2f; BoundingBox: %d,%d,%d,%d;\n",
               word, conf, x1, y1, x2, y2);
      delete[] word;
    } while (ri->Next(level));
  }
  // Destroy used object and release memory
  api->End();
  delete api;
  delete [] outText;
  pixDestroy(&image);
  return 0;
}