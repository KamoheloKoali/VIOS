// App.js
import React from 'react';
import { BrowserRouter, Routes, Route } from "react-router-dom";
import './App.css'; 
import Home from './components/Home';
import AddContact from './components/AddContact';
import Sign_in from './components/Sign_in';
import Contacts from './components/Contacts';
import NavBar from './components/NavBar';
import fetchJSONData from './extract';
import Profile from './components/profile';
import Landing_page from './components/Landing_page';
import { SignIn, SignUp } from '@clerk/clerk-react';

const App = () => {
  return (
    <>
      <BrowserRouter>
        <Routes>
          <Route path="/" element={<Sign_in />}>
            <Route path="/home" element={<Home />} />
            {/* <Route path="/home" element={<NavBar />} /> */}
            <Route path="/AddContact" element={<AddContact />} />
            <Route path="/Contacts" element={<Contacts />} />
            <Route path="/profile" element={<Profile />} />
            {/* <Route path="/signin" element={<Sign_in />} /> Add the sign-in route */}
            {/* <Route path="/signup" element={<SignUp />} /> Add the sign-up route */}
          </Route>
        </Routes>
      </BrowserRouter>
    </>
  );
};

export default App;
