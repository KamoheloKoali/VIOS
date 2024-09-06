import { UserButton } from "@clerk/nextjs";
import React from "react";

const Dashboardlayout = ({ children }) => {
	return (
		<div>
			<UserButton />
			{children}
		</div>
	);
};

export default Dashboardlayout;
