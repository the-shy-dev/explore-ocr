import openai
from openai import OpenAI
import os
from dotenv import load_dotenv
import time

# Load environment variables from the .env file
load_dotenv()

# Get the OpenAI API key from the environment variable
api_key = os.getenv("OPENAI_API_KEY")

client = OpenAI()
# Set the API key for the OpenAI library
openai.api_key = api_key

# Function to get response from ChatGPT
def get_chat_response(user_message):
    try:
        response = client.chat.completions.create(model="gpt-3.5-turbo",
        messages=[
                {"role": "system", "content": "You are a helpful assistant."},
                {"role": "user", "content": user_message}
            ])
        return response.choices[0].message.content
    except openai.RateLimitError as e:
        print("Rate limit exceeded, waiting for 60 seconds")
        time.sleep(60)  # Wait for 60 seconds before retrying
        return get_chat_response(user_message)
    except openai.OpenAIError as e:
        print(f"An error occurred: {e}")
        return "Sorry, I couldn't process your request at the moment."

# Example usage for a group of students
student_questions = [
    "Explain the theory of relativity.",
    "How do you solve a quadratic equation?",
    "Why HTTP GET requests don't use request body?",
    "Can you tell me a fun fact about space?",
    "Tell me a dad joke"
]

# Process each student's question
for idx, question in enumerate(student_questions):
    print(f"Student {idx + 1}: {question}")
    response = get_chat_response(question)
    print(f"ChatGPT: {response}\n")

# Simulate interactive session
while True:
    user_input = input("Enter a question (or type 'exit' to end): ")
    if user_input.lower() == 'exit':
        break
    response = get_chat_response(user_input)
    print(f"ChatGPT: {response}\n")
