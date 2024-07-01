import React, { useEffect } from 'react';
import { useNavigate } from 'react-router-dom';

function RedirectComponent() {
  const navigate = useNavigate();

  useEffect(() => {
    setTimeout(() => {
      navigate('/home'); // Replace with your desired destination
    }, 100); // Redirect after 2 seconds (2000 milliseconds)
  }, [navigate]);

  return (
    <div>
    </div>
  );
}

export default RedirectComponent;
