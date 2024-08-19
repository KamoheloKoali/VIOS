export default function Content() {
    return (
      <>
        <div className="absolute top-72 left-16">
          <h1 className="text-5xl font-inter font-bold text-black">
            Discerning objects that are in front of the user
          </h1>
        </div>

        <div className="absolute top-[530px] left-16 max-w-3xl">
          <p className="text-2xl font-inter text-gray-800">
            Visually Impaired individuals, mostly those who were not born
            visually impaired, may have a difficult time navigating through
            different environments. The idea around our MVP is to help users
            easily navigate and interact with different environments.
          </p>
        </div>

        <div className="absolute top-[763px] left-16">
          <button className="w-52 h-14 bg-pink-300 bg-opacity-50 rounded-full text-2xl font-inter text-black">
            Sign Up
          </button>
        </div>

        <div className="absolute top-[25%] left-[70%] w-52 h-48 bg-pink-500 bg-opacity-50"></div>
        <img
          src="../file.jpg"
          alt="person"
          className="absolute top-[40%] h-56 w-100 left-[75%] bg-opacity-50"
        />
        <div className="absolute top-[58%] left-[80%] w-60 h-56 bg-blue-300 bg-opacity-50"></div>
      </>
    );
  }