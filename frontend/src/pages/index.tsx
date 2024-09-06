import Content from "@/components/Content";
import IndexNavBar from "@/components/IndexNavBar";

export default function IndexPage() {
  return (
    <>
      <div className="relative w-full h-screen bg-gradient-to-r from-blue-400 via-purple-400 to-pink-400">
        <IndexNavBar />
        <Content />
      </div>
    </>
  );
}

