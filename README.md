# 🚛 Jorge the Truck Driver — Catálogo de versões

Este é o ponto de entrada do projeto. **As cinco versões estão organizadas separadamente.**
O jogo normal no site continua sendo o `index.html` da raiz.

| Versão | Onde encontrar | Como jogar |
|---|---|---|
| 🌐 HTML normal | [versoes/html-normal](versoes/html-normal/) | [Site oficial](https://jorgethetruckdriver.vercel.app/) |
| 🟦 HTML Pixel Art | [versoes/html-pixel](versoes/html-pixel/) | [Arquivo HTML da versão Pixel](versoes/html-pixel/index.html) |
| 📱 Android normal | [versoes/android-normal](versoes/android-normal/) | [Código Android normal](https://github.com/alan102168/jorge-truck-driver-android/tree/android-normal) |
| 📱 Android Pixel Art | [versoes/android-pixel](versoes/android-pixel/) | [Código Android Pixel](https://github.com/alan102168/jorge-truck-driver-android/tree/android-pixel) |
| 🎮 ROM Mega Drive Pixel Art | [versoes/rom-pixel](versoes/rom-pixel/) | [Código da ROM](https://github.com/alan102168/jogo-sest-senat-2d-caminhao/tree/rom-pixel-art/megadrive) |

## Abrir / baixar versões

**HTML normal:** [Jogar online](https://jorgethetruckdriver.vercel.app/) — [Código](versoes/html-normal/index.html).

**HTML Pixel Art:** [Código HTML](versoes/html-pixel/index.html) — baixar o `index.html` dessa pasta e abrir no navegador.

**Android normal:** [Releases de APK](https://github.com/alan102168/jorge-truck-driver-android/releases) — [branch Android normal](https://github.com/alan102168/jorge-truck-driver-android/tree/android-normal).

**Android Pixel Art:** [Releases de APK](https://github.com/alan102168/jorge-truck-driver-android/releases) — [branch Android Pixel](https://github.com/alan102168/jorge-truck-driver-android/tree/android-pixel).

**ROM Pixel Art:** [Releases da ROM](https://github.com/alan102168/jogo-sest-senat-2d-caminhao/releases) — [branch ROM Pixel](https://github.com/alan102168/jogo-sest-senat-2d-caminhao/tree/rom-pixel-art). Requer um emulador Mega Drive compatível no Game Stick.

## Separação segura

- `index.html` na raiz e `versoes/html-normal/index.html`: HTML normal.
- `versoes/html-pixel/index.html`: HTML Pixel Art para PC/celular.
- Repositório Android, branch `android-normal`: APK original.
- Repositório Android, branch `android-pixel`: APK Pixel Art (ID de app independente).
- Branch `rom-pixel-art`: jogo nativo SGDK para Mega Drive, ROM `.bin` e capa `.png`.

Cada ramo Android tem sua compilação GitHub Actions. O arquivo HTML Pixel Art **não é uma ROM**. A ROM é feita em C para Mega Drive. A compatibilidade com M8 Lite precisa ser testada no aparelho.

[📂 Abrir menu das versões](versoes/)
