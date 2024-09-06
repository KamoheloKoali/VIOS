# from PIL import Image
import pytesseract
from PIL import Image



# Use pytesseract to do OCR on the image
def read_text(image):
    text = pytesseract.image_to_string(image)
    
    with open("text_from_image.txt", "w", encoding="utf-8") as file:
        pass

    # Print the extracted text
    with open("text_from_image.txt", "a", encoding="utf-8") as file:
        file.write(text)


#used tessaract ocr
# Path to the image file
# image_path = './Screenshot.png'

# # Open the image file
# image = Image.open(image_path)

# read_text(image)