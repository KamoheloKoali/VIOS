import { useLocation, Outlet, Link } from "react-router-dom";
import RedirectComponent from "./RedirectComponent";
import { SignedIn, SignedOut, SignInButton, UserButton } from "@clerk/clerk-react";
import Sign_in from "./Sign_in";

const NavBar = ({ children }) => {
  const location = useLocation();

  return (
    <>
      {location.pathname === "/" ? <RedirectComponent /> : ""}
      <header className="navbar">
        <div className="upper-nav">
          <div className="navbar-left">
            <h1 className="navbar-title">Eyes for the blind</h1>
          </div>
          <div className="navbar-right">
          <Link to="/profile">
            {children}
          </Link>
          </div>
        </div>
        <nav className="navbar-center">
          <div className="right">
            <Link to="/home">
              <button
                className={`nav-button home ${
                  location.pathname === "/home" ? "active" : ""
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
              <Link to="/AddContact"></Link>                               
            </button>
          </div>
        </nav>
      </header>
      <Outlet />
    </>
  );
};

export default NavBar;
