from flask import Flask, request, jsonify, send_from_directory
import json
from werkzeug.utils import secure_filename
import os

from API.speech_to_text_endpoint import speech_to_text

app = Flask(__name__)

# Define your React app's build directory
react_folder = 'Web App'
directory = os.path.join(os.getcwd(), react_folder, 'dist', 'assets')

# Define allowed extensions
ALLOWED_IMAGE_EXTENSIONS = {'jpeg', 'jpg', 'png'}
ALLOWED_AUDIO_EXTENSIONS = {'mp3'}

def allowed_file(filename, allowed_extensions):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in allowed_extensions

@app.route('/<number>', methods=["GET"])
def index(number):
    data ={}
    data["heart_rate"] = number
    with open("heart_rate.json", "w", encoding="utf-8") as file:
        json.dump(file, data)

    # ''' Serve the main page '''
    # path = os.path.join(os.getcwd(), react_folder, 'dist')
    # return send_from_directory(directory=path, path='index.html')

@app.route('/data', methods=["GET"])
def data():
    with open("heart_rate.json", "r", encoding="utf-8") as file:
        return jsonify(json.load(file))

@app.route('/static/<folder>/<file>', methods=["GET"])
def serve_static(folder, file):
    path = os.path.join(folder, file)
    return send_from_directory(directory=directory, path=path, mimetype='application/javascript')


@app.route('/speech', methods=["POST"])
def speech():
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

if __name__ == '__main__':
    app.run(debug=True, threaded=True)
