function msg_time() {
    hour = 0
    min = Math.floor(SetTime/60)
    while (min >= 60) {
        min -= 60
        hour++
    }

    if (hour < 10) {                // 타이머 시간(hour)
        hour = "0" + hour
    }

    if (min < 10) {                 // 타이머 분(min)
        min = "0" + min
    }

    sec = SetTime % 60              // 타이머 초(se)
    if (sec < 10) {
        sec = "0" + sec
    }
	remainedTime = hour + ":" + min + ":" + sec;    // 시간 : 분 : 초


	document.all.ViewTimer.innerHTML = remainedTime;   // id = ViewTimer로 HTML 텍스트에 적용함

	SetTime--;   // 시간 감소


	if (SetTime < 0) {
		clearInterval(tid);
        window.location.href = "result"
        return
	}

    if (SetTime == 300) {
        document.all.Msg.innerHTML = "⚠️ 이번 회차 구매가 마감되었습니다."   // SetTime = 300 ⚠️ '이번 회차 구매가 마감되었습니다.' 출력
    }

}

function start_timer() {
    target = new Date()
    target.setHours(nextTime, 0, 0, 0)
    now = new Date()
    SetTime = target - now
    SetTime = Math.floor(SetTime / 1000)
    window.onload = function TimerStart(){ tid=setInterval('msg_time()',1000) };
}

before = 0

function load_NumWinners() {
    $.ajax({ // 남은 수령자의 값을 Go 서버에 정보 요청
        type:"GET",
        url:"/ajax",
        dataType:"text",

        success: function(data) {
            document.all.NumWinners.innerHTML =  "남은 당첨자 " + data + "명"
                if (data == 0) {
                    clearInterval(loader)
                    window.location.href = "timer"
                }
        }
    })
}
