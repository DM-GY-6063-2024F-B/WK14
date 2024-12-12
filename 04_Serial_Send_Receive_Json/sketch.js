let mSerial;

let connectButton;

let cBackground;

function sendSerial() {
  let data = { x: mouseX, y: mouseY, w: width, h: height };
  let dataString = JSON.stringify(data);

  mSerial.write("P" + dataString + "\n");
}

function receiveSerial() {
  if (mSerial.availableBytes() > 0) {
    let mLine = mSerial.readUntil("\n");
    mLine = trim(mLine);
    if (!mLine) return;
    if (mLine.charAt(0) != "{") return;

    let data = JSON.parse(mLine);
    cBackground = map(data.value, data.min, data.max, 0, 255, true);
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
