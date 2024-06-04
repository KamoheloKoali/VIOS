import { Outlet, Link } from "react-router-dom";

const NavBar = () => {
  return (
    <>
      <header className="navbar">
        <div className="navbar-left">
          <h1 className="navbar-title">Eyes for the blind</h1>
        </div>
        <nav className="navbar-center">
          <button className="nav-button active">
            <Link to="/">Home</Link>
          </button>
          <button className="nav-button">
            <Link to="/Contacts">Contacts</Link>
          </button>
          <button className="nav-button add-contact">
            <Link to="/AddContact">+ add contact</Link>
          </button>
        </nav>
        <div className="navbar-right">
          <a href="#"><img src="./src/moon.jpg" alt="Profile" className="profile-image" /></a>
        </div>
      </header>
      <Outlet />
    </>
  );
};

export default NavBar;