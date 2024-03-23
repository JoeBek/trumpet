import express from "express";
import path from "path";

const PORT = process.env.PORT || 3000;
const PATH = path.join(__dirname, "../frontend/build");

const app = express();

app.use(express.static(PATH));

//

app.listen(PORT, () => {
  console.log(`prosthetiproxy listening on ${PORT}`);
});