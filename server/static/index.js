var SetTime = prompt("몇분 타이머? (기본: 10분)","10");
SetTime = SetTime * 60

function msg_time() {
    hour = 0
	min = Math.floor(SetTime/60)
    while (min >= 60) {
        min -= 60
        hour++
    }

    if (hour < 10) {
        hour = "0" + String(hour)
    }
        
	if (min < 10) {
		min = "0" + String(min)
	}

	sec = SetTime % 60
	if (sec < 10) {
		sec = "0"+String(sec)
	}
	remainedTime = hour + ":"+ min + ":" + sec;


	document.all.ViewTimer.innerHTML = remainedTime;

	SetTime--;

	if (SetTime < 0) {

		clearInterval(tid);
		alert("종료");

	}

}

window.onload = function TimerStart(){ tid=setInterval('msg_time()',1000) };
