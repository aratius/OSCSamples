// https://www.npmjs.com/package/node-osc
const { Client } = require("node-osc")

const REMOTE_IP = "127.0.0.1";
const PORT_OUTGOING = 12000
let client

const send = () => {
  client = new Client(REMOTE_IP, PORT_OUTGOING)

  console.log("an app is running ...");

  // NOTE: 1秒おきに"/test"にランダムな数値を送る例
  setInterval(() => {
    const val = Math.random()
    client.send("/test", val);
    console.log(`osc send \/\"test"\ ${val}`);
  }, 1000)
}

send()