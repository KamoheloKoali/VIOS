import { SignUp } from "@clerk/nextjs";
import Image from "next/image";

export default function Page() {
	return (
		<div className='min-h-screen  mx-10 mt-20'>
			<div className='flex justify-between '>
				<div className='relative ml-20 hidden lg:block'>
					<div className='bg-blue-400 rounded-3xl  w-[15rem] h-[15rem] opacity-40 transform translate-x-[33rem] translate-y-40 '></div>
					<Image
						src={"/blind1.jpg"}
						alt={"not found"}
						width={650}
						height={1550}
						className='rounded-3xl shadow-xl'
					/>
					<div className='bg-pink-400 rounded-3xl  w-[13rem] h-[13rem] opacity-40 transform -translate-x-16 -translate-y-28 '></div>
				</div>
				<div className='mr-36 mt-36'>
					<SignUp />
				</div>
			</div>
		</div>
	);
}
