export default function fetchJSONData() {
    fetch('https://c224-154-126-223-249.ngrok-free.app/data')  // Replace with your API endpoint
  .then(response => {
    if (!response.ok) {
      throw new Error('Network response was not ok');
    }
    return response.json();
  })
  .then(data => {
    console.log(data);  // Log the JSON response data
    // You can process or use the 'data' object further here
  })
  .catch(error => {
    console.error('Error fetching data:', error);
  });

}