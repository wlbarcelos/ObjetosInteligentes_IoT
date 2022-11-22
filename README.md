# ObjetosInteligentes_IoT - Lixeira com monitoramento inteligente de capacidade

Descrição do Projeto

   O projeto consiste no monitoramento inteligente do volume de capacidade, 
de uma lixeira informando quando sua capacidade estiver completa para a 
manutenção do recipiente da lixeira.

Materiais utilizados

Para o protótipo do projeto foram utilizados os materiais abaixo:

- Placa Protoboard 400 pinos
- Placa DOIT ESP32 WROOM 32D Wifi/ Bluetooth
- 1 Sensor Ultrasônico
- 1 Led Difuso Verde 5mm - 5v
- 1 Led Difuso Vermelho 5mm - 5v
- 2 resistores 220
- Kit Jumper Macho Macho
- Kit JUmper Macho Femea
- 1 caixa de papelão simulando a lixeira.

Funcionalidades

A funcionalidada consiste no monitoramento da capaciade com o sensor ultrasonico, quando enquanto a lixeira
estiver com a capacidade, através de medição do sensor, o led verde fica ligado, é enviado através do protocolo 
MQTT para um Broker na web a cada segundo, a informação com da capacidade e a mensagem "Lixeira com capacidade"
após a capacidade estar completa, então o Led verde desliga e liga o Led vermelho informando a capacidade e a
mensagem "Lixeira cheia" através do mesmo protocolo MQTT.

Esse projeto pode ser utilizado de base para aperfeiçoamento desse monitoramento.

Além do projeto estar no GITHUB existe também um video explicativo do projeto no Youtube
https://www.youtube.com/watch?v=PiCtKrdyMIY
