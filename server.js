const mongoose = require("mongoose");
const Area = require("./models/area"); 
const SerialPort = require("serialport");
const Readline = require("@serialport/parser-readline");

const port = new SerialPort("/dev/ttyUSB0", {
  baudRate: 9600, 
});


const parser = port.pipe(new Readline({ delimiter: "\n" }));


port.open((err) => {
  if (err) {
    console.error("Error opening serial port:", err);
  } else {
    console.log("Serial port opened.");
  }
});

// Listen for data from the serial port-
parser.on("data", (data) => {
  try {
    const areaData = JSON.parse(data);
    saveData(areaData);
  } catch (error) {
    console.error("Error parsing JSON data:", error);
  }
});

mongoose.connect(
  "mongodb+srv://user:hello@sit314.1mcguhs.mongodb.net/?retryWrites=true&w=majority",
  { useNewUrlParser: true, useUnifiedTopology: true }
);

// Function to save data to MongoDB
function saveData(areaData) {
  const low = 0;
  const high = 40;
  const reading = Math.floor(Math.random() * (high - low) + low);
  areaData.people = reading;

  if (areaData.people === 0) {
    areaData.bulbStatus = false;
  }

  const newAreaData = new Area({
    id: areaData.id,
    name: areaData.name,
    motion_detected: areaData.motion_detected,
    timestamp: areaData.timestamp,
    people: areaData.people,
  });

  newAreaData
    .save()
    .then((doc) => {
      console.log(doc);
    })
    .then(() => {
      mongoose.connection.close();
    });

  const jsonString = JSON.stringify(areaData);
  console.log(jsonString);
}
