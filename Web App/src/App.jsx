import React from 'react';
import { BrowserRouter, Routes, Route,  } from "react-router-dom";
import './App.css'; 
import Home from './components/Home';
import AddContact from './components/AddContact';
import Contacts from './components/Contacts';
import NavBar from './components/NavBar';
import Profile from './components/profile';
import Landing_page from './components/Landing_page';


const App = () => {
  return (
    <>
    
    
    <BrowserRouter>
      <Routes>
        <Route path="/" element={<Landing_page />}>
          <Route index element={<Home />} />
          <Route path="/AddContact" element={<AddContact />} />
          <Route path="/Contacts" element={<Contacts />} />
          <Route path="/profile" element={<Profile />} />
        </Route>
      </Routes>
    </BrowserRouter>
    </>
  );


};

export default App;














































