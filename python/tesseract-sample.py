import cv2
import pytesseract

# Path to Tesseract-OCR executable
pytesseract.pytesseract.tesseract_cmd = r'/usr/bin/tesseract'

# Load image
image_path = 'sample.png'
image = cv2.imread(image_path)

# Convert image to RGB (Tesseract expects RGB image)
image_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

# Use Tesseract to extract text
text_tesseract = pytesseract.image_to_string(image_rgb)
print("Tesseract OCR Output:")
print(text_tesseract)
