# Convergence_Arduino
아두이노 키트 공모전

### IoT 모방한 무선 통신 구현
리모컨 하나로 전등을 제어하고, 알람이 울리길 원하는 시간을 받고 알람이 울린다면 사용자가 일어나 가까이 가야만 알람이 꺼지는 방식으로 방식입니다. LCD, 스위치, 알람 등 다양한 모듈을 하나로 통제하여 간이 스마트홈을 구현하였습니다.
<img src = "https://github.com/ssoxong/Convergence_Arduino/assets/112956015/9938ca2a-6a2d-48d2-844f-e9a0afe529d2" width="50%" height="50%">  
https://www.youtube.com/watch?v=uvN3YUE7riE

### 준비
<img src = "https://github.com/ssoxong/Convergence_Arduino/assets/112956015/6c6728bb-9ad8-48ad-a017-592681136a3e" width="50%" height="50%">  
100~220Ω 저항, LED, IR센서&리모컨, 가변저항, 서보모터, 초음파 센서, 수동 부저, LCD 

### 회로도
<img src = "https://github.com/ssoxong/Convergence_Arduino/assets/112956015/927aec3b-14fc-4a1b-b7a5-bec2a24bd2f3" width="50%" height="50%">  


### 모듈별 기능 명세
|모듈명|기능|
|------|----|
서보모터|각도 조절을 통해 전등 스위치를 제어한다.
초음파 센서|사용자가 가까이 있는지 확인한다.
적외선 수신 센서 & 리모컨|리모컨을 이용해 원하는 버튼을 누르면 적외선 센서를 통해 해당 입력을 수신한다.
|LCD(+가변저항)|LCD를 통하여 현재 어떠한 기능이 동작되고 있고, 알람이 울리기까지 시간은 얼마나 남았는지 사용자에게 알려준다. 가변저항을 통해 LCD의 밝기를 조절한다.|
LED|리모컨의 입력이 있을 때, 정상적으로 입력되었다면 LED를 깜빡인다.
수동 부저|해당 부저를 통해 알람을 울린다. 계이름을 직접 입력하여 멜로디를 바꿀 수 있으며, 해당 프로젝트에서는 ‘학교 종’ 노래를 이용하였다.
