export default function Login() {
  return (
    <>
      <div className="relative w-full h-screen bg-gradient-to-r from-blue-400 via-purple-400 to-pink-400">
        <div className="row">
          <div className="col-md-12 items-center justify-center flex h-screen">
            <form className="border">

              <fieldset>
                <input type="text" id="name" name="first_name" placeholder="First Name" required/>
                <input type="text" id="name" name="last_name" placeholder="Last Name" required/>
                <input type="email" id="mail" name="user_email" placeholder="Email" required/>
                <input type="password" id="password" name="user_password" placeholder="Password" required/>
              </fieldset>

              <button type="submit">Sign Up</button>
            </form>
          </div>
        </div>
      </div>
    </>
  );
}
