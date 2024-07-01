import { SignedIn, SignedOut, SignInButton, UserButton } from "@clerk/clerk-react";
import './Sign_in.css';
import Home from "./Home";

export default function Sign_in() {
  return (
    <header>
      <SignedOut>
        <SignInButton>
          <button className="btnn">Login</button>
        </SignInButton>
      </SignedOut>
      <SignedIn>
        <Home/>
        <UserButton />
      </SignedIn>
    </header>
  )
}
