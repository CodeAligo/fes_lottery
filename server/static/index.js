var SetTime = prompt("원하는 시간을 적어주세요(분 씩으로)","10");
SetTime = SetTime * 60

function msg_time() {
	n = Math.floor(SetTime/60)
	if (n < 10) {
		n = "0" + String(n)
	}

	y = SetTime % 60
	if (y < 10) {
		y = "0"+String(y)
	}
	m = "00:"+ n + ":" + y;

	var msg = m ;


	document.all.ViewTimer.innerHTML = msg;

	SetTime--;

	if (SetTime < 0) {

		clearInterval(tid);
		alert("종료");

	}

}

window.onload = function TimerStart(){ tid=setInterval('msg_time()',1000) };
