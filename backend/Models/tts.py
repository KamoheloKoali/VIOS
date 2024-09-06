from TTS.api import TTS

# Initialize TTS with a pre-trained model
# You can find the available models and their IDs here: https://github.com/coqui-ai/TTS#pretrained-models
tts = TTS(model_name="tts_models/en/ljspeech/tacotron2-DDC", progress_bar=True, gpu=False)


def text_to_speech(text):
    # Generate speech
    output_path = "output.wav"

    # Modify the model to use a different pre-trained model that may produce a voice similar to Siri
    # For example, you can try "tts_models/en/vctk/tacotron2-DCA" or "tts_models/en/libritts/tacotron2-DDC"
    tts.model_name = "tts_models/en/vctk/tacotron2-DCA"

    tts.tts_to_file(text=text, file_path=output_path)

    # Inform the user
    print(f"Generated speech saved to {output_path}")
text_to_speech("hello")