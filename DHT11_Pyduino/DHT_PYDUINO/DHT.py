import serial
import time
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from collections import deque
import re # <-- NOVA BIBLIOTECA IMPORTADA: Expressões Regulares

# --- CONFIGURAÇÕES ---
arduino_port = 'COM3' # Altere para a porta correta
baud_rate = 19200
MAX_DATA_POINTS = 50

# --- PREPARAÇÃO DOS DADOS E DO GRÁFICO ---
time_data = deque(maxlen=MAX_DATA_POINTS)
temp_data = deque(maxlen=MAX_DATA_POINTS)
umid_data = deque(maxlen=MAX_DATA_POINTS)
gas_data = deque(maxlen=MAX_DATA_POINTS)

fig, (ax1, ax2, ax3) = plt.subplots(3, 1, figsize=(8, 9))
fig.suptitle('Monitoramento de Sensores em Tempo Real', fontsize=16)

# --- FUNÇÃO DE ATUALIZAÇÃO (com a lógica corrigida) ---
def update(frame):
    """
    Esta função é chamada repetidamente para ler os dados e redesenhar o gráfico.
    """
    global temp, umid, gas # Usar variáveis globais para guardar o último valor válido
    
    line = "" # Inicia a linha como vazia
    try:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').strip()
            
            # --- NOVA LÓGICA DE INTERPRETAÇÃO COM REGEX ---
            parts = line.split('|')
            if len(parts) == 3:
                # Expressão Regular para encontrar um número (inteiro ou decimal)
                num_regex = re.compile(r"[-+]?\d*\.\d+|\d+")

                # Extrai a temperatura
                temp_match = num_regex.search(parts[0])
                if temp_match:
                    temp = float(temp_match.group(0))
                
                # Extrai a umidade
                umid_match = num_regex.search(parts[1])
                if umid_match:
                    umid = float(umid_match.group(0))
                
                # Extrai o gás
                gas_match = num_regex.search(parts[2])
                if gas_match:
                    gas = int(gas_match.group(0))

                # Adiciona os novos dados às listas para plotagem
                current_time = time.time()
                time_data.append(current_time)
                temp_data.append(temp)
                umid_data.append(umid)
                gas_data.append(gas)
                
                print(f"Dados Válidos: Temp={temp}°C, Umid={umid}%, Gás={gas}")
    
    except Exception as e:
        # Se qualquer outro erro ocorrer, imprime para podermos depurar
        print(f"A ignorar linha ou erro: '{line}' -> {e}")
        return

    # --- ATUALIZAÇÃO DOS GRÁFICOS ---
    if len(time_data) > 0:
        # Limpa e redesenha o gráfico de Temperatura
        ax1.clear()
        ax1.plot(list(time_data), list(temp_data), color='r', marker='o', linestyle='-')
        ax1.set_ylabel('Temperatura (°C)')
        ax1.set_title('Temperatura')
        ax1.grid(True)
        
        # Limpa e redesenha o gráfico de Umidade
        ax2.clear()
        ax2.plot(list(time_data), list(umid_data), color='b', marker='o', linestyle='-')
        ax2.set_ylabel('Umidade (%)')
        ax2.set_title('Umidade')
        ax2.grid(True)
        
        # Limpa e redesenha o gráfico de Gás
        ax3.clear()
        ax3.plot(list(time_data), list(gas_data), color='g', marker='o', linestyle='-')
        ax3.set_ylabel('Nível de Gás')
        ax3.set_title('Gás')
        ax3.set_xlabel('Tempo')
        ax3.grid(True)
        
        fig.tight_layout(rect=[0, 0, 1, 0.96])


# --- PONTO DE PARTIDA DO SCRIPT ---
if __name__ == "__main__":
    try:
        print(f"A tentar conectar à porta {arduino_port}...")
        ser = serial.Serial(arduino_port, baud_rate, timeout=1)
        time.sleep(2)
        print("Conexão estabelecida! A iniciar o gráfico...")

        # Inicia as variáveis com um valor padrão
        temp, umid, gas = 0.0, 0.0, 0
        
        ani = FuncAnimation(fig, update, interval=1000, cache_frame_data=False)
        plt.show()

    except serial.SerialException as e:
        print(f"ERRO: Não foi possível abrir a porta serial {arduino_port}.")
        print(f"Detalhes: {e}")
        print("Verifique se o Arduino está conectado, a porta COM está correta e o Monitor Serial da IDE está FECHADO.")
    
    except KeyboardInterrupt:
        print("\nPrograma interrompido pelo utilizador.")

    finally:
        if 'ser' in locals() and ser.is_open:
            ser.close()
            print("Conexão serial fechada.")