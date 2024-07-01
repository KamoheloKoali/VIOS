// pages/index.tsx
import React from 'react';
import Header from '../components/Header';
import Section from '../components/Section';
import Card from '../components/Card';
import Image from '../components/Image';
import Button from '../components/Button';
import Footer from '../components/Footer';
import { sharedClasses } from '../components/sharedClasses';

const ViosApp: React.FC = () => {
  return (
    <div className={`${sharedClasses.zincBg} ${sharedClasses.zincText}`}>
      <Header />
      <Section id="home">
        <h2 className="text-4xl md:text-5xl font-bold mb-4">Empowering the Visually Impaired</h2>
        <p className="text-lg md:text-xl mb-4">Navigate through different environments and access the internet with ease.</p>
        
      </Section>
      <Section id="stats" className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-4 gap-4 text-center">
        <Card title="10,000+" content="Users of our product" />
        <Card title="5,000+" content="Web app users" />
        <Card title="4.8/5" content="Product reviews" />
        <Card title="4.7/5" content="Web app reviews" />
      </Section>
      <Section id="about">
        <h2 className="text-3xl md:text-4xl font-bold mb-4">About Us</h2>
        <p className="text-lg md:text-xl mb-4">VIOS is dedicated to providing innovative solutions for the visually impaired, helping them navigate through different environments and access the internet with ease.</p>
      </Section>
      <Section id="services" className="bg-zinc-100 text-zinc-800">
        <h2 className="text-3xl md:text-4xl font-bold mb-4">Explore What We Offer</h2>
        <div className="grid grid-cols-1 md:grid-cols-3 gap-4">
          <div className="p-6 bg-zinc-100 text-zinc-800 rounded-lg shadow">
            <h3 className="text-xl md:text-2xl font-bold mb-2">Navigation Aid</h3>
            <p>Helping the visually impaired navigate through different environments.</p>
          </div>
          <div className="p-6 bg-zinc-100 text-zinc-800 rounded-lg shadow">
            <h3 className="text-xl md:text-2xl font-bold mb-2">Internet Access</h3>
            <p>Providing easy access to the internet for the visually impaired.</p>
          </div>
          <div className="p-6 bg-zinc-100 text-zinc-800 rounded-lg shadow">
            <h3 className="text-xl md:text-2xl font-bold mb-2">Communication App</h3>
            <p>Connecting visually impaired individuals with their companions through calls and messages.</p>
          </div>
        </div>
      </Section>
      <Footer />
    </div>
  );
};

export default ViosApp;
