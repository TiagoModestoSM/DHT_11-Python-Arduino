🌡️ Projeto DHT_11 – Leitura de Umidade e Temperatura via Serial
📌 Descrição

Este projeto tem como objetivo realizar a leitura de dados de um sensor DHT11 (umidade e temperatura) conectado a um Arduino, enviando essas informações pela porta serial para um script em Python, onde os dados são processados e exibidos juntamente com a data e hora da leitura.

O projeto é ideal para estudos de:

Comunicação Serial

Integração Arduino + Python

Sensores de temperatura e umidade

Monitoramento ambiental básico

🧰 Tecnologias Utilizadas

Arduino (qualquer modelo compatível)

Sensor DHT11

Python 3

Biblioteca pySerial

Biblioteca datetime

🔌 Esquema de Funcionamento

O DHT11 coleta os dados de:

Umidade (%)

Temperatura (°C)

Índice de calor (°C e °F)

O Arduino envia esses dados formatados via Serial.

O Python:

Lê os dados da porta serial

Trata a string recebida

Extrai os valores

Exibe os dados junto com o horário da leitura

📁 Estrutura do Projeto
DHT_11/
│
├── dht11_serial.py     # Script Python para leitura da Serial
├── README.md           # Documentação do projeto
└── arduino/
    └── dht11.ino       # Código Arduino para o sensor DHT11
⚙️ Pré-requisitos

Antes de executar o projeto, certifique-se de ter:

Python 3 instalado

Arduino IDE instalada

Biblioteca pySerial instalada no Python

Instalação da biblioteca pySerial:

pip install pyserial
▶️ Como Executar

Conecte o sensor DHT11 ao Arduino.

Faça o upload do código Arduino (dht11.ino) para a placa.

Conecte o Arduino ao computador via USB.

Verifique a porta serial utilizada (ex: COM5 no Windows).

No código Python, ajuste a porta se necessário:

ser = serial.Serial('COM5', 9600)

Execute o script Python:

python dht11_serial.py
📤 Exemplo de Saída no Terminal
Humidity: 55%	Temperature: 27 °C	Heat Index: 80 °F	Heat Index: 26 °C
Hora atual: 2024-06-04 15:32:10
🧠 Observações

A taxa de transmissão (baud rate) deve ser a mesma no Arduino e no Python (9600).

O script utiliza try/except para permitir interrupção segura com Ctrl + C.

A conexão serial é fechada corretamente ao encerrar o programa.

✍️ Autor

Tiago Modesto (Labigó)
📅 Data: 04/06/2024

Projeto desenvolvido para fins educacionais e aprendizado em eletrônica e programação.

📜 Licença

Este projeto é de uso livre para fins educacionais.
Sinta-se à vontade para estudar, modificar e compartilhar.
