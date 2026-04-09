const int spkrPin = 3; // 3:ConnectorA 4:ConnectorB

//きらきら星

// 音階の周波数定義
#define DO 261.6
#define RE 293.665
#define MI 329.63
#define FA 349.228
#define SO 391.995
#define RA 440
#define TI 493.883
#define octDO 523.251

// メロディの配列（きらきら星）
float melody[] = {
  DO, DO, SO, SO, RA, RA, SO, // ドドソソララソ〜
  FA, FA, MI, MI, RE, RE, DO, // ファファミミレレド〜
  SO, SO, FA, FA, MI, MI, RE, // ソソファファミミレ〜c:\Users\user68\Desktop\10_Speaker-melody2\09_Speaker_2.ino
  SO, SO, FA, FA, MI, MI, RE, // ソソファファミミレ〜
  DO, DO, SO, SO, RA, RA, SO, // ドドソソララソ〜
  FA, FA, MI, MI, RE, RE, DO  // ファファミミレレド〜
};

// 音の長さの定義 (ms)
const int noteDuration = 400; // 1音の長さ
const int pauseBetweenNotes = 50; // 音と音の間のわずかな休止

void playmusic() {
  // 配列の要素数分だけループして再生
  int totalNotes = sizeof(melody) / sizeof(melody[0]);

  for (int i = 0; i < totalNotes; i++) {
    ledcWriteTone(spkrPin, melody[i]);
    
    // 7番目（フレーズの区切り）は少し長めに伸ばす演出
    if ((i + 1) % 7 == 0) {
      delay(noteDuration * 2); 
    } else {
      delay(noteDuration);
    }

    // 音が繋がって聞こえないよう、一瞬音を止める
    ledcWriteTone(spkrPin, 0);
    delay(pauseBetweenNotes);
  }
}

void setup() {
  pinMode(spkrPin, OUTPUT);
  // ESP32のLEDC設定（ピン番号, 周波数, 解像度）
  ledcAttach(spkrPin, 12000, 8);
}

void loop() {
  playmusic();
  
  // 1曲終わったら5秒待機
  delay(5000);
}