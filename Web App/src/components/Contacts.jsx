import React from 'react';
import './Contacts.css';

const contacts = [
  { name: 'Tumelo', },
  { name: 'Tlotliso', },
  { name: 'Thato', },
  { name: 'Mohale', },
  { name: 'Kamohelo', },
  { name: 'Karabo', },
  { name: 'Reitumetse', },
  { name: 'Thebe', },
  { name: 'Sedimo', },
  { name: 'Bakuena', },
  { name: 'Leseli', },
  { name: 'Leseli', },
  { name: 'Leseli', },
  { name: 'Leseli', },
  { name: 'Leseli', },
  { name: 'Leseli', },
  { name: 'Leseli', },
  { name: 'Leseli', },
];

const Contacts = () => {
  return (
    <div className="contact-list">
      {contacts.map((contact, index) => (
        <div key={index} className="contact-item">
          <span className="contact-name">{contact.name}</span>
          <button className="call-button">Call</button>
          <button className="details-button">Details</button>
          <span className="contact-date">{contact.date}</span>
          <button className="menu-button">...</button>
        </div>
      ))}
    </div>
  );
};

export default Contacts;

