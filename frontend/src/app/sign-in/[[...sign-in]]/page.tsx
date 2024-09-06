import { SignIn } from "@clerk/nextjs";
import Image from "next/image";

export default function Page() {
	return (
		<div className='min-h-screen  mx-10 mt-20'>
			<div className='flex justify-between '>
				<div className='relative ml-20 hidden lg:block'>
					<div className='bg-blue-400 rounded-3xl  w-[13rem] h-[13rem] opacity-40 transform translate-x-72 translate-y-40 '></div>
					<Image
						src={"/blind.jpg"}
						alt={"not found"}
						width={350}
						height={450}
						className='rounded-3xl shadow-xl'
					/>
					<div className='bg-pink-400 rounded-3xl  w-[13rem] h-[13rem] opacity-40 transform -translate-x-16 -translate-y-28 '></div>
				</div>
				<div className='mr-36 mt-36'>
					<SignIn />
				</div>
			</div>
		</div>
	);
}
