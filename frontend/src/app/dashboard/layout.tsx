import { UserButton } from "@clerk/nextjs";
import React, { ReactNode } from "react";

interface DashboardLayoutProps {
  children: ReactNode;
}

const Dashboardlayout = ({ children }: DashboardLayoutProps) => {
  return (
    <div>
      <UserButton />
      {children}
    </div>
  );
};

export default Dashboardlayout;
