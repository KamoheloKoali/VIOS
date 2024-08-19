export default function NavBar() {
  return (
    <>
      <nav className="absolute top-5 left-5 flex items-center space-x-8">
        <span className="text-4xl font-inter font-light text-black">VIOS</span>
        <a href="#" className="text-xl font-inter text-black">
          Home
        </a>
        <a href="#" className="text-xl font-inter text-black">
          Dashboard
        </a>
        <a href="#" className="text-xl font-inter text-black">
          Profile
        </a>
        <a href="#" className="text-xl font-inter text-black">
          About Us
        </a>
        <a href="#" className="text-xl font-inter text-black">
          Contact Us
        </a>
      </nav>
    </>
  );
}
