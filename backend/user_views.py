from data_management.read_db import get_data_from_db as read_db
from Models.users import device_user, kith_and_kin
import uuid


def create_user(data):
    if data["userType"] == "deviceUser":
        for device_user in read_db("device_user"):
            if device_user.email == data["email"]:
                return "User already exists", 200
        user = device_user(
                first_name=data["firstName"],
                last_name=data["lastName"],
                age=data["age"],
                email=data["email"],
                user_id=uuid.uuid4().hex, 
                device_id=data["deviceId"]
                                )
        user.save_to_db()
        return user.to_dict(), 201
                
    elif data["userType"] == "kithAndKin":
        for user in read_db("kithAndKin"):
            if user.email == data["email"]:
                return "User already exists", 200
        user = device_user(
                first_name=data["firstName"],
                last_name=data["lastName"],
                age=data["age"],
                email=data["email"],
                user_id=uuid.uuid4().hex,
                                )
        user.save_to_db()
        return user.to_dict(), 201
                
def get_user(user_type, id):
    return read_db(user_type, id).to_dict(), 200


def get_users(user_type):
    list_of_users = read_db(user_type)
    users = []
    
    for user in list_of_users:
        users.append(user.to_dict())
        
    return users, 200


def update_user(user_type, id, data):
    user = read_db(user_type, id)
    user.first_name = data["firstName"]
    user.last_name = data["lastName"]
    user.age = data["age"]
    user.contacts = data["contacts"]
    
    return user.to_dict(), 201


def delete_user(user_type, id):
    user = read_db(user_type, id)
    
    user.delete_from_db()
    
    return "user deleted successfully", 201


