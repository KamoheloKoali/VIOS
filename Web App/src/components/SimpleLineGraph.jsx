import React from 'react';
import { Line } from 'react-chartjs-2';
import 'chart.js/auto';  // Import the necessary chart.js module

const SimpleLineGraph = () => {
  const data = {
    labels: ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'],
    datasets: [
      {
        label: 'bpm',
        data: [70, 59, 80, 81, 56, 55, 40, 45, 70, 75, 90, 100],
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
          text: 'Value',
        },
      },
    },
  };

  return (
    <div className='graph'>
    <div style={styles.container}>
      <h2 style={styles.title}>Pulse Rate</h2>
      <div style={styles.chartContainer}>
        <Line data={data} options={options} />
      </div>
    </div>
    </div>
  );
};

const styles = {
  container: {
    width: '50%',
    height: '300px',
    display: 'flex',
    flexDirection: 'column',
    alignItems: 'center',
    justifyContent: 'center',
    backgroundColor: '#fff',
    padding: '20px',
    borderRadius: '10px',
    boxShadow: '0 0 10px rgba(0,0,0,0.1)',
  },
  title: {
    marginBottom: '20px',
    fontSize: '18px',
    fontWeight: 'bold',
  },
  chartContainer: {
    width: '100%',
    height: '100%',
  },
  
};

export default SimpleLineGraph;
