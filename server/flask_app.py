from flask import Flask, request, jsonify
from werkzeug.utils import secure_filename
import os
from API.speech_to_text_endpoint import speech_to_text
from API.image_read_endpoint import read_image
from API.object_detection_endpoint import object_detection

app = Flask(__name__)

# Define allowed extensions
ALLOWED_IMAGE_EXTENSIONS = {'jpeg', 'jpg', 'png'}
ALLOWED_AUDIO_EXTENSIONS = {'mp3'}

def allowed_file(filename, allowed_extensions):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in allowed_extensions

@app.route('/')
def home():
    return "Welcome to VIOS"

@app.route('/speech', methods=["POST"])
def tts():
    if 'file' not in request.files:
        return jsonify({"error": "No file part in the request"}), 400
    file = request.files['file']
    if file and allowed_file(file.filename, ALLOWED_AUDIO_EXTENSIONS):
        filename = secure_filename(file.filename)
        filepath = os.path.join("/tmp", filename)
        file.save(filepath)
        result = speech_to_text(filepath)
        return jsonify(result)
    else:
        return jsonify({"error": "Invalid file type"}), 400

@app.route('/obj_detect', methods=["POST"])
def detect_obj():
    if 'file' not in request.files:
        return jsonify({"error": "No file part in the request"}), 400
    file = request.files['file']
    if file and allowed_file(file.filename, ALLOWED_IMAGE_EXTENSIONS):
        filename = secure_filename(file.filename)
        filepath = os.path.join("/tmp", filename)
        file.save(filepath)
        result = object_detection(filepath)
        return jsonify(result)
    else:
        return jsonify({"error": "Invalid file type"}), 400

@app.route('/image_read', methods=["POST"])
def image_read():
    if 'file' not in request.files:
        return jsonify({"error": "No file part in the request"}), 400
    file = request.files['file']
    if file and allowed_file(file.filename, ALLOWED_IMAGE_EXTENSIONS):
        filename = secure_filename(file.filename)
        filepath = os.path.join("/tmp", filename)
        file.save(filepath)
        result = read_image(filepath)
        return jsonify(result)
    else:
        return jsonify({"error": "Invalid file type"}), 400

@app.route('/text', methods=["POST"])
def handle_text():
    if not request.is_json:
        return jsonify({"error": "Request must be JSON"}), 400
    data = request.get_json()
    # Process the JSON data as needed
    # Example response:
    return jsonify({"received_data": data}), 200

if __name__ == "__main__":
    app.run()
