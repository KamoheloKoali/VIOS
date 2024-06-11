import SimpleLineGraph from "./SimpleLineGraph"
import Favourites from "./favourites"
import './Home.css';

const Home = () => {
  return (
    <>
      <br />
      <SimpleLineGraph />
      <div className="favourites">
      <Favourites />
      </div>
    </>
  )
}

export default Home
