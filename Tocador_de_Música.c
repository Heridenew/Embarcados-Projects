// Frequências das notas musicais
int C = 528;
int D = 592;
int E = 624;
int G = 394;
int B = 468;

// Entradas/Saídas 
int buzzer = 2;
int botao = 3;

bool musicaAtiva = false; // Estado da música (ligada/desligada)
bool botaoPressionado = false; // Controle de leitura do botão
int indiceNota = 0; // Índice atual na música

int notas[] = {C, C, E, D, C, E, C, C, E, D, C, E, D, C, D, C, B, C, B, G, B, G, B, G, B, C};
int duracoes[] = {300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 400, 300, 300, 300, 400, 300, 300, 500, 300, 300, 300};
int totalNotas = sizeof(notas) / sizeof(notas[0]);

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(botao, INPUT_PULLUP);
}

void loop() {
  // Verificar estado do botão
  if (digitalRead(botao) == LOW) { // Botão pressionado
    if (!botaoPressionado) {
      musicaAtiva = !musicaAtiva; // Alternar estado da música
      botaoPressionado = true;    // Evitar múltiplas leituras
      if (!musicaAtiva) {
        noTone(buzzer);           // Interrompe imediatamente o som
        indiceNota = 0;           // Reinicia a música para o próximo ciclo
      }
    }
  } else {
    botaoPressionado = false; // Libera para nova leitura
  }

  // Tocar música apenas se for ativada e o índice da nota for válido
  if (musicaAtiva && indiceNota < totalNotas) {
    tone(buzzer, notas[indiceNota]);      // Tocar a nota atual
    delay(duracoes[indiceNota]);          // Esperar a duração
    noTone(buzzer);                       // Parar a nota
    delay(50);                            // Pequeno intervalo entre notas
    indiceNota++;                         // Avançar para a próxima nota
  }

  // Finalizar música ao término
  if (musicaAtiva && indiceNota >= totalNotas) {
    musicaAtiva = false;                  // Finaliza a música
    indiceNota = 0;                       // Reinicia para o próximo ciclo
  }
}
