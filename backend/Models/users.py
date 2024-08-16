"""
    This module contains the tables for users in the database
"""
from flask_app import db
from datetime import datetime, timezone

class device_user(db.Model):
    """
        table of people who use our device
    """

    __tablename__ = "device_user"
    __table_args__ = {'extend_existing': True}

    first_name = db.Column(db.String(50), nullable=False)
    last_name = db.Column(db.String(50), nullable=False)
    age = db.Column(db.Integer, nullable=False)
    email = db.Column(db.String(120), nullable=False)
    user_id = db.Column(db.String(120), nullable=False, primary_key=True)
    device_id = db.Column(db.String(120), nullable=False)
    contacts = db.Column(db.Integer, db.ForeignKey("kith_and_kin.user_id"))
    created_at = db.Column(db.DateTime, default=datetime.now(tz=timezone.utc))
    
    def save_to_db(self):
        """Saves the user information to the database."""
        db.session.add(self)
        db.session.commit()
    
    def delete_from_db(self):
        """Deletes the user information from the database."""
        db.session.delete(self)
        db.session.commit()
        
    def to_dict(self):
        return {
            "firstName": self.first_name,
            "lastName": self.last_name,
            "age": self.age,
            "email": self.email,
            "userId": self.user_id,
            "deviceId": self.device_id,
            "contacts": [dict(contact) for contact in self.contacts],
            "createdAt": str(self.created_at)
        }

class kith_and_kin(db.Model):
    """
        table of friends and family of people who use our device
    """
    
    __tablename__ = "kith_and_kin"

    first_name = db.Column(db.String(50), nullable=False)
    last_name = db.Column(db.String(50), nullable=False)
    age = db.Column(db.Integer, nullable=False)
    email = db.Column(db.String(120), nullable=False)
    user_id = db.Column(db.String(120), nullable=False, primary_key=True)
    contacts = db.Column(db.Integer, db.ForeignKey("device_user.user_id"))
    created_at = db.Column(db.DateTime, default=datetime.now(tz=timezone.utc))
    
    def save_to_db(self):
        """Saves the user information to the database."""
        db.session.add(self)
        db.session.commit()
    
    def delete_from_db(self):
        """Deletes the user information from the database."""
        db.session.delete(self)
        db.session.commit()
        
    def to_dict(self):
        return {
            "firstName": self.first_name,
            "lastName": self.last_name,
            "age": self.age,
            "email": self.email,
            "userId": self.user_id,
            "contacts": [dict(contact) for contact in self.contacts],
            "createdAt": str(self.created_at)
        }