import React from 'react';
import { sharedClasses } from './sharedClasses';

interface ButtonProps {
  text: string;
}

const Button: React.FC<ButtonProps> = ({ text }) => {
  return <button className={sharedClasses.zincButton}>{text}</button>;
};

export default Button;