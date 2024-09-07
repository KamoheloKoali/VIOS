import Image from "next/image";
import Link from "next/link";

export default function Content() {
  return (
    <>
      <div className=" flex justify-between mx-14  min-h-screen ">
        <div>
          <div className="relative mt-20 sm:mt-16 md:mt-28 lg:mt-36 xl:mt-40 ">
            <h1 className=" text-3xl sm:text-2xl md:text-3xl lg:text-4xl xl:text-5xl font-inter font-bold text-black">
              Empowering the Visually Impaired <br /> with  Real-Time Object
              Detection
            </h1>
          </div>

          <div className="relative mt-16 sm:mt-14 md:mt-20 lg:mt-32 xl:mt-40  max-w-3xl">
            <p className=" md:text-lg lg:text-xl xl:text-2xl font-inter text-gray-800">
              Navigating unfamiliar environments can be challenging for visually
              impaired individuals. <b>Eyes for the Blind</b> is a wearable device
              designed to help users safely and confidently move through their
              surroundings. By leveraging advanced obstacle detection and
              auditory feedback, our solution enhances independence and enables
              seamless interaction with the world around them.
            </p>
          </div>

          <div className="relative mt-20 ">
            <div className=" w-56 h-16 bg-pink-300 bg-opacity-50 rounded-full flex items-center justify-center  ">
              <Link
                href={"/sign-in"}
                className=" text-2xl font-inter text-black"
              >
                Sign In
              </Link>
            </div>
          </div>
        </div>

        <div className="hidden lg:block">
          <div className="flex">
            <div className=" w-48 h-40 transform translate-y-20 -translate-x-20 bg-[#FE05B3] bg-opacity-30"></div>
            <div className=" w-20 h-20 transform translate-y-28 translate-x-28 bg-blue-500 bg-opacity-30"></div>
          </div>
          <Image src="/file.png" alt="person" width={341} height={341} />

          <div className="flex">
            <div className="w-20 h-20 transform -translate-y-12 -translate-x-10 bg-[#FE05B3] bg-opacity-30"></div>
            <div className=" w-48 h-40 transform -translate-y-20 translate-x-40 bg-blue-500 bg-opacity-30"></div>
          </div>
        </div>
      </div>
    </>
  );
}
