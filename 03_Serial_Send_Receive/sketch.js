let mSerial;

let connectButton;

let cBackground;

function sendSerial() {
  let mouseVal = 0;
  if (mouseX > width / 2) {
    mouseVal = 1;
  }

  mSerial.write("P" + mouseVal + "\n");
}

function receiveSerial() {
  if (mSerial.availableBytes() > 0) {
    let mLine = mSerial.readUntil("\n");
    mLine = trim(mLine);
    if (!mLine) return;

    let sensorVal = int(mLine);
    cBackground = map(sensorVal, 0, 2000, 0, 255, true);
  }
}

function connectToSerial() {
  if (!mSerial.opened()) {
    mSerial.open(9600);
    connectButton.hide();
  }
}

function setup() {
  createCanvas(windowWidth, windowHeight);

  mSerial = createSerial();

  connectButton = createButton("Connect To Serial");
  connectButton.position(width / 2, height / 2);
  connectButton.mousePressed(connectToSerial);

  cBackground = 0;
}

function draw() {
  background(cBackground);

  if (mSerial.opened()) {
    sendSerial();
    mSerial.write("G");
    receiveSerial();
  }
}
