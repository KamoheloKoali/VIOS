# `pip3 install assemblyai` (macOS)
# `pip install assemblyai` (Windows)

import assemblyai as aai
import os

aai.settings.api_key = os.getenv("ASSEMBLYAI_API_KEY")
transcriber = aai.Transcriber()

def convert(file_path):
    transcript = transcriber.transcribe(file_path)
    # transcript = transcriber.transcribe("./my-local-audio-file.wav")

    return transcript.text

#used whisper ai