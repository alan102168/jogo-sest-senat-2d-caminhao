# Jorge the Truck Driver — Mega Drive / M8 Lite (prototipo)

Este projeto adapta a ideia do jogo HTML original **Caminhao pelo Rio** para uma
ROM **de Sega Mega Drive**, que pode funcionar em emuladores de Mega Drive e em
alguns Game Stick M8 Lite. **Nao e um conversor de HTML para .bin**:
a mecanica foi reprogramada em C com [SGDK](https://github.com/Stephane-D/SGDK).

## O que a versao 16 bits faz
- Caminhao do Jorge em uma estrada de 3 faixas;
- Caixas para pegar (**+1 ponto**) e obstaculos para evitar (**-1 vida**);
- Caixas perdidas retiram **3 pontos**, sem pontuacao negativa;
- 5 vidas, tela inicial, pausa, game over e reinicio;
- Controle padrao Mega Drive de 3 ou 6 botoes: cima/baixo muda a faixa,
  A/C acelera, B freia, START inicia/pausa.

Os graficos desta primeira versao sao em estilo texto/tile 16 bits.
Ainda nao reproduz todas as fases, mapas, artes ou efeitos do HTML original.

## Build automatizado
O workflow em `.github/workflows/megadrive-rom.yml` usa SGDK e gera:
- `Jorge_Truck_Driver.bin` — ROM Mega Drive verdadeira;
- `Jorge_Truck_Driver.png` — capa PNG com o MESMO nome da ROM;
- `Jorge_Truck_Driver_M8_Lite.zip` — pacote com ambos os arquivos.

As versoes sao publicadas em **Releases** e podem ser baixadas nos Artifacts
da aba Actions, caso a publicacao seja permitida.

## Colocar no M8 Lite
1. Primeiro, teste a ROM em um emulador de Mega Drive no computador.
2. Faca backup do microSD inteiro do Game Stick antes de mexer.
3. Veja qual pasta/estrutura de jogos o SEU firmware realmente utiliza.
4. Coloque a ROM e a capa juntas:
   `Jorge_Truck_Driver.bin` e `Jorge_Truck_Driver.png`.
5. Se o Game Stick tiver listagem indexada ou outro metodo de importar
   jogos, siga o procedimento especifico do seu aparelho.
6. Nao apague jogos originais, BIOS, arquivos do firmware, nem altere particoes.

**Atencao:** `.bin` nao identifica sozinho um console. Uma ROM Mega Drive
nao roda no emulador de Super Nintendo/PlayStation. Ainda e necessario testar
no M8 Lite do usuario: revisoes diferentes podem ter listas de compatibilidade
e emuladores diferentes.

## Compilar localmente
Com Docker instalado, na pasta `megadrive`:

```bash
docker run --rm -v "$PWD:/m68k" registry.gitlab.com/doragasu/docker-sgdk:v2.00
```

O compilado SGDK fica em `out/rom.bin`. Para gerar a capa:

```bash
python -m pip install pillow
python tools/create_cover.py
```

## Estrutura
- `src/main.c` — jogo nativo de Mega Drive
- `tools/create_cover.py` — arte de capa original
- `tools/verify_rom.py` — checa assinatura SEGA da ROM
- `.github/workflows/megadrive-rom.yml` — build e GitHub Releases

A branch `main` mantem a versao HTML publicada na Vercel.
