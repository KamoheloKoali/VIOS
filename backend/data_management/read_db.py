from flask_app import db
from Models.users import device_user, kith_and_kin 

def get_data_from_db(table, id=None):
    table_obj = db.metadata.tables.get(table)
    if table_obj is None:
        raise ValueError(f"Table {table} not found in metadata")
    
    if id:
        if table == "device_user":
            return db.session.query(device_user).filter(device_user.user_id == id).first()
        elif table == "kith_and_kin":
            return db.session.query(kith_and_kin).filter(kith_and_kin.user_id == id).first()
        
    return db.session.query(table_obj).all()