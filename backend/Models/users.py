from create_app_db import db
from datetime import datetime, timezone

class device_user(db.Model):
    """
        Table of people who use our device.
    """

    __tablename__ = "device_user"
    __table_args__ = {'extend_existing': True}

    user_id = db.Column(db.String(120), nullable=False, primary_key=True)
    first_name = db.Column(db.String(50), nullable=False)
    last_name = db.Column(db.String(50), nullable=False)
    email = db.Column(db.String(120), nullable=False)
    password = db.Column(db.String(120), nullable=False)
    device_id = db.Column(db.String(120), nullable=False)
    created_at = db.Column(db.DateTime, default=datetime.now(tz=timezone.utc))

    # Relationship to kith_and_kin
    kith_and_kin_contacts = db.relationship('KithAndKin', backref='device_user', lazy=True)

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
            "email": self.email,
            "userId": self.user_id,
            "deviceId": self.device_id,
            "contacts": [dict(contact) for contact in self.kith_and_kin_contacts],
            "createdAt": str(self.created_at)
        }

class kith_and_kin(db.Model):
    """
        Table of friends and family of people who use our device.
    """
    
    __tablename__ = "kith_and_kin"

    user_id = db.Column(db.String(120), nullable=False, primary_key=True)
    first_name = db.Column(db.String(50), nullable=False)
    last_name = db.Column(db.String(50), nullable=False)
    email = db.Column(db.String(120), nullable=False)
    password = db.Column(db.String(120), nullable=False)
    contacts_user_id = db.Column(db.String(120), db.ForeignKey("device_user.user_id"))
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
            "email": self.email,
            "userId": self.user_id,
            "contacts": self.contacts_user_id,
            "createdAt": str(self.created_at)
        }
