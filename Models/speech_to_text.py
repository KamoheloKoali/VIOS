# `pip3 install assemblyai` (macOS)
# `pip install assemblyai` (Windows)

import assemblyai as aai

aai.settings.api_key = "ba975d68690a46e3a497c548d9d02856"
transcriber = aai.Transcriber()

def convert(file_path):
    transcript = transcriber.transcribe(file_path)
    # transcript = transcriber.transcribe("./my-local-audio-file.wav")

    return transcript.text

#used whisper ai