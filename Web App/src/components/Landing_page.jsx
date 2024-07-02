import React from 'react';
import './Landing_page.css';
import Sign_in from './Sign_in';
import { useLocation, Outlet, Link } from "react-router-dom";

const Landing_page = ({ children }) => {
  return (
    <div className="landing-page">
      <header className="header">
        <div className="logo"><img src="./src/img/lgo.png" alt="img" className='logoo' style={{width: 40, height: 40, borderRadius: 400/ 2}} /></div>
        <nav className="nav">
          <a href="#home">Home</a>
          <a href="#about">About us</a>
          
        </nav>
      </header>

      <section className="hero" id='#home'>
        <div className="hero-content">
          <h1>VIOS</h1><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br />
          {children}
        </div>
        <section className="about-us" id="about">
        <h2>About Us</h2>
        <p>We are a group of students from impact school who have had an idea placed at the convinience of blind people. We as students have decided to be their eyes and make life much easier for them by reducing their dependance on other people . Our aim is to is to make it easier for blind people to manoeuver their environment. This will allow all visually impaired people -no matter the cause- have a much safer journey  </p>
      </section>
      </section>
      <br />
      <section className="services" id="services">
        <h2>Explore What We Offer</h2>
        <div className="services-list">
          <div className="service-item">Pulse rate monitoring system</div>
          <div className="service-item">Ability to make calls using voice commands</div>
          <div className="service-item">Receive calls</div>
          <div className="service-item">A fully functional webapp that displays your contacts and a pulse rate graph</div>
        </div>
      </section>
      <footer className="footer">
        <nav className="footer-nav">
          <a href="#privacy">Privacy Policy</a>
          <a href="#terms">Terms & Conditions</a>
          <a href="#contact">Contact Us</a>
        </nav>
      </footer>
    </div>
  );
}

export default Landing_page;
