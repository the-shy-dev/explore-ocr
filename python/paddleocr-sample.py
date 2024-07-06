from paddleocr import PaddleOCR, draw_ocr
import cv2
from PIL import Image

# Load image
image_path = '../sample.png'
image = cv2.imread(image_path)

# Initialize PaddleOCR
ocr = PaddleOCR(use_angle_cls=True, lang='en')

# Use PaddleOCR to extract text
result = ocr.ocr(image_path, cls=True)

# Print PaddleOCR result
print("PaddleOCR Output:")
for line in result:
    print(line)

# Draw results on the image
boxes = [elements[0] for elements in result[0]]
txts = [elements[1][0] for elements in result[0]]
scores = [elements[1][1] for elements in result[0]]

# Draw results on the image
im_show = draw_ocr(image, boxes, txts, scores, font_path='fonts/Roboto-Regular.ttf')
im_show = Image.fromarray(im_show)

# Save result
im_show.save('result_image.png')
