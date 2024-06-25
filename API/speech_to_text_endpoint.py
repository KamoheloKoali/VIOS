"""convert audio to text for processing"""

from Models.speech_to_text import convert
from Handle_commands.main import analyse_text

def speech_to_text(file_path):
    text = convert(file_path)
    return analyse_text(text)