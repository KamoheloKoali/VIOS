import React from 'react';
import { sharedClasses } from './sharedClasses';

interface CardProps {
  title: string;
  content: string;
}

const Card: React.FC<CardProps> = ({ title, content }) => {
  return (
    <div className={sharedClasses.zincCard}>
      <h3 className="text-2xl md:text-3xl font-bold">{title}</h3>
      <p>{content}</p>
    </div>
  );
};

export default Card;