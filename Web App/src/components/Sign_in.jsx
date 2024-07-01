// Sign_in.js
import { SignedIn, SignedOut, SignInButton, UserButton } from "@clerk/clerk-react";
import React, { useEffect } from 'react';
import Landing_page from "./Landing_page";
import { useLocation, Outlet, Link } from "react-router-dom";
import NavBar from "./NavBar";
import { useNavigate } from 'react-router-dom'
import './Sign_in.css';
import Profile from "./profile";
import '../App.css'; 
import Home from "./Home";

let reloadCount = sessionStorage.getItem('reloadCount');
  reloadCount = reloadCount ? parseInt(reloadCount) : 0; // Convert to number or default to 0

  if (reloadCount < 2) {
    reloadCount++; // Increment reloadCount
    sessionStorage.setItem('reloadCount', String(reloadCount)); // Store updated value

    window.location.reload(); // Reload the page
  } else {
    sessionStorage.removeItem('reloadCount'); // Remove reloadCount if limit reached
  }




export default function Sign_in() {
  
  return (
    <header>
      <SignedOut>
        <Landing_page>
          <SignInButton>
            <button className="btnn">Sign up</button>
          </SignInButton>
        </Landing_page>
      </SignedOut>
      <SignedIn>
        <NavBar>
          {location.pathname === "/profile" ? <UserButton /> : <Link to="/profile">
            <img src="./src/img/moon.jpg" alt="" className="profile-image" />
          </Link>}
        </NavBar>
      </SignedIn>
    </header>
  )
}
