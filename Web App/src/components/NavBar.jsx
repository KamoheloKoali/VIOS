import { useLocation, Outlet, Link } from "react-router-dom";
import { SignedIn, SignedOut, SignInButton, UserButton } from "@clerk/clerk-react";
import Sign_in from "./Sign_in";

const NavBar = () => {
  const location = useLocation();

  return (
    <>
    
      <header className="navbar">
        <div className="upper-nav">
          <div className="navbar-left">
            <h1 className="navbar-title">Eyes for the blind</h1>
          </div>
          <div className="navbar-right">
          <Sign_in />
            
          </div>
        </div>
        <nav className="navbar-center">
          <div className="right">
            <Link to="/">
              <button
                className={`nav-button home ${
                  location.pathname === "/" ? "active" : ""
                }`}
              >
                Home
              </button>
            </Link>
            <Link to="/Contacts">
              <button
                className={`nav-button contact ${
                  location.pathname === "/Contacts" ? "active" : ""
                }`}
              >
                Contacts
              </button>
            </Link>
          </div>
          <div className="left">
            <button className="nav-button add-contact">
              <Link to="/AddContact">+ add contact</Link>
            </button>
          </div>
        </nav>
      </header>
      <Outlet />
    </>
  );
};

export default NavBar;
