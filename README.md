# fes_lottery

**fes_lottery**는 CodeAligo 동아리에서 학교 축제를 위해 진행하는 프로젝트로, 실재 재화가 아닌 축제에 사용하는 가상 화폐를 이용해 복권(로터리)을 판매하고, 공개하는 프로그램이 들어있습니다.


## 빌드 

**Server(Go)**

```shell
cd server
go build
```

**Client(C)**

[go-client/README.md 참고](go-client/README.md)

## 구성
크게 `client/`와 `server/`로 구분됩니다.

### Server

Server는 실행 시 커맨드라인에서 받은 인자를 포트로 http 서버를 실행하고, http를 이용해 클라이언트로부터 정보를 받습니다.

**실행**
```shell
$ ./server -h
Usage of ./server:
  -log string
    	A file for logging (default "access.log")
  -nt int
    	NextTime (default 10)
  -port string
    	A port number for the Server (default "8080")
```

```shell
$ ./server -port=8080 -nt=10
```

`-port`는 서버를 무슨 포트에 실행시킬지 결정합니다. 기본 값은 8080입니다.

`-nt`는 타이머를 몇시까지 구동시킬지 결정하는 `NextTime`의 초기값입니다.

`-log`는 서버 로그를 무슨 파일에 기록할 지 결정합니다. 기본 값은 `access.log`입니다.

#### /timer

서버 실행 뒤 `/timer`로 접속하면, `NextTime`의 값과 현재 시간을 비교해 복권 당첨 번호 공개까지 남은 시간을 보여줍니다. 만약 타이머가 끝나면,
`/result`로 리다이렉트됩니다.

#### /result

`/result`는 주로 `/timer`의 타이머가 0이 되었을 경우 리다이렉트로 들어오게 되는 페이지입니다. 당첨 번호와 남은 당첨자(수령자)를 보여줍니다. 남은 수령자는 ajax으로 5초마다 업데이트됩니다. 만약 남은 수령자가 0명이라면, `/timer`로 리다이렉트합니다.

#### /send

클라이언트로부터 값을 받기 위한 페이지입니다. 값에 문제가 없다면, `200`을 리턴하고, 문제가 있으면 `400`을 리턴합니다.

다음 값들은 각각 따로 또는 같이 보낼 수 있습니다.

필드 네임 | 타입 | 설명 | 예시
--- | --- | --- | ---
NextTime | int | 다음 타이머를 몇시까지 구동할 지 결정합니다. (1-24) | 10
RemainWinners | int | 남은 수령자 | 24
NumWinners | int | 총 수령자 | 25

당첨번호는 총 4가지이며, 1에서 25까지의 정수만 가능합니다. 만약 한자리 수일 경우 앞에 `0`을 붙여주어야하며, 따라서 타입은 `string`입니다.
`number`들은 따로 보낼 수 없습니다.

필드 네임 | 타입 | 예시
--- | --- | ---
number1 | string | 24
number2 | string | 09
number3 | string | 08
number4 | string | 03

**전송 예시**
```shell
curl http://localhost:8080/send?NextTime=10&NumWinners=25
```
```shell
curl http://localhost:8080/send?number1=24&number2=09&number3=08&number4=03&NextTime=10
```

#### /ajax

`/result` 페이지를 위한 ajax용 페이지입니다. json 형태입니다.

### Client

[go-client/README.md 참고](go-client/README.md)


## TODO

 - [ ] NextTime `null`에 대한 대처 코드 작성
 - [ ] `Msg`도 5초마다 불러올 수 있게 JavaScript 코드 수정
 - [ ] JavaScript 코드 싹 개편
