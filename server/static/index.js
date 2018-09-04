var SetTime = prompt("원하는 시간을 적어주세요(분 씩으로)","600");

function msg_time() {	
	
	m = "00:"+ Math.floor(SetTime / 60) + ":" + (SetTime % 60);	
	
	var msg = m ;
	
	document.all.ViewTimer.innerHTML = msg;		
			
	SetTime--;					
	
	if (SetTime < 0) {			
		
		clearInterval(tid);		
		alert("종료");
	}
	
}

window.onload = function TimerStart(){ tid=setInterval('msg_time()',1000) };

