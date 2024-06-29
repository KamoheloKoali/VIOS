import React from 'react';
import { sharedClasses } from './sharedClasses';

const Footer: React.FC = () => {
  return (
    <footer className={`${sharedClasses.zincBg} ${sharedClasses.zincText} p-4 text-center`}>
      <p>&copy; 2023 VIOS. All rights reserved.</p>
    </footer>
  );
};

export default Footer;