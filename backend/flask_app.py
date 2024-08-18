from flask import Flask, request, jsonify, send_from_directory
import json
from werkzeug.utils import secure_filename
import os
import datetime

from API.speech_to_text_endpoint import speech_to_text
from user_views import create_user, get_user, get_users, update_user, delete_user
from dotenv import load_dotenv
from create_app_db import db, init_db

load_dotenv(dotenv_path='.env.local')
db_user = os.getenv("DB_USER")
db_password = os.getenv("DB_PASS")
db_name = os.getenv("DB_NAME")

app = Flask(__name__)
app.config["SQLALCHEMY_DATABASE_URI"] = f"mysql+pymysql://{db_user}:{db_password}@localhost/{db_name}"
app.config["SQLALCHEMY_TRACK_MODIFICATIONS"] = False

init_db(app)

with app.app_context():
    db.create_all()


# Define your React app's build directory
react_folder = 'Web App'
directory = os.path.join(os.getcwd(), react_folder, 'dist', 'assets')

# Define allowed extensions
ALLOWED_IMAGE_EXTENSIONS = {'jpeg', 'jpg', 'png'}
ALLOWED_AUDIO_EXTENSIONS = {'mp3'}

def allowed_file(filename, allowed_extensions):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in allowed_extensions

@app.route('/', methods=["GET", "POST"])
def index():
    with open("heart_rate.json", "r", encoding="utf-8") as file:
        file_data = json.load(file)
    data = request.get_json();
    file_data["time_stamp"].append(datetime.datetime.now().strftime("%X"))
    file_data["heart_rate"].append(data["heart_rate"])
    with open("heart_rate.json", "w", encoding="utf-8") as file:
        json.dump(file_data, file)
    return "data added"

@app.route('/upload/<id>/<number>', methods=["POST", "GET"])
def upload(id, number):
    data ={}
    data[id] = number
    with open("heart_rate.json", "w", encoding="utf-8") as file:
        json.dump(data, file)
    return jsonify({"data entered": data})

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
    
# user routes

@app.route("/user", methods=["POST"])
def create():
    return create_user(request.get_json())

@app.route("/user/<user_type>/<id>", methods=["GET"])
def get(user_type, id):
    return get_user(user_type, id)
    
@app.route("/users/<user_type>", methods=["GET"])
def get_all():
    return get_users()
    
@app.route("/update_user/<user_type>/<id>", methods=["POST"])
def update(user_type, id):
    return update_user(user_type, id, request.get_json())

@app.route("/delete_user/<user_type>/<id>", methods=["POST"])
def delete(user_type, id):
    return delete_user(user_type, id)

if __name__ == '__main__':
    app.run(debug=True, threaded=True)
