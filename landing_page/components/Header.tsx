// components/Header.tsx
import React from 'react';
import Link from 'next/link';
import { sharedClasses } from './sharedClasses';

const Header: React.FC = () => {
  return (
    <header className={`${sharedClasses.zincBg} ${sharedClasses.zincText} p-4 flex justify-center border`}>
      <h1 className="text-3xl md:text-4xl font-bold">Welcome to VIOS</h1>
      {/* <nav>
        <ul className="flex space-x-4">
          <li><Link href="#home" className={sharedClasses.zincHover}>Home</Link></li>
          <li><Link href="#services" className={sharedClasses.zincHover}>Services</Link></li>
          <li><Link href="#about" className={sharedClasses.zincHover}>About</Link></li>
          <li><Link href="#contact" className={sharedClasses.zincHover}>Contact</Link></li>
        </ul>
      </nav> */}
    </header>
  );
};

export default Header;
