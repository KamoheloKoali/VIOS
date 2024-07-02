import React from 'react';
import { Line } from 'react-chartjs-2';
import 'chart.js/auto';
// import fetchJSONData from '../extract';
// import data from './pulseData.json';
// import './SimpleLineGraph.css'; // Import the CSS file
import jsonData from "../pulseData.json";
console.log(jsonData.age);
const SimpleLineGraph = () => {
  const data = {
    labels: ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'],
    datasets: [
      {
        label: 'bpm',
        data: [80, 59, 87, 81, 56, 55, 40, 45, 70, 75, 90, 100],
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
          text: 'Month',
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
