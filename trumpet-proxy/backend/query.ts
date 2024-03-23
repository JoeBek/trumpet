import OpenAI from "openai";

const openai = new OpenAI();

export async function query(): Promise<string | null> {
  const res = await openai.chat.completions.create({
    model: "gpt-4-vision-preview",
    messages: [
      {
        role: "user",
        content: [
          {type: "text", text: "List the notes in order. Response format must be [A, G, E, etc.]"},
          {type: "image_url", image_url: {
            url: "https://gcdnb.pbrd.co/images/TtNdHl5KlvQQ.png",
            detail: "auto"
          }}
        ]
      }
    ]
  });
  return res.choices[0].message.content;
}
