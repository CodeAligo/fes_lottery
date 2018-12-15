# fes_lottery/go-client

Go Modules를 사용하여 go1.11 이상이 필요합니다.

## 준비

먼저 클라이언트가 실행되고 있는 컴퓨터에서 접속 가능한 곳에 `fes_lottery/server`가 실행되고 있어야 합니다.

## 실행

```bash
go build
./go-client
```

`go-client`를 처음 실행할 시 `theworldisallone.db` 파일이 디렉터리에 생성되고, `NextTime`을 동기화하기 위하여 서버 도메인을 물어봅니다.

```bash
Server(blank for default): http://
```

`http://`  부분 뒤 서버의 도메인을 입력하세요.  다음, `NextTime`을 몇으로 설정할 지 물어봅니다.

```bash
NextTime(blank for an hour later):
```

아무 숫자도 입력하지 않고 엔터를 치면, 자동으로 다음 시각으로 설정됩니다. 그 후, 설정된 서버로 `NextTime`을 보냅니다.

만약 첫 실행이라면, 어드민을 생성해야합니다. 어드민은 클라이언트의 모든 작업을 수행할 수 있습니다.

```
It seems there's no admin. Do you want to register a new admin? (y/n)  y
Enter Your ID: admin
Enter Your Name: CodeAligo

Enter Your Password:
Type Again:

ID: admin, Name: CodeAligo. Is it you? (y/n) y
Success.
```

다음 실행 시 존재하는 어드민의 로그인 후에 새로운 어드민을 생성할 수 있으니 비밀번호는 꼭 기억하시길 바랍니다.


실행 시마다 어드민 로그인을 해야합니다.

```
-Logging in-
ID: admin
Password:
Login Success. Welcome CodeAligo.
>
```

로그인에 성공한 뒤에는 업무를 수행할 수 있습니다.

## 작업

로그인 후에 `> ` 형태의 콘솔 창이 보이게 됩니다. 이 곳에 적을 수 있는 명령어는 다음과 같습니다.

| 명령어 | 설명 |
| --- | --- |
| register | 새 어드민을 등록합니다. |
| logout | 현재 로그인 된 어드민을 로그아웃합니다. |
| lottery | 새 로터리를 등록합니다. |
| status | 현재 등록된 로터리의 수, 사용 중인 어드민의 정보를 띄웁니다. |
| pick | 이번 회차의 번호들을 뽑은 후, 서버로 전송합니다. |
| win | 이번 회차의 당첨된 로터리를 신분 확인 후 `수령됨`으로 체크합니다. |
| set | 디버그 용으로, 이번 회차의 번호를 수동으로 설정합니다. |
| server | 서버의 도메인을 변경합니다. |
| sendnum | 이번 회차의 번호를 수동으로 전송합니다. |
| sendmsg | 서버의 `/timer`에 보이는 메시지를 설정합니다. |
| newsess |  이번 회차를 종료하고 새로운 회차를 시작합니다. |
| exit | 프로그램을 종료합니다. |
| help | 명령어 목록을 보여줍니다. |

## 명령어별 부연 설명
### lottery

`lottery`를 입력해 새 로터리를 등록할 수 있습니다.
로터리의 주인의 학번을 입력한 뒤, 자동/수동의 여부를 입력합니다.

```
> lottery
Lottery Owner(ex 2826): 2826

Do you want to custom your numbers? (y/n)
```

수동은 `y`, 자동은 `n`을 입력합니다.

`y`을 입력한 경우, `1-35`의 네 정수를 입력합니다. 순서는 자동으로 정렬됩니다.

```
Enter Four Numbers: 1 2 3 4
```

다음, 수령 시 신분확인을 위한 8자리 숫자 비밀번호를 설정합니다. 비밀번호가 8자리인지만 체크하고, 숫자인지는 딱히 확인 코드를 넣지 않았습니다.

```
Enter 8-digit Passcode:
Passcode should be 8-digit.

Enter 8-digit Passcode:
Type Again:
Owner: 2826, Numbers: 1 2 3 4. Is it right? (y/n) y
```

정보 확인 단계에서 `n`을 입력시 학번 입력부터 다시 시작합니다.

## TODO

 - [ ] 4자리 모두 맞아야 당첨인 것을 당첨 단계를 나누기
 - [ ] 수익 계산
 - [ ] 당첨자 상금 계산
 - [ ] 코드 개편
