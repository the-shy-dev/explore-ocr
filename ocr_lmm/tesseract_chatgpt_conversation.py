import openai
from openai import OpenAI
import os
from dotenv import load_dotenv
import time
import pytesseract
from PIL import Image
import sys

# Load environment variables from the .env file
load_dotenv()

# Get the OpenAI API key from the environment variable
api_key = os.getenv("OPENAI_API_KEY")

client = OpenAI()
# Set the API key for the OpenAI library
openai.api_key = api_key

# Function to get response from ChatGPT
def get_chat_response(conversation):
    try:
        response = client.chat.completions.create(
            model="gpt-3.5-turbo",
            messages=conversation
        )
        return response.choices[0].message.content
    except openai.RateLimitError as e:
        print("Rate limit exceeded, waiting for 60 seconds")
        time.sleep(60)  # Wait for 60 seconds before retrying
        return get_chat_response(conversation)
    except openai.OpenAIError as e:
        print(f"An error occurred: {e}")
        return "Sorry, I couldn't process your request at the moment."

# Function to extract text from an image using Tesseract OCR
def extract_text_from_image(image_path):
    try:
        image = Image.open(image_path)
        text = pytesseract.image_to_string(image)
        return text
    except Exception as e:
        print(f"Error extracting text from image: {e}")
        return None

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script_name.py path_to_image")
        sys.exit(1)

    image_path = sys.argv[1]

    # Initialize conversation history
    conversation = [
        {"role": "system", "content": "You are a helpful assistant."}
    ]

    # # Example usage for a group of students
    # student_questions = [
    #     "Explain the theory of relativity.",
    #     "How do you solve a quadratic equation?",
    #     "Why HTTP GET requests don't use request body?",
    #     "Can you tell me a fun fact about space?",
    #     "Tell me a dad joke"
    # ]

    # # Process each student's question
    # for idx, question in enumerate(student_questions):
    #     conversation.append({"role": "user", "content": question})
    #     response = get_chat_response(conversation)
    #     conversation.append({"role": "assistant", "content": response})
    #     print(f"Student {idx + 1}: {question}")
    #     print(f"ChatGPT: {response}\n")
    
    # Extract text from the image and use it as input
    extracted_text = extract_text_from_image(image_path)
    if extracted_text:
        conversation.append({"role": "user", "content": extracted_text})
        print(f"Extracted Text: {extracted_text}")
        response = get_chat_response(conversation)
        conversation.append({"role": "assistant", "content": response})
        print(f"ChatGPT: {response}\n")

    # Simulate interactive session
    while True:
        user_input = input("Enter a question (or type 'exit' to end): ")
        if user_input.lower() == 'exit':
            break
        conversation.append({"role": "user", "content": user_input})
        response = get_chat_response(conversation)
        conversation.append({"role": "assistant", "content": response})
        print(f"ChatGPT: {response}\n")
