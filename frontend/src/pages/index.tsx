import Content from "@/components/Content";
import NavBar from "@/components/NavBar";

export default function IndexPage() {
  return (
    <>
      <div className="relative w-full h-screen bg-gradient-to-r from-blue-400 via-purple-400 to-pink-400">
        <NavBar />
        <Content />
      </div>
    </>
  );
}
