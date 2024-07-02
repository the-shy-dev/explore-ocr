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
  Boxa* boxes = api->GetComponentImages(tesseract::RIL_TEXTLINE, true, NULL, NULL);
  printf("Found %d textline image components.\n", boxes->n);
  for (int i = 0; i < boxes->n; i++) {
    BOX* box = boxaGetBox(boxes, i, L_CLONE);
    api->SetRectangle(box->x, box->y, box->w, box->h);
    char* ocrResult = api->GetUTF8Text();
    int conf = api->MeanTextConf();
    fprintf(stdout, "Box[%d]: x=%d, y=%d, w=%d, h=%d, confidence: %d, text: %s",
                    i, box->x, box->y, box->w, box->h, conf, ocrResult);
    boxDestroy(&box);
  }
  // Destroy used object and release memory
  api->End();
  delete api;
  delete [] outText;
  pixDestroy(&image);

  return 0;
}
