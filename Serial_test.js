var mraa = require('mraa');
serialPort = new mraa.Uart(0)
serialPort.setBaudRate(9600);
serialPort.setMode(8, 0, 1);
serialPort.setFlowcontrol(false, false);
sleep(100);

while(true)
{
	serialPort.writeStr("test\n");
	sleep(100);
}

function sleep(delay) {
  delay += new Date().getTime();
  while (new Date() < delay) { }
}
