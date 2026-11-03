# Implementação 5

## Ambiente de Desenvolvimento

* **Sistema Operacional:** macOS
* **Linguagem:** C (Padrão C17 / `gnu17`)
* **Compilador:** `gcc` (Clang) com suporte a `-pthread`

## Estrutura dos Arquivos

* **`sync_car.c`**: Contém a implementação da lógica principal das funções de sincronização da estação:
  * `station_init`: Inicializa as primitivas de sincronização e o estado da estação.
  * `station_load_car`: Gerencia a chegada do vagão e controla a espera até o embarque completo.
  * `station_wait_for_car`: Bloqueia o passageiro até haver vagas disponíveis.
  * `station_on_board`: Atualiza o estado da estação após a acomodação do passageiro e sinaliza a partida do vagão.

* **`sync_car-runner.c`**: Arquivo de teste principal (fornecido/adaptado), responsável por instanciar a estação, simular a criação concorrente de threads de passageiros e validar os requisitos do sistema.

* **`sync_car.h`**: Cabeçalho com a definição da `struct station` e protótipos das funções.

## Como Compilar e Executar

O projeto possui um `Makefile` configurado para automatizar todo o processo de compilação e execução.

### 1. Compilação

Para compilar todos os executáveis do projeto do zero, rode:

```bash
make
```

Para limpar os arquivos de objeto (`.o`) e executáveis antigos, rode:

```bash
make clean
```

---

### 2. Execução 

Rode no terminal:

```bash
./sync_car
```

