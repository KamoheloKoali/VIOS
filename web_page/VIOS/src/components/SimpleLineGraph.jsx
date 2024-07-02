import React from 'react';
import { Line } from 'react-chartjs-2';
import 'chart.js/auto';
// import fetchJSONData from '../extract';
// import data from './pulseData.json';
// import './SimpleLineGraph.css'; // Import the CSS file
import jsonData from "../../../../heart_rate.json";
import { delay } from 'framer-motion';

console.log(jsonData);


const SimpleLineGraph = () => {
  const data = {
    labels: jsonData.time_stamp,
    datasets: [
      {
        label: 'bpm',
        data: jsonData.heart_rate,
        fill: false,
        borderColor: '#007bff',
        tension: 0.1,
      },
    ],
  };




  const options = {
    responsive: true,
    maintainAspectRatio: false,
    scales: {
      x: {
        title: {
          display: true,
          text: 'Time',
        },
      },
      y: {
        title: {
          display: true,
          text: 'Value/bpm',
        },
      },
    },
  };

  return (
    <div className="graph">
      <div className="container">
        <h2 className="title">Pulse Rate</h2>
        <div className="chartContainer">
          <Line data={data} options={options} />
        </div>
      </div>
    </div>
  );
};

export default SimpleLineGraph;
