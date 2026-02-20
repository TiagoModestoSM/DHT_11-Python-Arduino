# 🌡️ Sistema de Monitoramento com DHT11, LCD e Python

## 📌 Visão Geral

Este projeto implementa um **sistema completo de monitoramento ambiental**, utilizando o sensor **DHT11** para leitura de **temperatura**, **umidade** e cálculo de **índice de calor**, com três camadas principais:

1. **Arduino** – Aquisição dos dados, menu em LCD 16x2 e controle de hardware
2. **Comunicação Serial** – Envio contínuo dos dados formatados
3. **Python** – Leitura da Serial, tratamento dos dados e visualização gráfica em tempo real

O sistema foi desenvolvido com foco em **aprendizado**, **organização de código** e **integração entre hardware e software**.

---

## 🧰 Tecnologias Utilizadas

### Hardware

* Arduino (Uno, Nano ou compatível)
* Sensor **DHT11** (Temperatura e Umidade)
* Display **LCD 16x2 com interface I2C**
* Botões de navegação (UP, DOWN, ENTER, BACK)
* LEDs
* Buzzer

### Software

* Arduino IDE
* Python 3
* Bibliotecas Arduino:

  * `LiquidCrystal_I2C`
  * `Wire`
  * `DHT`
* Bibliotecas Python:

  * `pyserial`
  * `matplotlib`
  * `collections (deque)`
  * `re`

---

## 📁 Estrutura do Projeto

```bash
DHT_11-Python-Arduino/
│
├── DHT11_Pyduino/
│   └── DHT11_LCD
|       └── DTH11_LCD.ino # Código Arduino (LCD + Menu + Sensor)
|   └── DHT_PYDUINO
|       └── DHT.py  # Leitura serial e gráficos em tempo real
│
└── README.md                   # Documentação do projeto
```

---

## ⚙️ Funcionamento Geral do Sistema

### 🔹 Arduino

* Lê os dados do sensor **DHT11**
* Exibe informações em um **menu interativo no LCD**
* Permite navegação usando botões físicos
* Controla LEDs e buzzer
* Envia dados formatados via **Serial** em intervalos regulares

### 🔹 Comunicação Serial

* Dados enviados no formato texto
* Exemplo de saída:

```text
| Umidade:  55.2 % | Temperatura:  27.3 °C | Heat Index (F):  80.1 °F | Heat Index (C):  26.7 °C |
```

### 🔹 Python

* Lê os dados da porta serial
* Usa **expressões regulares** para extrair valores numéricos
* Armazena os últimos dados em filas (deque)
* Plota gráficos em tempo real:

  * Temperatura
  * Umidade
  * Nível de gás

---

## 📟 Menu no LCD (Arduino)

O sistema possui um menu navegável com botões:

* **UP / DOWN** → Navegação
* **ENTER** → Selecionar opção
* **BACK** → Retorno (estrutura preparada)

### Telas disponíveis:

1. Monitoramento (exibe temperatura e umidade)
2. Controle (aciona LED)
3. Control °C
4. Modo

O LCD também utiliza **caracteres personalizados**, como:

* Grau (°)
* Gota (umidade)
* Floco de neve

---

## 📊 Gráficos em Tempo Real (Python)

O script Python utiliza `matplotlib.animation.FuncAnimation` para atualizar os gráficos automaticamente.

Características:

* Atualização a cada 1 segundo
* Histórico limitado (janela deslizante)
* Tratamento de dados inválidos
* Execução contínua até interrupção manual

---

## ▶️ Como Executar

### 1️⃣ Arduino

1. Conecte o sensor DHT11 ao pino definido no código
2. Conecte o LCD via I2C
3. Ajuste os pinos dos botões, LEDs e buzzer se necessário
4. Faça o upload do arquivo `.ino`
5. Abra o Monitor Serial (9600 baud) para testes

### 2️⃣ Python

Instale as dependências:

```bash
pip install pyserial matplotlib
```

Configure a porta serial no código:

```python
arduino_port = 'COM3'
baud_rate = 19200
```

Execute:

```bash
python monitor_serial_plot.py
```

---

## ⚠️ Observações Importantes

* A **porta serial** deve ser a mesma no Arduino e no Python
* O **baud rate** precisa coincidir nos dois códigos
* Feche o **Monitor Serial da IDE Arduino** antes de rodar o Python
* O uso de `millis()` evita travamentos por `delay()`

---

## 🎯 Objetivos Educacionais

* Integração Arduino + Python
* Comunicação Serial
* Leitura de sensores
* Criação de menus em LCD
* Visualização gráfica em tempo real
* Organização e boas práticas de código

---

## ✍️ Autor

**Tiago Modesto de Sousa Moura**
📅 Julho de 2024

Projeto desenvolvido para fins educacionais, experimentação e aprendizado em sistemas embarcados.

---

## 📜 Licença

Projeto de uso livre para fins educacionais.
Sinta-se à vontade para estudar, modificar e expandir.

---

## 🚀 Possíveis Evoluções

* Refatoração para máquina de estados
* Salvamento de dados em arquivo (CSV)
* Dashboard com interface gráfica (PyQt)
* Integração com Wi-Fi / IoT
* Alarmes por limite de temperatura
