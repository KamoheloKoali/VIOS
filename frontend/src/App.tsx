import { Route, Routes } from "react-router-dom";

import IndexPage from "@/pages/index";
import Login from "@/components/Login";

function App() {
  return (
    <Routes>
      <Route element={<IndexPage />} path="/" />
      <Route element={<Login />} path="/Login" />
      {/* <Route element={<DocsPage />} path="/docs" />
      <Route element={<PricingPage />} path="/pricing" />
      <Route element={<BlogPage />} path="/blog" />
      <Route element={<AboutPage />} path="/about" /> */}
    </Routes>
  );
}

export default App;
