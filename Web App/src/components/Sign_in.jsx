import { SignIn, SignedIn, SignedOut, SignInButton, UserButton } from "@clerk/clerk-react";

const Sign_in = () => {
  return (
    <div className="signin">  
      <SignIn />
    </div>
  )
}

export default Sign_in
