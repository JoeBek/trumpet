import express from "express";
import path from "path";
import { query } from "./query";

const PORT = process.env.PORT || 3000;
const PATH = path.join(__dirname, "../frontend/build");

const app = express();

let img = null;
let notes = "G A B C D";

app.use(express.static(PATH));

// Handle client request to upload image
app.post("/img", async (req, res) => {

  // Store the image on the backend

  // Send image to OpenAI
  const text = await query();

  // Store OpenAI results on backend
  if (text != null) {
    notes = text;
    console.log(notes);
  } else {
    console.log("OpenAI query failed");
  }

  res.end();
});

// Handle hardware request for music
app.get("music", (req, res) => {
  // Send music data
});

app.listen(PORT, () => {
  console.log(`prosthetiproxy listening on ${PORT}`);
});