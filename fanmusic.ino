#include <TimerOne.h>

int speed = 0;
int speedi = 0;
int flag = 1;

void motor() {
  if (speedi < speed) {
    digitalWrite(6, HIGH);
  }
  else {
    digitalWrite(6, LOW);
  }
  speedi += 1;
  if (speedi > 50) speedi = 0;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(6, OUTPUT);
}

/*发音控制
 * n范围1~7，分别对应do re mi fa so la si
 * 0为休止符，9为将四分音符延长至二分音符使用（已舍弃）
 * m范围1~3，控制高低音输出；1为低音，3为高音
 * 使用前请测试，可能部分风扇无法发出部分高音
 */
void fan(int n,int m) {
  switch (m){
    case 1:
    switch (n) {
    case 1:
      Timer1.initialize(78);
      Timer1.attachInterrupt(motor);
      Serial.println("do");
      break;
    case 2:
      Timer1.initialize(69);
      Timer1.attachInterrupt(motor);
      Serial.println("re");
      break;
    case 3:
      Timer1.initialize(62.5);
      Timer1.attachInterrupt(motor);
      Serial.println("mi");
      break;
    case 4:
      Timer1.initialize(59);
      Timer1.attachInterrupt(motor);
      Serial.println("fa");
      break;
    case 5:
      Timer1.initialize(52);
      Timer1.attachInterrupt(motor);
      Serial.println("so");
      break;
    case 6:
      Timer1.initialize(47);
      Timer1.attachInterrupt(motor);
      Serial.println("la");
      break;
    case 7:
      Timer1.initialize(44);
      Timer1.attachInterrupt(motor);
      Serial.println("si");   
      break;
    case 9:
      Serial.println("-"); 
      break;
    case 0:
      Timer1.initialize(500);
      Timer1.attachInterrupt(motor);
      Serial.println("0");  
      break;
  }
  break;
  case 2:
  switch (n) {
    case 1:
      Timer1.initialize(39);
      Timer1.attachInterrupt(motor);
      Serial.println("do");
      break;
    case 2:
      Timer1.initialize(35);
      Timer1.attachInterrupt(motor);
      Serial.println("re");
      break;
    case 3:
      Timer1.initialize(31);
      Timer1.attachInterrupt(motor);
      Serial.println("mi");
      break;
    case 4:
      Timer1.initialize(29);
      Timer1.attachInterrupt(motor);
      Serial.println("fa");
      break;
    case 5:
      Timer1.initialize(26);
      Timer1.attachInterrupt(motor);
      Serial.println("so");
      break;
    case 6:
      Timer1.initialize(23.5);
      Timer1.attachInterrupt(motor);
      Serial.println("la");
      break;
    case 7:
      Timer1.initialize(21);
      Timer1.attachInterrupt(motor);
      Serial.println("si");   
      break;
    case 9:
      Serial.println("-"); 
      break;
    case 0:
      Timer1.initialize(500);
      Timer1.attachInterrupt(motor);
      Serial.println("0");  
      break;
  }
  break;
  case 3:
  switch (n) {
    case 1:
      Timer1.initialize(19.5);
      Timer1.attachInterrupt(motor);
      Serial.println("do");
      break;
    case 2:
      Timer1.initialize(17);
      Timer1.attachInterrupt(motor);
      Serial.println("re");
      break;
    case 3:
      Timer1.initialize(15.6);
      Timer1.attachInterrupt(motor);
      Serial.println("mi");
      break;
    case 4:
      Timer1.initialize(14.5);
      Timer1.attachInterrupt(motor);
      Serial.println("fa");
      break;
    case 5:
      Timer1.initialize(13);
      Timer1.attachInterrupt(motor);
      Serial.println("so");
      break;
    case 6:
      Timer1.initialize(11);
      Timer1.attachInterrupt(motor);
      Serial.println("la");
      break;
    case 7:
      Timer1.initialize(10);
      Timer1.attachInterrupt(motor);
      Serial.println("si");   
      break;
    case 9:
      Serial.println("-"); 
      break;
    case 0:
      Timer1.initialize(500);
      Timer1.attachInterrupt(motor);
      Serial.println("0");  
      break;
  }
}
}
/*读简谱并演奏，调用fan函数
 * 三个参数均为char型数组 
 * str： 乐谱本身
 * mask：音符时值，对乐谱中对应位置有效。
 *       几分音符就输入几：四分音符为4，全音符为1；特殊：十六分音符输入9；
 * h:    音高选择，1位低音，3位高音
 * 
 */
void music(char str[],char mask[],char h[])
{
  int len = strlen(str);
  for (int i = 0;i < len ;i++){
    fan((int)str[i]-48,(int)h[i]-48);
    int tmp=(int)mask[i]-48;
    if(tmp==9) tmp=16;
    int d=128*16/(tmp)-10;
    delay(d);
    //音间隔10ms
    Timer1.initialize(500);
    Timer1.attachInterrupt(motor);
    delay(10);
  }
}

/*
 * speed指定占空比，范围0~50；低于10某些电机/风扇可能无法启动
 * 示例内容为超级玛丽主题曲
 * 使用种应注意控制变量个数以防止arduino可能发生的内存不足
 */
void loop() {
  speed = 20;
  char a[50];
  char b[50];
  char c[50];
  Serial.println("SuperMarioStart!");
  strcpy(a,"333013505010503067076555645031270");
  strcpy(b,"989998888889988989998888899989989");
  strcpy(c,"333233322232222222222233333233322");
  music(a,b,c);
  Serial.print("1");
  strcpy(a,"1050306707653564503127005443305610612");
  strcpy(b,"8998898999888889998998989998999999999");
  strcpy(c,"3222222222223333323332223333322232233");
  music(a,b,c);
  Serial.print("2");
  strcpy(a,"054433011100544330561061205040300");
  strcpy(b,"899989989888999899999999988989884");
  strcpy(c,"233333233322333332223223323232322");
  music(a,b,c);
  Serial.print("3");
  strcpy(a,"054433056106120544330111005443305610612");
  strcpy(b,"899989999999998999899898889998999999999");
  strcpy(c,"233333222322332333332333223333322232233");
  music(a,b,c);
  Serial.print("4");
  strcpy(a,"0504030011101231650111012300");
  strcpy(b,"8898988498999898988989999944");
  strcpy(c,"2323232233323333222333233322");
  music(a,b,c);
  Serial.print("5");
  strcpy(a,"111012316503330135050105030670760");
  strcpy(b,"989998989889899988888899889899999");
  strcpy(c,"333233332223332333222322222222222");
  music(a,b,c);
  Serial.print("6");
  strcpy(a,"53564503127010503067076535645031270");
  strcpy(b,"88889998998989988989998888899989989");
  strcpy(c,"23333323333232222222222233333233322");
  music(a,b,c);
  Serial.print("7");
  strcpy(a,"3150564460766654316503150564460744432100");
  strcpy(b,"9898898988888888989889898898988989888884");
  strcpy(c,"3322223322233333332223322223322233333322");
  music(a,b,c);
  Serial.print("8");

  strcpy(a,"315056446076665431650");
  strcpy(b,"989889898888888898988");
  strcpy(c,"332222332232222222333");
  music(a,b,c);
  Serial.print("9");
  strcpy(a,"315056446074443210011101231650");
  strcpy(b,"989889898898988888498999898988");
  strcpy(c,"332222332223333332233323333222");
  music(a,b,c);
  Serial.print("10");
  strcpy(a,"111012300111012316503330135050");
  strcpy(b,"989888844989998989889899988888");
  strcpy(c,"333233322333233332223332333222");
  music(a,b,c);
  Serial.print("11");
  strcpy(a,"3150564460766654316503150564460744432100");
  strcpy(b,"9898898988888888989889898898988989888884");
  strcpy(c,"3322223322233333332223322223322233333322");
  music(a,b,c);
  Serial.print("12");
  
  Serial.print("done...");
  delay(5000);  
}
