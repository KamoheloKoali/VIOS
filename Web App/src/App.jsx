import React from 'react';
import { BrowserRouter, Routes, Route } from "react-router-dom";
import './App.css'; 
import Home from './components/Home';
import AddContact from './components/AddContact';
import Contacts from './components/Contacts';
import NavBar from './components/NavBar';

const App = () => {
  return (
    <BrowserRouter>
      <Routes>
        <Route path="/" element={<NavBar />}>
          <Route index element={<Home />} />
          <Route path="/AddContact" element={<AddContact />} />
          <Route path="/Contacts" element={<Contacts />} />
        </Route>
      </Routes>
    </BrowserRouter>
  );
};

 

export default App;















































