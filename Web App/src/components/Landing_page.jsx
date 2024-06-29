import React from 'react';
import './Landing_page.css';
import Sign_in from './Sign_in';
import { useLocation, Outlet, Link } from "react-router-dom";

const Landing_page = () => {
  return (
    <div className="landing-page">
      <header className="header">
        <div className="logo"><img src="./src/img/lgo.png" alt="img" className='logoo' style={{width: 40, height: 40, borderRadius: 400/ 2}} /></div>
        <nav className="nav">
          <a href="#home">Home</a>
          <a href="#about">About</a>
          <a href="#form">Sign up</a>
          
        </nav>
      </header>

      <section className="hero" id='#home'>
        <div className="hero-content">
          <h1>VIOS</h1><br /><br /><br /><br /><br />
          <Sign_in />
        </div>
        
      </section>

      <section className="about-us" id="about">
        <h2>About Us</h2>
        <p>We are a group of students from imapct school who have had an idea placed at the convinience of blind people. We as students have decided to be their eyes and make life much more reducing their need for depending on people . Our aim is to is to make it easier for blind people to manoeuver their environment. This will allow all visually impaired people -no matter the cause- have a much safer approach to  </p>
        <div className="about-video">
          <img src="./src/img/images.jpg" alt="About Us" className='theimage'/>
        </div>
      </section>

      <section className="services" id="services">
        <h2>Explore What We Offer</h2>
        <div className="services-list">
          <div className="service-item">Pulse rate monitoring system</div>
          <div className="service-item">Ability to make calls using voice commands</div>
          <div className="service-item">Receive calls</div>
          <div className="service-item">A fully functional webapp that displays your contacts and a pulse rate graph</div>
        </div>
      </section>
      <section>
      <form class="form" id='form' method="#" action="#">
    		<div>
    		<input type="text" placeholder="Name" name="Name"/>
    		<input type="text" placeholder="Surname" name="Surname"/>
    		<input type="number" placeholder="Phone Number" name="Phone Number"/>
    		<select>
    			<option value="male">male</option>
    			<option value="female">female</option>
    		</select>
    		<input type="email" placeholder="email address" name="email address"/>
    		<input type="password" name="password" placeholder="password"/>
    		<button type="submit" className='bttn'>submit</button>
    		</div>
    		

    	</form>
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
