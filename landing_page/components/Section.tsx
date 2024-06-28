import React from 'react';
import { sharedClasses } from './sharedClasses';

interface SectionProps {
  id: string;
  className?: string;
  children: React.ReactNode;
}

const Section: React.FC<SectionProps> = ({ id, className = '', children }) => {
  return <section id={id} className={`${sharedClasses.zincBg} ${sharedClasses.zincText} p-8 ${className}`}>{children}</section>;
};

export default Section;