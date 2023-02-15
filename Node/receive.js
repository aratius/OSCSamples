// https://www.npmjs.com/package/node-osc
const { Server } = require("node-osc")

const PORT_INCOMMING = 12000
let server

const receive = () => {
  server = new Server(PORT_INCOMMING, "0.0.0.0", () => {
    console.log("OSC Server is running");
  })

  server.on("/test", (msg) => {
    console.log(`message received : ${msg}`);
  })
}

receive()